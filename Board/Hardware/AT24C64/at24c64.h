#ifndef __AT24C64_H
#define __AT24C64_H
#include "stm32f1xx.h"

#define EEPROM_SIZE	0xFFFF
#define EEPROM_BUFFER_SIZE	100

#define FINGER_FUNC_ADDR	0x0401	//指纹功能存储基地址

extern uint8_t EEPROM_RX_BUF[];
uint8_t AT24C64_ReadOneByte(uint16_t ReadAddr);
void AT24C64_WriteOneByte(uint16_t WriteAddr,uint8_t DataToWrite);
void AT24C64_Read(uint16_t ReadAddr,uint8_t *pBuffer,uint16_t NumToRead);
void AT24C64_Write(uint16_t WriteAddr,uint8_t *pBuffer,uint16_t NumToWrite);
#endif
