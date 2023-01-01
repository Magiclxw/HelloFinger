#include "msgHandler.h"
#include "usart.h"
#include "E:\WORK\PersonalProject\HelloKey\root\HelloKey\Hardware\CH9329\func.h"
#include "string.h"
#include "ZW800.h"

static uint8_t g_running_mode = 0;		//ϵͳ��ǰ����ģʽ	0:Э�鴫��	1:͸��


uint8_t Calc_Checksum(uint8_t *data)		//����У���
{
	uint8_t checksum = 0;
	uint8_t datalenght = data[1];
	for(int i=0;i<datalenght+2;i++){
		checksum += data[i];
	}
	return checksum;
}

uint8_t Cmp_Checksum(uint8_t *data)		//�Ƚ�У���
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

uint8_t GenerateCmd(uint8_t head,uint8_t *data,uint8_t datalength)	//������Ӧ
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

void Handler(uint8_t *data)	//�жϽ��յ�����������
{
	uint8_t head;		//ָ����
	uint8_t cmd;		//ָ������
	if(!Cmp_Checksum(data)){
		//checksum error
	}
	head = data[0];

	if(head == RECEIVE){
		cmd = data[2];
		switch (cmd){
		case USB_TRANSMIT:	//͸��ģʽ
			g_running_mode = 1;
			break;
		case USB_COMMAND:		//Э�鴫��ģʽ
			g_running_mode = 0;
			break;
		case USB_TABLESTATE:	//��ȡ��������Ϣ
			GetTableState();
			uint8_t cmdLen = GenerateCmd(USB_TABLESTATE,RX_TableState,8);
			HAL_UART_Transmit(&KEYOUT,USB_CMD,cmdLen,1000);
			memset(USB_CMD,0,100);
			break;
		case USB_ENROLL:	//ע��ָ��
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
