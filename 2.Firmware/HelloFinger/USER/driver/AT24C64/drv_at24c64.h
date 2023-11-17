#ifndef __AT24C64_H
#define __AT24C64_H
#include "stm32f1xx.h"

#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 

#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) 	//0x40010C08 
 
#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //��� 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //���� 

#define SDA_IN()  {GPIOB->CRH&=0XFFFFFF0F;GPIOB->CRH|=(uint32_t)8<<4;}	//PB9����ģʽ
#define SDA_OUT() {GPIOB->CRH&=0XFFFFFF0F;GPIOB->CRH|=(uint32_t)3<<4;} 	//PB9���ģʽ

#define IIC_SCL   PBout(8) //SCL
#define IIC_SDA   PBout(9) //SDA
#define READ_SDA  PBin(9)  //����SDA



void AT24C64_Init(void);
uint8_t AT24C64_ReadOneByte(uint16_t ReadAddr);
void AT24C64_WriteOneByte(uint16_t WriteAddr,uint8_t DataToWrite);
void AT24C64_Read(uint16_t ReadAddr,uint8_t *pBuffer,uint16_t NumToRead);
void AT24C64_Write(uint16_t WriteAddr,uint8_t *pBuffer,uint16_t NumToWrite);
#endif