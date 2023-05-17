#include "at24c64.h"
#include "soft_iic.h"
#include "delay.h"
 
uint8_t EEPROM_RX_BUF[EEPROM_BUFFER_SIZE];

uint8_t AT24C64_ReadOneByte(uint16_t ReadAddr)
{				  
	uint8_t temp=0;
	IIC_Start(); 
	IIC_Send_Byte(0XA0);
	IIC_Wait_Ack();
	IIC_Send_Byte(ReadAddr>>8);
	IIC_Wait_Ack(); 
  IIC_Send_Byte(ReadAddr);
	IIC_Wait_Ack();	    
	IIC_Start();  	 	   
	IIC_Send_Byte(0XA1); 
	IIC_Wait_Ack();
  temp=IIC_Read_Byte(0);		   
  IIC_Stop();
	return temp;
}

void AT24C64_WriteOneByte(uint16_t WriteAddr,uint8_t DataToWrite)
{				   	  	    																 
  IIC_Start();
	IIC_Send_Byte(0XA0);
	IIC_Wait_Ack();
	IIC_Send_Byte(WriteAddr>>8);
	IIC_Wait_Ack();
  IIC_Send_Byte(WriteAddr);
	IIC_Wait_Ack();
	IIC_Send_Byte(DataToWrite);					   
	IIC_Wait_Ack();
  IIC_Stop();
	Delay_ms(10);
}

/**
 * @brief		写16bit或32bit数据
 * @param		WriteAddr 写操作地址
 * @param		DataToWrite 要写入的数据
 * @param		Len 数据宽度
 *          - 2 16bit
 * 					- 4 32bit
 * @date		2023-3-30 20:15:20
 * @return 	NULL
 */
void AT24C64_WriteLenByte(uint16_t WriteAddr,uint32_t DataToWrite,uint8_t Len)
{  	
	for(uint8_t t=0;t<Len;t++)
	{
		AT24C64_WriteOneByte(WriteAddr+t,(DataToWrite>>(8*t))&0xff);
	}												    
}

/**
 * @brief		读16bit或32bit数据
 * @param		ReadAddr 读操作地址
 * @param		Len 数据宽度
 *          - 2 16bit
 * 					- 4 32bit
 * @date		2023-3-30 20:16:05
 * @return 	NULL
 */
uint32_t AT24C64_ReadLenByte(uint16_t ReadAddr,uint8_t Len)
{  	
	uint32_t temp=0;
	for(uint8_t t=0;t<Len;t++)
	{
		temp<<=8;
		temp+=AT24C64_ReadOneByte(ReadAddr+Len-t-1); 	 				   
	}
	return temp;												    
}

void AT24C64_Read(uint16_t ReadAddr,uint8_t *pBuffer,uint16_t NumToRead)
{
	while(NumToRead)
	{
		*pBuffer++=AT24C64_ReadOneByte(ReadAddr++);
		NumToRead--;
	}
}

void AT24C64_Write(uint16_t WriteAddr,uint8_t *pBuffer,uint16_t NumToWrite)
{
	while(NumToWrite--)
	{
		AT24C64_WriteOneByte(WriteAddr,*pBuffer);
		WriteAddr++;
		pBuffer++;
	}
}






