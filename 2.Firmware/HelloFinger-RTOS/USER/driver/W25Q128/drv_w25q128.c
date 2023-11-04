#include "drv_w25q128.h"

DMA_HandleTypeDef hdma_spi1_tx;
DMA_HandleTypeDef hdma_spi1_rx;
SPI_HandleTypeDef hspi1;

//static uint16_t SPI_TIMEOUT_UserCallback(uint8_t errorCode);

int SPI1_Init(void)
{
	__HAL_RCC_SPI1_CLK_ENABLE(); 

	hspi1.Instance = SPI1;
	hspi1.Init.Mode = SPI_MODE_MASTER;                        
	hspi1.Init.Direction = SPI_DIRECTION_2LINES;              
	hspi1.Init.DataSize = SPI_DATASIZE_8BIT;                  
	hspi1.Init.CLKPolarity = SPI_POLARITY_HIGH;               
	hspi1.Init.CLKPhase = SPI_PHASE_2EDGE;                    
	hspi1.Init.NSS = SPI_NSS_SOFT;                            
	hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8; 
	hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;                   
	hspi1.Init.TIMode = SPI_TIMODE_DISABLE;                   
	hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;   
	hspi1.Init.CRCPolynomial = 7;                             
	HAL_SPI_Init(&hspi1);                                     

	__HAL_SPI_ENABLE(&hspi1);
	
	return OPERATE_SUCCESS;
}

int Flash_Init(void)
{
	__HAL_RCC_GPIOB_CLK_ENABLE();
	
	GPIO_InitTypeDef gpio_init_struct;
  gpio_init_struct.Pin = GPIO_PIN_12;
  gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;
  gpio_init_struct.Pull = GPIO_PULLUP;
  gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &gpio_init_struct);
	
	SPI1_Init();
	
	return OPERATE_SUCCESS;
}

uint8_t Flash_Read_Write_Byte(uint8_t txdata)
{
    uint8_t rxdata;
    HAL_SPI_TransmitReceive(&hspi1, &txdata, &rxdata, 1, 1000);
    return rxdata;
}

uint8_t Flash_Read_SR(uint8_t regno)
{
    uint8_t byte = 0, command = 0;

    switch (regno)
    {
        case 1:
            command = FLASH_ReadStatusReg1;
            break;

        case 2:
            command = FLASH_ReadStatusReg2;
            break;

        case 3:
            command = FLASH_ReadStatusReg3;
            break;

        default:
            command = FLASH_ReadStatusReg1;
            break;
    }

    SPI_FLASH_CS_LOW();
    Flash_Read_Write_Byte(command);
    byte = Flash_Read_Write_Byte(0Xff);
    SPI_FLASH_CS_HIGH();
    
    return byte;
}

static void Flash_Wait_Busy(void)
{
    while ((Flash_Read_SR(1) & 0x01) == 0x01);
}

void Flash_Write_Enable(void)
{
    SPI_FLASH_CS_LOW();
    Flash_Read_Write_Byte(FLASH_WriteEnable);
    SPI_FLASH_CS_HIGH();
}

static void Flash_Send_Address(uint32_t address)
{
    Flash_Read_Write_Byte((uint8_t)((address)>>16));
    Flash_Read_Write_Byte((uint8_t)((address)>>8));
    Flash_Read_Write_Byte((uint8_t)address);
}

int Flash_Write_SR(uint8_t regno, uint8_t sr)
{
    uint8_t command = 0;

    switch (regno)
    {
        case 1:
            command = FLASH_WriteStatusReg1;
            break;

        case 2:
            command = FLASH_WriteStatusReg2;
            break;

        case 3:
            command = FLASH_WriteStatusReg3;
            break;

        default:
            command = FLASH_WriteStatusReg1;
            break;
    }

    SPI_FLASH_CS_LOW();
    Flash_Read_Write_Byte(command);
    Flash_Read_Write_Byte(sr);
    SPI_FLASH_CS_HIGH();
		
		return OPERATE_SUCCESS;
}

uint16_t Flash_Read_id(void)
{
    uint16_t deviceid;

    SPI_FLASH_CS_LOW();
    Flash_Read_Write_Byte(FLASH_ManufactDeviceID);
    Flash_Read_Write_Byte(0);
    Flash_Read_Write_Byte(0);
    Flash_Read_Write_Byte(0);
    deviceid = Flash_Read_Write_Byte(0xFF) << 8;
    deviceid |= Flash_Read_Write_Byte(0xFF);
    SPI_FLASH_CS_HIGH();

    return deviceid;
}

int Flash_read(uint8_t *pbuf, uint32_t addr, uint16_t datalen)
{
	uint16_t i;

	SPI_FLASH_CS_LOW();
	Flash_Read_Write_Byte(FLASH_ReadData);
	Flash_Send_Address(addr);
	
	for(i=0;i<datalen;i++)
	{
			pbuf[i] = Flash_Read_Write_Byte(0XFF);
	}
	
	SPI_FLASH_CS_HIGH();
	
	return OPERATE_SUCCESS;
}

static void Flash_Write_Page(uint8_t *pbuf, uint32_t addr, uint16_t datalen)
{
    uint16_t i;

    Flash_Write_Enable();

    SPI_FLASH_CS_LOW();
    Flash_Read_Write_Byte(FLASH_PageProgram);
    Flash_Send_Address(addr);

    for(i=0;i<datalen;i++)
    {
        Flash_Read_Write_Byte(pbuf[i]);
    }
    
    SPI_FLASH_CS_HIGH();
    Flash_Wait_Busy();
}

static void Flash_Write_nocheck(uint8_t *pbuf, uint32_t addr, uint16_t datalen)
{
    uint16_t pageremain;
    pageremain = 256 - addr % 256;

    if (datalen <= pageremain)
    {
        pageremain = datalen;
    }

    while (1)
    {
        Flash_Write_Page(pbuf, addr, pageremain);

        if (datalen == pageremain)
        {
            break;
        }
        else
        {
            pbuf += pageremain;
            addr += pageremain;
            datalen -= pageremain;

            if (datalen > 256)
            {
                pageremain = 256;
            }
            else
            {
                pageremain = datalen;
            }
        }
    }
}

uint8_t g_norflash_buf[4096];

int Flash_write(uint8_t *pbuf, uint32_t addr, uint16_t datalen)
{
	uint32_t secpos;
	uint16_t secoff;
	uint16_t secremain;
	uint16_t i;
	uint8_t *norflash_buf;

	norflash_buf = g_norflash_buf;
	secpos = addr / 4096;
	secoff = addr % 4096;
	secremain = 4096 - secoff;
	if (datalen <= secremain)
	{
			secremain = datalen;    /* 不大于4096个字节 */
	}

	while (1)
	{
			Flash_read(norflash_buf, secpos * 4096, 4096);   /* 读出整个扇区的内容 */

			for (i = 0; i < secremain; i++)   /* 校验数据 */
			{
					if (norflash_buf[secoff + i] != 0XFF)
					{
							break;      /* 需要擦除, 直接退出for循环 */
					}
			}

			if (i < secremain)   /* 需要擦除 */
			{
					Flash_Erase_Sector(secpos);  /* 擦除这个扇区 */

					for (i = 0; i < secremain; i++)   /* 复制 */
					{
							norflash_buf[i + secoff] = pbuf[i];
					}

					Flash_Write_nocheck(norflash_buf, secpos * 4096, 4096);  /* 写入整个扇区 */
			}
			else        /* 写已经擦除了的,直接写入扇区剩余区间. */
			{
					Flash_Write_nocheck(pbuf, addr, secremain);  /* 直接写扇区 */
			}

			if (datalen == secremain)
			{
					break;  /* 写入结束了 */
			}
			else        /* 写入未结束 */
			{
					secpos++;               /* 扇区地址增1 */
					secoff = 0;             /* 偏移位置为0 */

					pbuf += secremain;      /* 指针偏移 */
					addr += secremain;      /* 写地址偏移 */
					datalen -= secremain;   /* 字节数递减 */

					if (datalen > 4096)
					{
							secremain = 4096;   /* 下一个扇区还是写不完 */
					}
					else
					{
							secremain = datalen;/* 下一个扇区可以写完了 */
					}
			}
	}
	return OPERATE_SUCCESS;
}

/**
 * @brief       擦除整个芯片
 *   @note      等待时间超长...
 * @param       无
 * @retval      无
 */
int Flash_Erase_Chip(void)
{
	Flash_Write_Enable();
	Flash_Wait_Busy();
	SPI_FLASH_CS_LOW();
	Flash_Read_Write_Byte(FLASH_ChipErase);
	SPI_FLASH_CS_HIGH();
	Flash_Wait_Busy();
}

int Flash_Erase_Sector(uint32_t saddr)
{
	saddr *= 4096;
	Flash_Write_Enable();
	Flash_Wait_Busy();

	SPI_FLASH_CS_LOW();
	Flash_Read_Write_Byte(FLASH_SectorErase);
	Flash_Send_Address(saddr);
	SPI_FLASH_CS_HIGH();
	Flash_Wait_Busy();
	
	return OPERATE_SUCCESS;
}


int Flash_Read_DMA(uint8_t *pbuf, uint32_t addr, uint16_t datalen)
{
	SPI_FLASH_CS_LOW();
	Flash_Read_Write_Byte(FLASH_ReadData);
  Flash_Send_Address(addr);
	HAL_SPI_Receive_DMA(&hspi1,pbuf,datalen);
	//delay_ms(1000);
	//SPI_FLASH_CS_HIGH();	//dma传输完成后拉高片选
	return OPERATE_SUCCESS;
}

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
{
	if(hspi->Instance == SPI1)
	{
		SPI_FLASH_CS_HIGH();
		printf("spi dma rec ok\r\n");
	}
}
