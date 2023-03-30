#ifndef __SOFTIIC_H
#define __SOFTIIC_H
#include "stm32f1xx.h"
#include "delay.h"

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


void IIC_Init(void);                			//初始化IIC的IO口				 
void IIC_Start(void);											//发送IIC开始信号
void IIC_Stop(void);	  									//发送IIC停止信号
void IIC_Send_Byte(uint8_t txd);					//IIC发送一个字节
uint8_t IIC_Read_Byte(unsigned char ack);	//IIC读取一个字节
uint8_t IIC_Wait_Ack(void); 							//IIC等待ACK信号
void IIC_Ack(void);												//IIC发送ACK信号
void IIC_NAck(void);											//IIC不发送ACK信号

void IIC_Write_One_Byte(uint8_t daddr,uint8_t addr,uint8_t data);
uint8_t IIC_Read_One_Byte(uint8_t daddr,uint8_t addr);

#endif
