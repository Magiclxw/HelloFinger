#include "msgHandler.h"
#include "usart.h"
#include "E:\WORK\PersonalProject\HelloKey\root\HelloKey\Hardware\CH9329\func.h"
#include "string.h"
#include "ZW800.h"

static uint8_t g_running_mode = 0;		//系统当前运行模式	0:协议传输	1:透传


uint8_t Calc_Checksum(uint8_t *data)		//计算校验和
{
	uint8_t checksum = 0;
	uint8_t datalenght = data[1];
	for(int i=0;i<datalenght+2;i++){
		checksum += data[i];
	}
	return checksum;
}

uint8_t Cmp_Checksum(uint8_t *data)		//比较校验和
{
	uint8_t checksum = 0;
	uint8_t datalenght = data[1];
	for(int i=0;i<datalenght+1;i++){
		checksum += data[i];
	}
	if(checksum == data[datalenght+1]){
		return 1;
	}else{
		return 0;
	}
}

uint8_t GenerateCmd(uint8_t head,uint8_t *data,uint8_t datalength)	//生成响应
{
	uint8_t checksum;;
	
	USB_CMD[0] = head;							
	USB_CMD[1] = datalength;
	for(int i=2;i<datalength+2;i++){
		USB_CMD[i] = data[i-2];
	}
	checksum = Calc_Checksum(USB_CMD);
	USB_CMD[datalength+2] = checksum;
	return datalength+3;
}

void Handler(uint8_t *data)	//判断接收到的数据类型
{
	uint8_t head;		//指令码
	uint8_t cmd;		//指令数据
	if(!Cmp_Checksum(data)){
		//checksum error
	}
	head = data[0];

	if(head == RECEIVE){
		cmd = data[2];
		switch (cmd){
		case USB_TRANSMIT:	//透传模式
			g_running_mode = 1;
			break;
		case USB_COMMAND:		//协议传输模式
			g_running_mode = 0;
			break;
		case USB_TABLESTATE:	//获取索引表信息
			GetTableState();
			uint8_t cmdLen = GenerateCmd(USB_TABLESTATE,RX_TableState,8);
			HAL_UART_Transmit(&KEYOUT,USB_CMD,cmdLen,1000);
			memset(USB_CMD,0,100);
			break;
		case USB_ENROLL:	//注册指纹
		{
			uint8_t ID[2] = {0};
			uint8_t PARAM[2]={0};
			uint8_t enrolltimes = 0;
			ID[1] = data[4];
			enrolltimes = data[5];
			PARAM[0] = data[6];
			PARAM[1] = data[7];
			Con_AutoEnroll(ID,enrolltimes,PARAM);
			
		}
			break;
		
		default :break;
		}
	}
	
}
