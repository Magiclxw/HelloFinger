#ifndef __DRV_W25Q128_H
#define __DRV_W25Q128_H

#include "sys_config.h"


#define SPI_FLASH_CS_HIGH()		(GPIOB->BSRR = GPIO_PIN_12)
#define SPI_FLASH_CS_LOW()		(GPIOB->BSRR = (uint32_t)GPIO_PIN_12 << 16)

//#define SPI_FLASH_PageSize            4096
#define SPI_FLASH_PageSize              256
#define SPI_FLASH_PerWritePageSize      256

/* 指令表 */
#define FLASH_WriteEnable           0x06 
#define FLASH_WriteDisable          0x04 
#define FLASH_ReadStatusReg1        0x05 
#define FLASH_ReadStatusReg2        0x35 
#define FLASH_ReadStatusReg3        0x15 
#define FLASH_WriteStatusReg1       0x01 
#define FLASH_WriteStatusReg2       0x31 
#define FLASH_WriteStatusReg3       0x11 
#define FLASH_ReadData              0x03 
#define FLASH_FastReadData          0x0B 
#define FLASH_FastReadDual          0x3B 
#define FLASH_FastReadQuad          0xEB  
#define FLASH_PageProgram           0x02 
#define FLASH_PageProgramQuad       0x32 
#define FLASH_BlockErase            0xD8 
#define FLASH_SectorErase           0x20 
#define FLASH_ChipErase             0xC7 
#define FLASH_PowerDown             0xB9 
#define FLASH_ReleasePowerDown      0xAB 
#define FLASH_DeviceID              0xAB 
#define FLASH_ManufactDeviceID      0x90 
#define FLASH_JedecDeviceID         0x9F 
#define FLASH_Enable4ByteAddr       0xB7
#define FLASH_Exit4ByteAddr         0xE9
#define FLASH_SetReadParam          0xC0 
#define FLASH_EnterQPIMode          0x38
#define FLASH_ExitQPIMode           0xFF

#define WIP_Flag                  0x01  /* Write In Progress (WIP) flag */
#define Dummy_Byte                0xFF

#define FINGER_FUNC_BASE_ADDR	(0x100000)
#define FINGER_KEY_FUNC_BASE_ADDR	(0x102710)
#define FINGER_FUNC_LEN1_OFFSET	(0x01)
#define FINGER_FUNC_BASE_SIZE	(100)
#define FINGER_FUNC_RESERVED_DATA	(0x00)

#define ACTION_FUNC_BASE_ADDR	(0x104E20)


/*等待超时时间*/
#define SPIT_FLAG_TIMEOUT         ((uint32_t)0x1000)
#define SPIT_LONG_TIMEOUT         ((uint32_t)(10 * SPIT_FLAG_TIMEOUT))

/*信息输出*/
#define FLASH_DEBUG_ON         1

int Flash_Init(void);
int Flash_Erase_Chip(void);
int Flash_Erase_Sector(uint32_t saddr);
int Flash_Write_SR(uint8_t regno, uint8_t sr);
uint16_t Flash_Read_id(void);
int Flash_read(uint8_t *pbuf, uint32_t addr, uint16_t datalen);
int Flash_write(uint8_t *pbuf, uint32_t addr, uint16_t datalen);
int Flash_Read_DMA(uint8_t *pbuf, uint32_t addr, uint16_t datalen);

#endif
