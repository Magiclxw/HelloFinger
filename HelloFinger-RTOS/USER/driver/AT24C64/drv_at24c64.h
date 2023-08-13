#ifndef __AT24C64_H
#define __AT24C64_H
#include "stm32f1xx.h"

#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 

#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) 	//0x40010C08 
 
#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //输入 

#define SDA_IN()  {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(uint32_t)8<<28;}	//PB7输入模式
#define SDA_OUT() {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(uint32_t)3<<28;} 	//PB7输出模式

#define IIC_SCL   PBout(6) //SCL
#define IIC_SDA   PBout(7) //SDA
#define READ_SDA  PBin(7)  //输入SDA

#define EEPROM_SIZE	0xFFFF
#define EEPROM_BUFFER_SIZE	100

#define FINGER_FUNC_ADDR	0x0401	//指纹功能存储基地址

extern uint8_t EEPROM_RX_BUF[];
void IIC_Init(void);
uint8_t AT24C64_ReadOneByte(uint16_t ReadAddr);
void AT24C64_WriteOneByte(uint16_t WriteAddr,uint8_t DataToWrite);
void AT24C64_Read(uint16_t ReadAddr,uint8_t *pBuffer,uint16_t NumToRead);
void AT24C64_Write(uint16_t WriteAddr,uint8_t *pBuffer,uint16_t NumToWrite);
#endif
