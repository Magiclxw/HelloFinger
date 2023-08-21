#include "..\USER\driver\W25Q128\drv_w25q128.h"

DMA_HandleTypeDef hdma_spi1;
SPI_HandleTypeDef hspi1;

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



uint8_t SPI1_Read_Write_Byte(uint8_t txdata)
{
    uint8_t rxdata;
    HAL_SPI_TransmitReceive(&hspi1, &txdata, &rxdata, 1, 1000);
    return rxdata;
}

static void Flas_Wait_Busy(void)
{
    while ((Flash_Read_SR(1) & 0x01) == 0x01);   /* �ȴ�BUSYλ��� */
}

uint16_t Flash_Read_id(void)
{
    uint16_t deviceid;

    FLASH_CS_LOW;
    SPI1_Read_Write_Byte(FLASH_ManufactDeviceID);   /* ���Ͷ� ID ���� */
    SPI1_Read_Write_Byte(0);    /* д��һ���ֽ� */
    SPI1_Read_Write_Byte(0);
    SPI1_Read_Write_Byte(0);
    deviceid = SPI1_Read_Write_Byte(0xFF) << 8;     /* ��ȡ��8λ�ֽ� */
    deviceid |= SPI1_Read_Write_Byte(0xFF);         /* ��ȡ��8λ�ֽ� */
    FLASH_CS_HIGH;

    return deviceid;
}

/**
 * @brief       25QXXдʹ��
 *   @note      ��S1�Ĵ�����WEL��λ
 * @param       ��
 * @retval      ��
 */
void Flash_Write_Enable(void)
{
    FLASH_CS_LOW;
    SPI1_Read_Write_Byte(FLASH_WriteEnable);   /* ����дʹ�� */
    FLASH_CS_HIGH;
}

/**
 * @brief       25QXX���͵�ַ
 *   @note      ����оƬ�ͺŵĲ�ͬ, ����24ibt / 32bit��ַ
 * @param       address : Ҫ���͵ĵ�ַ
 * @retval      ��
 */
static void Flash_Send_Address(uint32_t address)
{
    SPI1_Read_Write_Byte((uint8_t)((address)>>16));     /* ���� bit23 ~ bit16 ��ַ */
    SPI1_Read_Write_Byte((uint8_t)((address)>>8));      /* ���� bit15 ~ bit8  ��ַ */
    SPI1_Read_Write_Byte((uint8_t)address);             /* ���� bit7  ~ bit0  ��ַ */
}

/**
 * @brief       ��ȡ25QXX��״̬�Ĵ�����25QXXһ����3��״̬�Ĵ���
 *   @note      ״̬�Ĵ���1��
 *              BIT7  6   5   4   3   2   1   0
 *              SPR   RV  TB BP2 BP1 BP0 WEL BUSY
 *              SPR:Ĭ��0,״̬�Ĵ�������λ,���WPʹ��
 *              TB,BP2,BP1,BP0:FLASH����д��������
 *              WEL:дʹ������
 *              BUSY:æ���λ(1,æ;0,����)
 *              Ĭ��:0x00
 *
 *              ״̬�Ĵ���2��
 *              BIT7  6   5   4   3   2   1   0
 *              SUS   CMP LB3 LB2 LB1 (R) QE  SRP1
 *
 *              ״̬�Ĵ���3��
 *              BIT7      6    5    4   3   2   1   0
 *              HOLD/RST  DRV1 DRV0 (R) (R) WPS ADP ADS
 *
 * @param       regno: ״̬�Ĵ����ţ���Χ:1~3
 * @retval      ״̬�Ĵ���ֵ
 */
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

    FLASH_CS_LOW;
    SPI1_Read_Write_Byte(command);      /* ���Ͷ��Ĵ������� */
    byte = SPI1_Read_Write_Byte(0Xff);  /* ��ȡһ���ֽ� */
    FLASH_CS_HIGH;
    
    return byte;
}

/**
 * @brief       д25QXX״̬�Ĵ���
 *   @note      �Ĵ���˵����norflash_read_sr����˵��
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

    FLASH_CS_LOW;
    SPI1_Read_Write_Byte(command);  /* ���Ͷ��Ĵ������� */
    SPI1_Read_Write_Byte(sr);       /* д��һ���ֽ� */
    FLASH_CS_HIGH;
}


/**
 * @brief       ��ȡSPI FLASH
 *   @note      ��ָ����ַ��ʼ��ȡָ�����ȵ�����
 * @param       pbuf    : ���ݴ洢��
 * @param       addr    : ��ʼ��ȡ�ĵ�ַ(���32bit)
 * @param       datalen : Ҫ��ȡ���ֽ���(���65535)
 * @retval      ��
 */
void Flash_Read(uint8_t *pbuf, uint32_t addr, uint16_t datalen)
{
    uint16_t i;

    FLASH_CS_LOW;
    SPI1_Read_Write_Byte(FLASH_ReadData);
    Flash_Send_Address(addr);
    
    for(i=0;i<datalen;i++)
    {
        pbuf[i] = SPI1_Read_Write_Byte(0XFF);   /* ѭ����ȡ */
    }
    
    FLASH_CS_HIGH;
}

void Flash_Read_DMA(uint8_t *pbuf, uint32_t addr, uint16_t datalen)
{
	FLASH_CS_LOW;
	SPI1_Read_Write_Byte(FLASH_ReadData);
  Flash_Send_Address(addr);
	HAL_SPI_Receive_DMA(&hspi1,pbuf,datalen);
	FLASH_CS_HIGH;
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

    FLASH_CS_LOW;
    SPI1_Read_Write_Byte(FLASH_PageProgram);    /* ����дҳ���� */
    Flash_Send_Address(addr);                /* ���͵�ַ */

    for(i=0;i<datalen;i++)
    {
        SPI1_Read_Write_Byte(pbuf[i]);          /* ѭ��д�� */
    }
    
    FLASH_CS_HIGH;
    Flas_Wait_Busy();       /* �ȴ�д����� */
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

void Flash_Write(uint8_t *pbuf, uint32_t addr, uint16_t datalen)
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
        Flash_Read(norflash_buf, secpos * 4096, 4096);   /* ������������������ */

        for (i = 0; i < secremain; i++)   /* У������ */
        {
            if (norflash_buf[secoff + i] != 0XFF)
            {
                break;      /* ��Ҫ����, ֱ���˳�forѭ�� */
            }
        }

        if (i < secremain)   /* ��Ҫ���� */
        {
            Flash_Sector_Erase(secpos);  /* ����������� */

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
void Flash_Chip_Erase(void)
{
    Flash_Write_Enable();    /* дʹ�� */
    Flas_Wait_Busy();       /* �ȴ����� */
    FLASH_CS_LOW;
    SPI1_Read_Write_Byte(FLASH_ChipErase);  /* ���Ͷ��Ĵ������� */ 
    FLASH_CS_HIGH;
    Flas_Wait_Busy();       /* �ȴ�оƬ�������� */
}

/**
 * @brief       ����һ������
 *   @note      ע��,������������ַ,�����ֽڵ�ַ!!
 *              ����һ������������ʱ��:150ms
 *
 * @param       saddr : ������ַ ����ʵ����������
 * @retval      ��
 */
void Flash_Sector_Erase(uint32_t saddr)
{
    //printf("fe:%x\r\n", saddr);   /* ����falsh�������,������ */
    saddr *= 4096;
    Flash_Write_Enable();        /* дʹ�� */
    Flas_Wait_Busy();           /* �ȴ����� */

    FLASH_CS_LOW;
    SPI1_Read_Write_Byte(FLASH_SectorErase);    /* ����дҳ���� */
    Flash_Send_Address(saddr);   /* ���͵�ַ */
    FLASH_CS_HIGH;
    Flas_Wait_Busy();           /* �ȴ������������ */
}



















