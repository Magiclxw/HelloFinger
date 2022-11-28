#include "msgHandler.h"
#include "usart.h"
#include "func.h"



uint8_t Calc_Checksum(uint8_t *data)		//计算校验和
{
	uint8_t checksum = 0;
	uint8_t datalenght = data[1];
	for(int i=0;i<datalenght+1;i++){
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

uint8_t* GenerateCmd(uint8_t head,uint8_t *data,uint8_t datalength)	//生成响应
{
	uint8_t checksum;;
	static uint8_t cmd[20];			//指令长度
	cmd[0] = head;							
	cmd[1] = datalength;
	for(int i=2;i<datalength+2;i++){
		cmd[i] = data[i-2];
	}
	checksum = Calc_Checksum(cmd);
	cmd[datalength+2] = checksum;
	return cmd;
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
		case USB_TRANSMIT:
				//透传模式
			break;
		case USB_COMMAND:
				//协议传输模式
			break;
		case USB_TABLESTATE:
			GetTableState();
			uint8_t* USB_TableState = GenerateCmd(USB_TABLESTATE,RX_TableState,8);
			HAL_UART_Transmit(&KEYOUT,USB_TableState,11,1000);
		
		
		default :break;
		}
	}
	
}
