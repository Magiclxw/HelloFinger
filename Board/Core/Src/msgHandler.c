#include "msgHandler.h"
#include "usart.h"
#include "string.h"
#include "ch9329.h"
#include "fpm383c.h"
#include "func_fingerprint.h"
#include "func_keyboard.h"
#include "delay.h"

static uint8_t g_running_mode = 0;		//系统当前运行模式	0:协议传输	1:透传
uint16_t protocol_vid = 0x1998;
uint16_t protocol_pid = 0x0804;
uint16_t transmission_vid = 0x8421;
uint16_t transmission_pid = 0xABCD;



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

void USB_Handler(uint8_t *data)	//判断接收到的数据类型
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
		{
			GetTableState();
			uint8_t cmdLen = GenerateCmd(USB_TABLESTATE,RX_TableState,8);
			Delay_ms(100);
			HAL_UART_Transmit(&KEYOUT,USB_CMD,cmdLen,1000);
			memset(USB_CMD,0,100);
			memset(RX_TableState,0,8);
			break;
		}
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
		case USB_DELETE:		//删除指纹
		{
			uint8_t state[1] = {0};
			uint8_t ID[2] = {0};
			uint8_t NUM[2] = {0};
			ID[1] = data[4];
			NUM[1] = data[6];
			uint8_t result = Con_DeleteChar(ID,NUM);
			if(result == 1){		//删除成功
				state[0] = 0x00;
				uint8_t cmdLen = GenerateCmd(USB_DELETE,state,1);
				HAL_UART_Transmit(&KEYOUT,USB_CMD,cmdLen,1000);
				memset(USB_CMD,0,100);
			}else{
				state[0] = 0x01;	//删除失败
				uint8_t cmdLen = GenerateCmd(USB_DELETE,state,1);
				HAL_UART_Transmit(&KEYOUT,USB_CMD,cmdLen,1000);
				memset(USB_CMD,0,100);
			}
		}
		default :break;
		}
	}else if(head == PROTOCOL){		//协议传输响应
		switch (data[3]){
			case PRO_READ_PARA:
				memcpy(CH9329_CONFIG,RxData1,50);
				memset(RxData1,0,100);
				break;
			case PRO_SET_PARA:
				//1、判断eeprom中数据是否有效
				//2、获取eeprom中数据
				//3、更新配置
				//4、设置配置
				//5、保存配置
				memset(RxData1,0,100);
				break;
			case PRO_HID_DATA:	//收到上位机切换透传模式指令
			{
				if(data[7] == USB_TRANSMIT){
					SET_EN;
					CH9329_WorkMode_Config(WORKMODE_SOFT_3);
					CH9329_SerialMode_Config(SERIALMODE_SOFT_2);
					CH9329_Set_Cfg();
					SET_DEN;
				}
				break;
			}
			case PRO_GET_INFO:
			{
				g_connectstate = data[6];
				g_keystate = data[7];
				break;
			}
			
		}
	}
	
}

void FPM383_Handler(uint8_t *data)
{
	uint32_t dev_addr = data[2]<<24 | data[3]<<16 | data[4]<<8 | data[5];	//设备地址
	uint8_t pack_id = data[6];	//包标识
	
}



























