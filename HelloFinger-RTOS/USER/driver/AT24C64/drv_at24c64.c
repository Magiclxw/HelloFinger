#include "drv_at24c64.h"
#include "delay.h"

void IIC_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    
    __HAL_RCC_GPIOB_CLK_ENABLE();
    
    GPIO_Initure.Pin=GPIO_PIN_6|GPIO_PIN_7;
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;
    GPIO_Initure.Pull=GPIO_PULLUP;
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);
    
    IIC_SDA=1;
    IIC_SCL=1;  
}

void IIC_Start(void)
{
	SDA_OUT();
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	delay_us(4);
 	IIC_SDA=0;
	delay_us(4);
	IIC_SCL=0;
}	  

void IIC_Stop(void)
{
	SDA_OUT();
	IIC_SCL=0;
	IIC_SDA=0;
 	delay_us(4);
	IIC_SCL=1; 
	IIC_SDA=1;
	delay_us(4);							   	
}

uint8_t IIC_Wait_Ack(void)
{
	uint8_t ucErrTime=0;
	SDA_IN();
	IIC_SDA=1;delay_us(1);
	IIC_SCL=1;delay_us(1);
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL=0;   
	return 0;  
} 

void IIC_Ack(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=0;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}
    
void IIC_NAck(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=1;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}					 				     

void IIC_Send_Byte(uint8_t txd)
{                        
  uint8_t t;   
	SDA_OUT(); 	    
  IIC_SCL=0;
  for(t=0;t<8;t++)
  {              
  IIC_SDA=(txd&0x80)>>7;
  txd<<=1; 	  
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
	delay_us(2);
  }	 
} 	    

uint8_t IIC_Read_Byte(uint8_t ack)
{
	uint8_t i = 0;
	uint8_t receive=0;
	SDA_IN();
  for(i=0;i<8;i++ )
	{
    IIC_SCL=0; 
    delay_us(2);
		IIC_SCL=1;
    receive<<=1;
    if(READ_SDA)receive++;   
		delay_us(1); 
  }
  if(!ack){
    IIC_NAck();
	}else{
    IIC_Ack(); 
	}
  return receive;
}
 
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
	delay_us(10);
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






