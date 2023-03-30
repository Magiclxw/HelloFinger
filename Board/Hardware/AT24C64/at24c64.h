#ifndef __AT24C64_H
#define __AT24C64_H
#include "stm32f1xx.h"

#define EEPROM_SIZE	0xFFFF
#define EEPROM_BUFFER_SIZE	100

extern uint8_t EEPROM_RX_BUF[];

void AT24C64_Read(uint16_t ReadAddr,uint8_t *pBuffer,uint16_t NumToRead);
void AT24C64_Write(uint16_t WriteAddr,uint8_t *pBuffer,uint16_t NumToWrite);
#endif
