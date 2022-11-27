#include "func.h"
#include "ZW800.h"
#include "CH9329.h"
#include "kmfunc.h"
#include "delay.h"

extern uint8_t PS_AutoEnroll[AutoEnrollSize];
extern uint8_t PS_AutoIdentify[AutoIdentifySize];
extern uint8_t PS_DeletChar[DeletCharSize];
extern uint8_t PS_Cancel[CancelSize];
extern uint8_t PS_Sleep[SleepSize];
extern uint8_t PS_ValidTempleteNum[ValidTempleteNumSize];
extern uint8_t PS_ReadIndexTable[ReadIndexTableSize];
extern uint8_t PS_SetPwd[SetPwdSize];
extern uint8_t PS_VfyPwd[VfyPwdSize];
extern uint8_t PS_GetChipEcho[GetChipEchoSize];
extern uint8_t PS_AutoCaiSensor[AutoCaiSensorSize];
extern uint8_t PS_ControlBLN[ControlBLNSize];
extern uint8_t PS_GetDummyTempleteNo[GetDummyTempleteNoSize];

extern uint8_t PS_GetChipSN[GetChipSNSize];
extern uint8_t PS_HandShake[HandShakeSize];
extern uint8_t PS_CheckSensor[CheckSensorSize];
extern uint8_t PS_SetChipAddr[SetChipAddrSize];
extern uint8_t PS_WriteNotepad[WriteNotepadSize];
extern uint8_t PS_ReadNotepad[ReadNotepadSize];

extern uint8_t RxData1[100];
extern uint8_t RxData2[100];
extern __IO uint8_t rxstate1;
extern __IO uint8_t rxstate;

uint8_t RX_TableData[44];			//存储接收到的数据
uint8_t RX_TableState[8];			//存储索引表状态信息
uint8_t RX_SleepData[12];
uint8_t RX_AutoEnrollData[14];
uint8_t RX_AutoIdentifyData[17]={0};
uint8_t RX_GetDummyTempleteNoData[14];
uint8_t RX_ControlBLN[12];

uint8_t RX_GetChipSN[32];
uint8_t RX_ReadNotepad[32];

void GetTableState(void)			//获取索引表信息
{
	CMD_ReadIndexTable(0);
	
	HAL_UART_Transmit(&FINGER,PS_ReadIndexTable,ReadIndexTableSize,1000);
	
	while(rxstate!=1);

	for(int i=10;i<8+10;i++)
	{
		RX_TableState[i-10]=RxData2[i];
	}
	
	rxstate=0;

}

uint8_t Con_Sleep(void)
{
	CMD_Sleep();

	HAL_UART_Transmit(&FINGER,PS_Sleep,SleepSize,1000);

	while(rxstate!=1);
	
	rxstate=0;
	
	if(RxData2[8]==0x03 && RxData2[9]==0x00){
		//HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
		return 1;
	}
	return 0;
}

void Get_Free_ID()
{
	
}

void Con_AutoEnroll(uint8_t *ID,uint8_t NUM,uint8_t *PARAM)			//自动注册模板
{
	uint8_t result=0;
	
	uint8_t enrollstate[14];		//状态接收
	
	HAL_NVIC_DisableIRQ(EXTI4_IRQn);
	
	CMD_AutoEnroll(ID,NUM,PARAM);
	
	HAL_UART_Transmit(&FINGER,PS_AutoEnroll,AutoEnrollSize,1000);
	
	while(HAL_UART_Receive(&FINGER,enrollstate,14,1000))
	{
		if(RxData2[9]==0x00 && RxData2[10]==0x06)			//录入成功
		{
			
			HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
			
			break;
		}
		
		if(RxData2[9]==0x00 && RxData2[10]==0x03)			//判断手指离开
		{
			
		}
		
		if(RxData2[9]==0x22)			//指纹模板非空
		{
			
		}
		
	}
	
	
	
	HAL_NVIC_EnableIRQ(EXTI4_IRQn);
	
	if(result==1)
	{
		//CMD_ControlBLN(1,2,10);
		
		//HAL_UART_Transmit(&FINGER,PS_ControlBLN,ControlBLNSize,1000);
	}
}

uint8_t Con_AutoIdentify(uint8_t *ID,uint8_t *PARAM)						//自动验证指纹
{
	uint8_t result=0;
	
	CMD_AutoIdentify(3,ID,PARAM);

	HAL_UART_Transmit(&FINGER,PS_AutoIdentify,AutoIdentifySize,1000);

	while(rxstate!=1);
	
	if(RxData2[9]==0x00 && RxData2[10]==0x05)
	{
		HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
		
		UnLock(960,625);
		
		rxstate=0;
		
		//memset(RxData2,0,20);
		
		return 1;
	}
	//}
	return 0;
}

uint16_t blanknum;
uint16_t Con_GetDummyTempleteNo(void)		//指纹模块从 ID 位置 0 开始自动搜索没有注册的空白 ID 号	FPM383C无此功能
{
	CMD_GetDummyTempleteNo();
	
	HAL_UART_Transmit(&FINGER,PS_GetDummyTempleteNo,GetDummyTempleteNoSize,1000);
	
	while(rxstate!=1);
	
	if(RX_GetDummyTempleteNoData[9]==0x00)
	{
		blanknum=RX_GetDummyTempleteNoData[10];
		
		blanknum<<=8;
		
		blanknum|=RX_GetDummyTempleteNoData[11];
		
		rxstate=0;
		
		return blanknum;
	}
	
	rxstate=0;
	
	return 0;
}

uint8_t Con_ControlBLN(uint8_t FUNC,uint8_t startcolor,uint8_t endcolor,uint8_t circle)		//led灯控制
{
	CMD_ControlBLN(FUNC,startcolor,endcolor,circle);
	
	HAL_UART_Transmit(&FINGER,PS_ControlBLN,ControlBLNSize,1000);
	
	while(rxstate!=1);
	
	rxstate=0;
	
	if(RxData2[6]==0x07 && RxData2[9]==0x00)
	{
		return 1;
	}
	
	return 0;
}

uint8_t Con_GetChipSN(void)			//获取芯片唯一序列号
{
	CMD_GetChipSN();
	
	HAL_UART_Transmit(&FINGER,PS_GetChipSN,GetChipSNSize,1000);
	
	while(rxstate!=1);
	
	if(RxData2[9]==0x00)
	{
		for(int i=0;i<32;i++)
		{
			RX_GetChipSN[i]=RxData2[i+10];
		}
	}else
	{
		return 0;
	}
	rxstate=0;
	
	return 1;
}

uint8_t Con_HandShake(void)				//发送握手指令
{
	CMD_HandShake();
	
	HAL_UART_Transmit(&FINGER,PS_HandShake,HandShakeSize,1000);
	
	while(rxstate!=1);
	
	rxstate=0;
	
	if(RxData2[6]==0x07 && RxData2[9]==0x00)
	{
		
		return 1;
	}
	
	return 0;
	
}

uint8_t Con_CheckSensor(void)			//发送传感器校验指令
{
	CMD_CheckSensor();
	
	HAL_UART_Transmit(&FINGER,PS_CheckSensor,CheckSensorSize,1000);
	
	while(rxstate!=1);
	
	rxstate=0;
	
	if(RxData2[9]!=0x29)
	{
		return 1;
	}
	
	return 0;
}

uint8_t Con_SetPwd(uint8_t *PassWord)				//发送设置口令指令
{
	CMD_SetPwd(PassWord);
	
	HAL_UART_Transmit(&FINGER,PS_SetPwd,SetPwdSize,1000);
	
	while(rxstate!=1);
	
	rxstate=0;
	
	if(RxData2[6]==0x07 && RxData2[9]==0x00)
	{
		return 1;
	}
	
	return 0;
}

uint8_t Con_VfyPwd(uint8_t *PassWord)				//发送设置口令指令
{
	CMD_VfyPwd(PassWord);
	
	HAL_UART_Transmit(&FINGER,PS_VfyPwd,VfyPwdSize,1000);
	
	while(rxstate!=1);
	
	rxstate=0;
	
	if(RxData2[6]==0x07 && RxData2[9]==0x00)
	{
		return 1;
	}
	
	return 0;
}

uint8_t Con_SetChipAddr(uint8_t *Addr)			//设置设备地址
{
	CMD_SetChipAddr(Addr);
	
	HAL_UART_Transmit(&FINGER,PS_SetChipAddr,SetChipAddrSize,1000);
	
	while(rxstate!=1);
	
	rxstate=0;
	
	if(RxData2[6]==0x07 && RxData2[9]==0x00)
	{
		return 1;									//生成地址成功
	}
	return 0;
}

uint8_t Con_WriteNotepad(uint8_t Page,uint8_t *Content)			//写记事本
{
	CMD_WriteNotePad(Page,Content);
	
	HAL_UART_Transmit(&FINGER,PS_WriteNotepad,WriteNotepadSize,1000);
	
	while(rxstate!=1);
	
	rxstate=0;
	
	if(RxData2[6]==0x07 && RxData2[9]==0x00)
	{
		return 1;
	}
	
	if(RxData2[6]==0x07 && RxData2[9]==0x01)
	{
		return 0;				//收包有错
	}
	
	if(RxData2[6]==0x07 && RxData2[9]==0x1C)
	{
		return 2;				//记事本页码指定错误
	}
	
}

uint8_t Con_ReadNotepad(uint8_t Page)
{
	CMD_ReadNotepad(Page);
	
	HAL_UART_Transmit(&FINGER,PS_ReadNotepad,ReadNotepadSize,1000);
	
	while(rxstate!=1);
	
	rxstate=0;
	
	if(RxData2[6]==0x07 && RxData2[9]==0x00)
	{
		for(int i=0;i<32;i++)
		{
			RX_ReadNotepad[i]=RxData2[i+10];
		}
		
		return 1;
	}
	
	if(RxData2[6]==0x07 && RxData2[9]==0x01)			//收包有错
	{
		return 0;
	}
	
	if(RxData2[6]==0x07 && RxData2[9]==0x1C)			//记事本页码指定错误
	{
		return 2;
	}
	
}













