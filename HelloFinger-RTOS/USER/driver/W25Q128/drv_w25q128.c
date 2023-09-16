#include "..\USER\driver\W25Q128\drv_w25q128.h"

DMA_HandleTypeDef hdma_spi1;
SPI_HandleTypeDef hspi1;

static __IO uint32_t  SPITimeout = SPIT_LONG_TIMEOUT;   

static uint16_t SPI_TIMEOUT_UserCallback(uint8_t errorCode);

void SPI1_Init(void)
{
    __HAL_RCC_SPI1_CLK_ENABLE(); 

    hspi1.Instance = SPI1;
    hspi1.Init.Mode = SPI_MODE_MASTER;                        
    hspi1.Init.Direction = SPI_DIRECTION_2LINES;              
    hspi1.Init.DataSize = SPI_DATASIZE_8BIT;                  
    hspi1.Init.CLKPolarity = SPI_POLARITY_HIGH;               
    hspi1.Init.CLKPhase = SPI_PHASE_2EDGE;                    
    hspi1.Init.NSS = SPI_NSS_SOFT;                            
    hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256; 
    hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;                   
    hspi1.Init.TIMode = SPI_TIMODE_DISABLE;                   
    hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;   
    hspi1.Init.CRCPolynomial = 7;                             
    HAL_SPI_Init(&hspi1);                                     

    __HAL_SPI_ENABLE(&hspi1); /* ʹ��SPI2 */
}

void Flash_Init(void)
{
	__HAL_RCC_GPIOB_CLK_ENABLE();
	
	GPIO_InitTypeDef gpio_init_struct;
  gpio_init_struct.Pin = GPIO_PIN_12;
  gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;
  gpio_init_struct.Pull = GPIO_PULLUP;
  gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &gpio_init_struct);
	
	hdma_spi1.Instance = DMA1_Channel2;
	hdma_spi1.Init.Direction = DMA_PERIPH_TO_MEMORY;
	hdma_spi1.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	hdma_spi1.Init.MemInc = DMA_MINC_ENABLE;
	hdma_spi1.Init.Mode = DMA_CIRCULAR;
	hdma_spi1.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	hdma_spi1.Init.PeriphInc = DMA_PINC_DISABLE;
	hdma_spi1.Init.Priority = DMA_PRIORITY_LOW;
	
	SPI1_Init();
}

uint8_t Flash_Read_Write_Byte(uint8_t txdata)
{
    uint8_t rxdata;
    HAL_SPI_TransmitReceive(&hspi1, &txdata, &rxdata, 1, 1000);
    return rxdata; /* �����յ������� */
}

uint8_t Flash_Read_SR(uint8_t regno)
{
    uint8_t byte = 0, command = 0;

    switch (regno)
    {
        case 1:
            command = FLASH_ReadStatusReg1;  /* ��״̬�Ĵ���1ָ�� */
            break;

        case 2:
            command = FLASH_ReadStatusReg2;  /* ��״̬�Ĵ���2ָ�� */
            break;

        case 3:
            command = FLASH_ReadStatusReg3;  /* ��״̬�Ĵ���3ָ�� */
            break;

        default:
            command = FLASH_ReadStatusReg1;
            break;
    }

    SPI_FLASH_CS_LOW();
    Flash_Read_Write_Byte(command);      /* ���Ͷ��Ĵ������� */
    byte = Flash_Read_Write_Byte(0Xff);  /* ��ȡһ���ֽ� */
    SPI_FLASH_CS_HIGH();
    
    return byte;
}

/**
 * @brief       �ȴ�����
 * @param       ��
 * @retval      ��
 */
static void Flash_Wait_Busy(void)
{
    while ((Flash_Read_SR(1) & 0x01) == 0x01);   /* �ȴ�BUSYλ��� */
}

/**
 * @brief       25QXXдʹ��
 *   @note      ��S1�Ĵ�����WEL��λ
 * @param       ��
 * @retval      ��
 */
void Flash_Write_Enable(void)
{
    SPI_FLASH_CS_LOW();
    Flash_Read_Write_Byte(FLASH_WriteEnable);   /* ����дʹ�� */
    SPI_FLASH_CS_HIGH();
}

/**
 * @brief       25QXX���͵�ַ
 *   @note      ����оƬ�ͺŵĲ�ͬ, ����24ibt / 32bit��ַ
 * @param       address : Ҫ���͵ĵ�ַ
 * @retval      ��
 */
static void Flash_Send_Address(uint32_t address)
{
    Flash_Read_Write_Byte((uint8_t)((address)>>16));     /* ���� bit23 ~ bit16 ��ַ */
    Flash_Read_Write_Byte((uint8_t)((address)>>8));      /* ���� bit15 ~ bit8  ��ַ */
    Flash_Read_Write_Byte((uint8_t)address);             /* ���� bit7  ~ bit0  ��ַ */
}


/**
 * @brief       д25QXX״̬�Ĵ���
 *   @note      �Ĵ���˵����Flash_read_sr����˵��
 * @param       regno: ״̬�Ĵ����ţ���Χ:1~3
 * @param       sr   : Ҫд��״̬�Ĵ�����ֵ
 * @retval      ��
 */
void Flash_Write_SR(uint8_t regno, uint8_t sr)
{
    uint8_t command = 0;

    switch (regno)
    {
        case 1:
            command = FLASH_WriteStatusReg1;  /* д״̬�Ĵ���1ָ�� */
            break;

        case 2:
            command = FLASH_WriteStatusReg2;  /* д״̬�Ĵ���2ָ�� */
            break;

        case 3:
            command = FLASH_WriteStatusReg3;  /* д״̬�Ĵ���3ָ�� */
            break;

        default:
            command = FLASH_WriteStatusReg1;
            break;
    }

    SPI_FLASH_CS_LOW();
    Flash_Read_Write_Byte(command);  /* ���Ͷ��Ĵ������� */
    Flash_Read_Write_Byte(sr);       /* д��һ���ֽ� */
    SPI_FLASH_CS_HIGH();
}

/**
 * @brief       ��ȡоƬID
 * @param       ��
 * @retval      FLASHоƬID
 *   @note      оƬID�б��: norflash.h, оƬ�б���
 */
uint16_t Flash_Read_id(void)
{
    uint16_t deviceid;

    SPI_FLASH_CS_LOW();
    Flash_Read_Write_Byte(FLASH_ManufactDeviceID);   /* ���Ͷ� ID ���� */
    Flash_Read_Write_Byte(0);    /* д��һ���ֽ� */
    Flash_Read_Write_Byte(0);
    Flash_Read_Write_Byte(0);
    deviceid = Flash_Read_Write_Byte(0xFF) << 8;     /* ��ȡ��8λ�ֽ� */
    deviceid |= Flash_Read_Write_Byte(0xFF);         /* ��ȡ��8λ�ֽ� */
    SPI_FLASH_CS_HIGH();

    return deviceid;
}

/**
 * @brief       ��ȡSPI FLASH
 *   @note      ��ָ����ַ��ʼ��ȡָ�����ȵ�����
 * @param       pbuf    : ���ݴ洢��
 * @param       addr    : ��ʼ��ȡ�ĵ�ַ(���32bit)
 * @param       datalen : Ҫ��ȡ���ֽ���(���65535)
 * @retval      ��
 */
void Flash_read(uint8_t *pbuf, uint32_t addr, uint16_t datalen)
{
    uint16_t i;

    SPI_FLASH_CS_LOW();
    Flash_Read_Write_Byte(FLASH_ReadData);       /* ���Ͷ�ȡ���� */
    Flash_Send_Address(addr);                /* ���͵�ַ */
    
    for(i=0;i<datalen;i++)
    {
        pbuf[i] = Flash_Read_Write_Byte(0XFF);   /* ѭ����ȡ */
    }
    
    SPI_FLASH_CS_HIGH();
}

/**
 * @brief       SPI��һҳ(0~65535)��д������256���ֽڵ�����
 *   @note      ��ָ����ַ��ʼд�����256�ֽڵ�����
 * @param       pbuf    : ���ݴ洢��
 * @param       addr    : ��ʼд��ĵ�ַ(���32bit)
 * @param       datalen : Ҫд����ֽ���(���256),������Ӧ�ó�����ҳ��ʣ���ֽ���!!!
 * @retval      ��
 */
static void Flash_Write_Page(uint8_t *pbuf, uint32_t addr, uint16_t datalen)
{
    uint16_t i;

    Flash_Write_Enable();    /* дʹ�� */

    SPI_FLASH_CS_LOW();
    Flash_Read_Write_Byte(FLASH_PageProgram);    /* ����дҳ���� */
    Flash_Send_Address(addr);                /* ���͵�ַ */

    for(i=0;i<datalen;i++)
    {
        Flash_Read_Write_Byte(pbuf[i]);          /* ѭ��д�� */
    }
    
    SPI_FLASH_CS_HIGH();
    Flash_Wait_Busy();       /* �ȴ�д����� */
}

/**
 * @brief       �޼���дSPI FLASH
 *   @note      ����ȷ����д�ĵ�ַ��Χ�ڵ�����ȫ��Ϊ0XFF,�����ڷ�0XFF��д������ݽ�ʧ��!
 *              �����Զ���ҳ����
 *              ��ָ����ַ��ʼд��ָ�����ȵ�����,����Ҫȷ����ַ��Խ��!
 *
 * @param       pbuf    : ���ݴ洢��
 * @param       addr    : ��ʼд��ĵ�ַ(���32bit)
 * @param       datalen : Ҫд����ֽ���(���65535)
 * @retval      ��
 */
static void Flash_Write_nocheck(uint8_t *pbuf, uint32_t addr, uint16_t datalen)
{
    uint16_t pageremain;
    pageremain = 256 - addr % 256;  /* ��ҳʣ����ֽ��� */

    if (datalen <= pageremain)      /* ������256���ֽ� */
    {
        pageremain = datalen;
    }

    while (1)
    {
        /* ��д���ֽڱ�ҳ��ʣ���ַ���ٵ�ʱ��, һ����д��
         * ��д��ֱ�ӱ�ҳ��ʣ���ַ�����ʱ��, ��д������ҳ��ʣ���ַ, Ȼ�����ʣ�೤�Ƚ��в�ͬ����
         */
        Flash_Write_Page(pbuf, addr, pageremain);

        if (datalen == pageremain)   /* д������� */
        {
            break;
        }
        else     /* datalen > pageremain */
        {
            pbuf += pageremain;         /* pbufָ���ַƫ��,ǰ���Ѿ�д��pageremain�ֽ� */
            addr += pageremain;         /* д��ַƫ��,ǰ���Ѿ�д��pageremain�ֽ� */
            datalen -= pageremain;      /* д���ܳ��ȼ�ȥ�Ѿ�д���˵��ֽ��� */

            if (datalen > 256)          /* ʣ�����ݻ�����һҳ,����һ��дһҳ */
            {
                pageremain = 256;       /* һ�ο���д��256���ֽ� */
            }
            else     /* ʣ������С��һҳ,����һ��д�� */
            {
                pageremain = datalen;   /* ����256���ֽ��� */
            }
        }
    }
}

/**
 * @brief       дSPI FLASH
 *   @note      ��ָ����ַ��ʼд��ָ�����ȵ����� , �ú�������������!
 *              SPI FLASH һ����: 256���ֽ�Ϊһ��Page, 4KbytesΪһ��Sector, 16������Ϊ1��Block
 *              ��������С��λΪSector.
 *
 * @param       pbuf    : ���ݴ洢��
 * @param       addr    : ��ʼд��ĵ�ַ(���32bit)
 * @param       datalen : Ҫд����ֽ���(���65535)
 * @retval      ��
 */
uint8_t g_norflash_buf[4096];   /* �������� */

void Flash_write(uint8_t *pbuf, uint32_t addr, uint16_t datalen)
{
    uint32_t secpos;
    uint16_t secoff;
    uint16_t secremain;
    uint16_t i;
    uint8_t *norflash_buf;

    norflash_buf = g_norflash_buf;
    secpos = addr / 4096;       /* ������ַ */
    secoff = addr % 4096;       /* �������ڵ�ƫ�� */
    secremain = 4096 - secoff;  /* ����ʣ��ռ��С */

    //printf("ad:%X,nb:%X\r\n", addr, datalen); /* ������ */
    if (datalen <= secremain)
    {
        secremain = datalen;    /* ������4096���ֽ� */
    }

    while (1)
    {
        Flash_read(norflash_buf, secpos * 4096, 4096);   /* ������������������ */

        for (i = 0; i < secremain; i++)   /* У������ */
        {
            if (norflash_buf[secoff + i] != 0XFF)
            {
                break;      /* ��Ҫ����, ֱ���˳�forѭ�� */
            }
        }

        if (i < secremain)   /* ��Ҫ���� */
        {
            Flash_Erase_Sector(secpos);  /* ����������� */

            for (i = 0; i < secremain; i++)   /* ���� */
            {
                norflash_buf[i + secoff] = pbuf[i];
            }

            Flash_Write_nocheck(norflash_buf, secpos * 4096, 4096);  /* д���������� */
        }
        else        /* д�Ѿ������˵�,ֱ��д������ʣ������. */
        {
            Flash_Write_nocheck(pbuf, addr, secremain);  /* ֱ��д���� */
        }

        if (datalen == secremain)
        {
            break;  /* д������� */
        }
        else        /* д��δ���� */
        {
            secpos++;               /* ������ַ��1 */
            secoff = 0;             /* ƫ��λ��Ϊ0 */

            pbuf += secremain;      /* ָ��ƫ�� */
            addr += secremain;      /* д��ַƫ�� */
            datalen -= secremain;   /* �ֽ����ݼ� */

            if (datalen > 4096)
            {
                secremain = 4096;   /* ��һ����������д���� */
            }
            else
            {
                secremain = datalen;/* ��һ����������д���� */
            }
        }
    }
}

/**
 * @brief       ��������оƬ
 *   @note      �ȴ�ʱ�䳬��...
 * @param       ��
 * @retval      ��
 */
void Flash_Erase_Chip(void)
{
    Flash_Write_Enable();    /* дʹ�� */
    Flash_Wait_Busy();       /* �ȴ����� */
    SPI_FLASH_CS_LOW();
    Flash_Read_Write_Byte(FLASH_ChipErase);  /* ���Ͷ��Ĵ������� */ 
    SPI_FLASH_CS_HIGH();
    Flash_Wait_Busy();       /* �ȴ�оƬ�������� */
}

/**
 * @brief       ����һ������
 *   @note      ע��,������������ַ,�����ֽڵ�ַ!!
 *              ����һ������������ʱ��:150ms
 *
 * @param       saddr : ������ַ ����ʵ����������
 * @retval      ��
 */
void Flash_Erase_Sector(uint32_t saddr)
{
    //printf("fe:%x\r\n", saddr);   /* ����falsh�������,������ */
    saddr *= 4096;
    Flash_Write_Enable();        /* дʹ�� */
    Flash_Wait_Busy();           /* �ȴ����� */

    SPI_FLASH_CS_LOW();
    Flash_Read_Write_Byte(FLASH_SectorErase);    /* ����дҳ���� */
    Flash_Send_Address(saddr);   /* ���͵�ַ */
    SPI_FLASH_CS_HIGH();
    Flash_Wait_Busy();           /* �ȴ������������ */
}


void Flash_Read_DMA(uint8_t *pbuf, uint32_t addr, uint16_t datalen)
{
	//SPI_FLASH_CS_LOW();
  Flash_Read_Write_Byte(addr);
	HAL_SPI_Receive_DMA(&hspi1,pbuf,datalen);
	SPI_FLASH_CS_HIGH();
}


