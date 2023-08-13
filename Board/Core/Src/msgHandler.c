#include "msgHandler.h"
#include "usart.h"
#include "string.h"
#include "ch9329.h"
#include "fpm383c.h"
#include "func_fingerprint.h"
#include "func_keyboard.h"
#include "delay.h"
#include "func_info.h"

static uint8_t g_running_mode = 0;		//ϵͳ��ǰ����ģʽ	0:Э�鴫��	1:͸��
uint16_t protocol_vid = 0x1998;
uint16_t protocol_pid = 0x0804;
uint16_t transmission_vid = 0x8421;
uint16_t transmission_pid = 0xABCD;

uint8_t Protocol_CMD[100];

/**
 * @brief		������Ӧ���ݰ�
 * @param		head ָ��ͷ
 * @param		data ��Ӧ����
 * @param		datalength	��Ӧ���ݳ���
 * @date		2023-5-5 19:13:46
 * @return 	��Ӧ���ݰ�����
 */
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

/**
 * @brief		��װЭ�鴫��HID���ݰ�
 * @param		*data ��Ӧ���ݰ�
 * @param		cmdLen ��Ӧ���ݰ�����
 * @date		2023-5-5 19:10:49
 * @return 	Э�����ݰ�����
 */
uint8_t GenerateProtocolCMD(uint8_t *data,uint8_t cmdLen)	//��װ��Ӧ
{
	Protocol_CMD[0] = 0x57;
	Protocol_CMD[1] = 0xAB;
	Protocol_CMD[2] = 0x00;
	Protocol_CMD[3] = 0x06;
	Protocol_CMD[4] = cmdLen;
	for(uint8_t i=0;i<cmdLen;i++){
		Protocol_CMD[i+5] = data[i];
	}

	Protocol_CMD[cmdLen+5] = CH9329_GenerateCheckSum(Protocol_CMD,cmdLen+5);
	return cmdLen+6;
}

void USB_Handler(uint8_t *data)	//�жϽ��յ�����������
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
		{
			GetTableState();
			uint8_t cmdLen = GenerateCmd(USB_TABLESTATE,RX_TableState,8);
			GenerateProtocolCMD(USB_CMD,cmdLen);
			Delay_ms(100);
			HAL_UART_Transmit(&KEYOUT,Protocol_CMD,cmdLen+6,1000);
			memset(USB_CMD,0,100);
			memset(Protocol_CMD,0,100);
			memset(RX_TableState,0,8);
			break;
		}
		case USB_ENROLL:	//ע��ָ��
		{
			uint8_t ID[2] = {0};
			uint8_t PARAM[2]={0};
			uint8_t enrolltimes = 0;
			ID[0] = data[3];
			ID[1] = data[4];
			enrolltimes = data[5];
			PARAM[0] = data[6];
			PARAM[1] = data[7];
			Con_AutoEnroll(ID,enrolltimes,PARAM);
			
		}
			break;
		case USB_DELETE:		//ɾ��ָ��
		{
			uint8_t state[1] = {0};
			uint8_t ID[2] = {0};
			uint8_t NUM[2] = {0};
			ID[0] = data[3];
			ID[1] = data[4];
			NUM[0] = data[5];
			NUM[1] = data[6];
			uint8_t result = Con_DeleteChar(ID,NUM);
			if(result == 1){		//ɾ���ɹ�
				state[0] = 0x00;
				//uint8_t cmdLen = GenerateCmd(USB_DELETE,state,1);
				//HAL_UART_Transmit(&KEYOUT,USB_CMD,cmdLen,1000);
				//memset(USB_CMD,0,100);
			}else{
				state[0] = 0x01;	//ɾ��ʧ��
				//uint8_t cmdLen = GenerateCmd(USB_DELETE,state,1);
				//HAL_UART_Transmit(&KEYOUT,USB_CMD,cmdLen,1000);
				//memset(USB_CMD,0,100);
			}
			break;
		}
		default :break;
		}
	}else if(head == PROTOCOL && data[3] == PRO_HID_DATA){		//Э�鴫����Ӧ
		switch (data[7]){	//�Զ���HID�豸���ݰ�
			case PRO_READ_PARA:
				memcpy(CH9329_CONFIG,RxData1,50);
				memset(RxData1,0,100);
				break;
			case PRO_SET_PARA:
				//1���ж�eeprom�������Ƿ���Ч
				//2����ȡeeprom������
				//3����������
				//4����������
				//5����������
				memset(RxData1,0,100);
				break;
			case USB_TRANSMIT:	//�л�Ϊ͸��ģʽ
			{
				if(data[7] == USB_TRANSMIT){	//�յ���λ���л�͸��ģʽָ��
					SET_EN;
					CH9329_WorkMode_Config(WORKMODE_SOFT_3);
					CH9329_SerialMode_Config(SERIALMODE_SOFT_2);
					CH9329_Set_Cfg();
					SET_DEN;
				}
				break;
			}
			case PRO_GET_TABLESTATE:	//��ȡ������״̬
			{
				GetTableState();
				uint8_t cmdLen = GenerateCmd(USB_TABLESTATE,RX_TableState,8);
				GenerateProtocolCMD(USB_CMD,cmdLen);
				Delay_ms(100);
				HAL_UART_Transmit(&KEYOUT,Protocol_CMD,cmdLen+6,1000);
				memset(USB_CMD,0,100);
				memset(Protocol_CMD,0,100);
				memset(RX_TableState,0,8);
				break;
			}
			case PRO_ENROLL:	//ע��ָ��
			{
				uint8_t ID[2] = {0};
				uint8_t PARAM[2]={0};
				uint8_t enrolltimes = 0;
				ID[0] = data[8];
				ID[1] = data[9];
				enrolltimes = data[10];
				PARAM[0] = data[11];
				PARAM[1] = data[12];
				Con_AutoEnroll(ID,enrolltimes,PARAM);
				break;
			}
			case PRO_DELETE:
			{
				uint8_t state[1] = {0};
				uint8_t ID[2] = {0};
				uint8_t NUM[2] = {0};
				ID[0] = data[8];
				ID[1] = data[9];
				NUM[0] = data[10];
				NUM[1] = data[11];
				uint8_t result = Con_DeleteChar(ID,NUM);
				if(result == 1){		//ɾ���ɹ�
					state[0] = 0x00;
					//uint8_t cmdLen = GenerateCmd(USB_DELETE,state,1);
					//HAL_UART_Transmit(&KEYOUT,USB_CMD,cmdLen,1000);
					//memset(USB_CMD,0,100);
				}else{
					state[0] = 0x01;	//ɾ��ʧ��
					//uint8_t cmdLen = GenerateCmd(USB_DELETE,state,1);
					//HAL_UART_Transmit(&KEYOUT,USB_CMD,cmdLen,1000);
					//memset(USB_CMD,0,100);
				}
			}
			case PRO_GET_INFO:
			{
				g_connectstate = data[6];
				g_keystate = data[7];
				break;
			}
			case PRO_STORE_FUNC:
			{
				uint8_t store_type = data[8];
				uint8_t *store_data = &data[9];
				Func_Store(store_type,store_data);
				break;
			}
			
			default : break;
		}
	}
	
}

void FPM383_Handler(uint8_t *exeFlag)
{
	if(*exeFlag == 0x01){
		*exeFlag = 0;
		uint8_t id[2] = {0xFF,0xFF};
		uint8_t param[2] = {0x00,0x04};
		uint8_t index = Con_AutoIdentify(id,param);
		Delay_ms(1000);
		Con_Sleep();
		
	}
	
}



























