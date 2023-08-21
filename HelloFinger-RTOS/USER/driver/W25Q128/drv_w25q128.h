#ifndef __DRV_W25Q128_H
#define __DRV_W25Q128_H

#include "sys_config.h"


#define FLASH_CS_HIGH		(GPIOB->BSRR = GPIO_PIN_12)
#define FLASH_CS_LOW		(GPIOB->BSRR = (uint32_t)GPIO_PIN_12 << 16)

/* ָ��� */
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




void Flash_Init(void);
uint16_t Flash_Read_id(void);
uint8_t Flash_Read_SR(uint8_t regno);
static void Flash_Write_Page(uint8_t *pbuf, uint32_t addr, uint16_t datalen);
void Flash_Write(uint8_t *pbuf, uint32_t addr, uint16_t datalen);
void Flash_Sector_Erase(uint32_t saddr);


#endif
