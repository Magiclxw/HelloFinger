#include "kmfunc.h"
#include "CH9329.h"
#include "delay.h"
#include "mouse.h"
#include "func.h"

uint8_t Response[100];
uint8_t nums;

uint8_t CpStatus;
uint8_t CpNumLock;
uint8_t CpCapsLock;

uint8_t Parameter				[9]						={0x57,0xAB,0x00,0x08,0x00,0x0A,0xFF,0x0D,0x0A};
uint8_t Reset						[9]						={0x57,0xAB,0x00,0x0F,0x00,0x11,0xFF,0x0D,0x0A};
uint8_t Default					[9]						={0x57,0xAB,0x00,0x0C,0x00,0x1F,0xFF,0x0D,0x0A};

uint16_t TIMES;

uint8_t tests[10]={"asd13579"};


uint8_t autoidentify[6]="autoid";
uint8_t getdummytempleteno[6]="getdum";
uint8_t gettablestate[6]="gettab";

//1920*1080:  X=960,Y=625		解锁
void UnLock(uint16_t X,uint16_t Y)
{
	Cal(X,Y);
	HAL_UART_Transmit(&KEYOUT,Move2Center,16,1000);
	HAL_UART_Transmit(&KEYOUT,PressLeft,16,1000);
	HAL_UART_Transmit(&KEYOUT,PressRelease,16,1000);
	Sendtest(tests);
	SendCommand(LeftEnter);
}

/**发送字符输出指令*/
void Sendtest(uint8_t *asc)
{
	toASCLL(asc);
	for(int i=0;i<len;i++){
		SendCommand((uint8_t*)ascll[result[i]]);	//发送ascll字符数组中第result[i]个字符
	}
}

void CMD_GET_INFO(void)
{
	nums=14;
	TIMES=1000;
	HAL_UART_Transmit(&KEYOUT,INFO,9,1000);
	Delay_ms(100);
	while(Response[3]!=0x81){
		TIMES--;
		if(TIMES==0){
			//Usart2_SendWord("信息获取失败\r\n");
			break;
		}
	}
	if(TIMES!=0){
		//Usart2_SendWord("信息获取成功\r\n");
	}
	CpStatus=Response[6];
	CpNumLock=Response[7]&0x01;
	CpCapsLock=Response[7]&0x02;
}

void CMD_GET_PARA_CFG(void)
{
	HAL_UART_Transmit(&KEYOUT,Parameter,9,1000);
}

void CMD_RESET(void)
{
	HAL_UART_Transmit(&KEYOUT,Reset,9,1000);
}

void CMD_SET_DEFAULT_CFG()
{
	
}


uint8_t DATA_Compare(uint8_t *Data ,uint8_t *Temp , uint8_t Length)
{
	for(int i=0;i<Length;i++)
	{
		if(Data[i]!=Temp[i]) return 0;
	}
	
	return 1;
}

void DATA_Judge(uint8_t *Data , uint8_t Length)
{
	if(DATA_Compare(Data,autoidentify,Length)){
		Con_ControlBLN(0x01,0x01,0x01,0x00);
	}
	
	if(DATA_Compare(Data,getdummytempleteno,Length)){
		Con_GetDummyTempleteNo();
	}
	
	if(DATA_Compare(Data,gettablestate,Length)){
		GetTableState();
	}
	
	
}






























