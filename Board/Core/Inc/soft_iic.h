#ifndef __SOFTIIC_H
#define __SOFTIIC_H
#include "stm32f1xx.h"
#include "delay.h"

#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 

#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) 	//0x40010C08 
 
#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //��� 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //���� 

#define SDA_IN()  {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(uint32_t)8<<28;}	//PB7����ģʽ
#define SDA_OUT() {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(uint32_t)3<<28;} 	//PB7���ģʽ

#define IIC_SCL   PBout(6) //SCL
#define IIC_SDA   PBout(7) //SDA
#define READ_SDA  PBin(7)  //����SDA


void IIC_Init(void);                			//��ʼ��IIC��IO��				 
void IIC_Start(void);											//����IIC��ʼ�ź�
void IIC_Stop(void);	  									//����IICֹͣ�ź�
void IIC_Send_Byte(uint8_t txd);					//IIC����һ���ֽ�
uint8_t IIC_Read_Byte(unsigned char ack);	//IIC��ȡһ���ֽ�
uint8_t IIC_Wait_Ack(void); 							//IIC�ȴ�ACK�ź�
void IIC_Ack(void);												//IIC����ACK�ź�
void IIC_NAck(void);											//IIC������ACK�ź�

void IIC_Write_One_Byte(uint8_t daddr,uint8_t addr,uint8_t data);
uint8_t IIC_Read_One_Byte(uint8_t daddr,uint8_t addr);

#endif
