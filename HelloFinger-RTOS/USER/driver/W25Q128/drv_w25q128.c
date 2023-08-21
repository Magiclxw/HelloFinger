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

    __HAL_SPI_ENABLE(&hspi1); /* 使能SPI2 */
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
    while ((Flash_Read_SR(1) & 0x01) == 0x01);   /* 等待BUSY位清空 */
}

uint16_t Flash_Read_id(void)
{
    uint16_t deviceid;

    FLASH_CS_LOW;
    SPI1_Read_Write_Byte(FLASH_ManufactDeviceID);   /* 发送读 ID 命令 */
    SPI1_Read_Write_Byte(0);    /* 写入一个字节 */
    SPI1_Read_Write_Byte(0);
    SPI1_Read_Write_Byte(0);
    deviceid = SPI1_Read_Write_Byte(0xFF) << 8;     /* 读取高8位字节 */
    deviceid |= SPI1_Read_Write_Byte(0xFF);         /* 读取低8位字节 */
    FLASH_CS_HIGH;

    return deviceid;
}

/**
 * @brief       25QXX写使能
 *   @note      将S1寄存器的WEL置位
 * @param       无
 * @retval      无
 */
void Flash_Write_Enable(void)
{
    FLASH_CS_LOW;
    SPI1_Read_Write_Byte(FLASH_WriteEnable);   /* 发送写使能 */
    FLASH_CS_HIGH;
}

/**
 * @brief       25QXX发送地址
 *   @note      根据芯片型号的不同, 发送24ibt / 32bit地址
 * @param       address : 要发送的地址
 * @retval      无
 */
static void Flash_Send_Address(uint32_t address)
{
    SPI1_Read_Write_Byte((uint8_t)((address)>>16));     /* 发送 bit23 ~ bit16 地址 */
    SPI1_Read_Write_Byte((uint8_t)((address)>>8));      /* 发送 bit15 ~ bit8  地址 */
    SPI1_Read_Write_Byte((uint8_t)address);             /* 发送 bit7  ~ bit0  地址 */
}

/**
 * @brief       读取25QXX的状态寄存器，25QXX一共有3个状态寄存器
 *   @note      状态寄存器1：
 *              BIT7  6   5   4   3   2   1   0
 *              SPR   RV  TB BP2 BP1 BP0 WEL BUSY
 *              SPR:默认0,状态寄存器保护位,配合WP使用
 *              TB,BP2,BP1,BP0:FLASH区域写保护设置
 *              WEL:写使能锁定
 *              BUSY:忙标记位(1,忙;0,空闲)
 *              默认:0x00
 *
 *              状态寄存器2：
 *              BIT7  6   5   4   3   2   1   0
 *              SUS   CMP LB3 LB2 LB1 (R) QE  SRP1
 *
 *              状态寄存器3：
 *              BIT7      6    5    4   3   2   1   0
 *              HOLD/RST  DRV1 DRV0 (R) (R) WPS ADP ADS
 *
 * @param       regno: 状态寄存器号，范围:1~3
 * @retval      状态寄存器值
 */
uint8_t Flash_Read_SR(uint8_t regno)
{
    uint8_t byte = 0, command = 0;

    switch (regno)
    {
        case 1:
            command = FLASH_ReadStatusReg1;  /* 读状态寄存器1指令 */
            break;

        case 2:
            command = FLASH_ReadStatusReg2;  /* 读状态寄存器2指令 */
            break;

        case 3:
            command = FLASH_ReadStatusReg3;  /* 读状态寄存器3指令 */
            break;

        default:
            command = FLASH_ReadStatusReg1;
            break;
    }

    FLASH_CS_LOW;
    SPI1_Read_Write_Byte(command);      /* 发送读寄存器命令 */
    byte = SPI1_Read_Write_Byte(0Xff);  /* 读取一个字节 */
    FLASH_CS_HIGH;
    
    return byte;
}

/**
 * @brief       写25QXX状态寄存器
 *   @note      寄存器说明见norflash_read_sr函数说明
 * @param       regno: 状态寄存器号，范围:1~3
 * @param       sr   : 要写入状态寄存器的值
 * @retval      无
 */
void Flash_Write_SR(uint8_t regno, uint8_t sr)
{
    uint8_t command = 0;

    switch (regno)
    {
        case 1:
            command = FLASH_WriteStatusReg1;  /* 写状态寄存器1指令 */
            break;

        case 2:
            command = FLASH_WriteStatusReg2;  /* 写状态寄存器2指令 */
            break;

        case 3:
            command = FLASH_WriteStatusReg3;  /* 写状态寄存器3指令 */
            break;

        default:
            command = FLASH_WriteStatusReg1;
            break;
    }

    FLASH_CS_LOW;
    SPI1_Read_Write_Byte(command);  /* 发送读寄存器命令 */
    SPI1_Read_Write_Byte(sr);       /* 写入一个字节 */
    FLASH_CS_HIGH;
}


/**
 * @brief       读取SPI FLASH
 *   @note      在指定地址开始读取指定长度的数据
 * @param       pbuf    : 数据存储区
 * @param       addr    : 开始读取的地址(最大32bit)
 * @param       datalen : 要读取的字节数(最大65535)
 * @retval      无
 */
void Flash_Read(uint8_t *pbuf, uint32_t addr, uint16_t datalen)
{
    uint16_t i;

    FLASH_CS_LOW;
    SPI1_Read_Write_Byte(FLASH_ReadData);
    Flash_Send_Address(addr);
    
    for(i=0;i<datalen;i++)
    {
        pbuf[i] = SPI1_Read_Write_Byte(0XFF);   /* 循环读取 */
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
 * @brief       SPI在一页(0~65535)内写入少于256个字节的数据
 *   @note      在指定地址开始写入最大256字节的数据
 * @param       pbuf    : 数据存储区
 * @param       addr    : 开始写入的地址(最大32bit)
 * @param       datalen : 要写入的字节数(最大256),该数不应该超过该页的剩余字节数!!!
 * @retval      无
 */
static void Flash_Write_Page(uint8_t *pbuf, uint32_t addr, uint16_t datalen)
{
    uint16_t i;

    Flash_Write_Enable();    /* 写使能 */

    FLASH_CS_LOW;
    SPI1_Read_Write_Byte(FLASH_PageProgram);    /* 发送写页命令 */
    Flash_Send_Address(addr);                /* 发送地址 */

    for(i=0;i<datalen;i++)
    {
        SPI1_Read_Write_Byte(pbuf[i]);          /* 循环写入 */
    }
    
    FLASH_CS_HIGH;
    Flas_Wait_Busy();       /* 等待写入结束 */
}

/**
 * @brief       无检验写SPI FLASH
 *   @note      必须确保所写的地址范围内的数据全部为0XFF,否则在非0XFF处写入的数据将失败!
 *              具有自动换页功能
 *              在指定地址开始写入指定长度的数据,但是要确保地址不越界!
 *
 * @param       pbuf    : 数据存储区
 * @param       addr    : 开始写入的地址(最大32bit)
 * @param       datalen : 要写入的字节数(最大65535)
 * @retval      无
 */
static void Flash_Write_nocheck(uint8_t *pbuf, uint32_t addr, uint16_t datalen)
{
    uint16_t pageremain;
    pageremain = 256 - addr % 256;  /* 单页剩余的字节数 */

    if (datalen <= pageremain)      /* 不大于256个字节 */
    {
        pageremain = datalen;
    }

    while (1)
    {
        /* 当写入字节比页内剩余地址还少的时候, 一次性写完
         * 当写入直接比页内剩余地址还多的时候, 先写完整个页内剩余地址, 然后根据剩余长度进行不同处理
         */
        Flash_Write_Page(pbuf, addr, pageremain);

        if (datalen == pageremain)   /* 写入结束了 */
        {
            break;
        }
        else     /* datalen > pageremain */
        {
            pbuf += pageremain;         /* pbuf指针地址偏移,前面已经写了pageremain字节 */
            addr += pageremain;         /* 写地址偏移,前面已经写了pageremain字节 */
            datalen -= pageremain;      /* 写入总长度减去已经写入了的字节数 */

            if (datalen > 256)          /* 剩余数据还大于一页,可以一次写一页 */
            {
                pageremain = 256;       /* 一次可以写入256个字节 */
            }
            else     /* 剩余数据小于一页,可以一次写完 */
            {
                pageremain = datalen;   /* 不够256个字节了 */
            }
        }
    }
}

/**
 * @brief       写SPI FLASH
 *   @note      在指定地址开始写入指定长度的数据 , 该函数带擦除操作!
 *              SPI FLASH 一般是: 256个字节为一个Page, 4Kbytes为一个Sector, 16个扇区为1个Block
 *              擦除的最小单位为Sector.
 *
 * @param       pbuf    : 数据存储区
 * @param       addr    : 开始写入的地址(最大32bit)
 * @param       datalen : 要写入的字节数(最大65535)
 * @retval      无
 */
uint8_t g_norflash_buf[4096];   /* 扇区缓存 */

void Flash_Write(uint8_t *pbuf, uint32_t addr, uint16_t datalen)
{
    uint32_t secpos;
    uint16_t secoff;
    uint16_t secremain;
    uint16_t i;
    uint8_t *norflash_buf;

    norflash_buf = g_norflash_buf;
    secpos = addr / 4096;       /* 扇区地址 */
    secoff = addr % 4096;       /* 在扇区内的偏移 */
    secremain = 4096 - secoff;  /* 扇区剩余空间大小 */

    //printf("ad:%X,nb:%X\r\n", addr, datalen); /* 测试用 */
    if (datalen <= secremain)
    {
        secremain = datalen;    /* 不大于4096个字节 */
    }

    while (1)
    {
        Flash_Read(norflash_buf, secpos * 4096, 4096);   /* 读出整个扇区的内容 */

        for (i = 0; i < secremain; i++)   /* 校验数据 */
        {
            if (norflash_buf[secoff + i] != 0XFF)
            {
                break;      /* 需要擦除, 直接退出for循环 */
            }
        }

        if (i < secremain)   /* 需要擦除 */
        {
            Flash_Sector_Erase(secpos);  /* 擦除这个扇区 */

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
}

/**
 * @brief       擦除整个芯片
 *   @note      等待时间超长...
 * @param       无
 * @retval      无
 */
void Flash_Chip_Erase(void)
{
    Flash_Write_Enable();    /* 写使能 */
    Flas_Wait_Busy();       /* 等待空闲 */
    FLASH_CS_LOW;
    SPI1_Read_Write_Byte(FLASH_ChipErase);  /* 发送读寄存器命令 */ 
    FLASH_CS_HIGH;
    Flas_Wait_Busy();       /* 等待芯片擦除结束 */
}

/**
 * @brief       擦除一个扇区
 *   @note      注意,这里是扇区地址,不是字节地址!!
 *              擦除一个扇区的最少时间:150ms
 *
 * @param       saddr : 扇区地址 根据实际容量设置
 * @retval      无
 */
void Flash_Sector_Erase(uint32_t saddr)
{
    //printf("fe:%x\r\n", saddr);   /* 监视falsh擦除情况,测试用 */
    saddr *= 4096;
    Flash_Write_Enable();        /* 写使能 */
    Flas_Wait_Busy();           /* 等待空闲 */

    FLASH_CS_LOW;
    SPI1_Read_Write_Byte(FLASH_SectorErase);    /* 发送写页命令 */
    Flash_Send_Address(saddr);   /* 发送地址 */
    FLASH_CS_HIGH;
    Flas_Wait_Busy();           /* 等待扇区擦除完成 */
}



















