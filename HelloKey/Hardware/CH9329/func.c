#include "func.h"
#include "ZW800.h"
#include "CH9329.h"
#include "kmfunc.h"
#include "delay.h"
#include "stdlib.h"


extern uint8_t RxData1[100];
extern uint8_t RxData2[100];
extern __IO uint8_t rxstate1;
extern __IO uint8_t rxstate;

uint8_t RX_TableData[44];			//�洢���յ�������
uint8_t RX_TableState[8];			//�洢������״̬��Ϣ
uint8_t RX_SleepData[12];
uint8_t RX_AutoEnrollData[14];
uint8_t RX_AutoIdentifyData[17]={0};
uint8_t RX_GetDummyTempleteNoData[14];
uint8_t RX_ControlBLN[12];

uint8_t RX_GetChipSN[32];
uint8_t RX_ReadNotepad[32];

uint8_t USB_CMD[100];		//usb����ָ��buffer

uint8_t GenerateHeadLenCheck(uint8_t *data,uint8_t head)		//����Э���ʽ���������ͷ�����ݳ��Ⱥ�У���
{
	uint8_t checksum = 0;
	uint8_t length = 0;
	length = sizeof(data) + 3;
	
	USB_CMD[0] = head;
	USB_CMD[1] = length;
	/* ������� */
	for(uint8_t i=2;i<length-1;i++){
		USB_CMD[i] = data[i-2];
	}
	/* ����У��� */
	for(uint8_t i=0;i<length-1;i++){
		checksum += USB_CMD[i];
	}
	USB_CMD[length - 1] = checksum;
	
	return length;
}

void GetTableState(void)			//��ȡ��������Ϣ
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

void Con_AutoEnroll(uint8_t *ID,uint8_t NUM,uint8_t *PARAM)			//�Զ�ע��ģ��
{
	HAL_NVIC_DisableIRQ(EXTI4_IRQn);	//����ָ�ƴ����ж�
	
	CMD_AutoEnroll(ID,NUM,PARAM);
	
	HAL_UART_Transmit(&FINGER,PS_AutoEnroll,AutoEnrollSize,1000);	//�����Զ�ע��ģ��ָ��
	
	while(1)
	{
		if(rxstate == 1){
			if(RxData2[9]==0x00){
				if(RxData2[10]==0x03){
					HAL_UART_Transmit(&KEYOUT,"��ָ�ƿ�",10,100);
				}
				
				if(RxData2[10]==0x01){
					HAL_UART_Transmit(&KEYOUT,"������ָ",10,100);
				}

				if(RxData2[10]==0x06)			//¼��ɹ�
				{
					HAL_UART_Transmit(&KEYOUT,"¼��ɹ�",10,100);
					HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);	//����˸
					rxstate = 0;
					break;
				}
			}else{
				if(RxData2[9]==0x27 && RxData2[10]==0x05){
					HAL_UART_Transmit(&KEYOUT,"ָ���ظ�",10,100);
				}
				
				HAL_UART_Transmit(&KEYOUT,"ע��ʧ��",10,100);
				break;
			}
			rxstate = 0;
		}
	}
	HAL_NVIC_EnableIRQ(EXTI4_IRQn);
}

void Con_GenerateEnroll()
{
	HAL_NVIC_DisableIRQ(EXTI4_IRQn);	//����ָ�ƴ����ж�
	
	
}

uint8_t Con_AutoIdentify(uint8_t *ID,uint8_t *PARAM)						//�Զ���ָ֤��
{
	uint8_t result=0;
	
	CMD_AutoIdentify(3,ID,PARAM);

	HAL_UART_Transmit(&FINGER,PS_AutoIdentify,AutoIdentifySize,1000);

	while(rxstate!=1);
	
	if(RxData2[9]==0x00 && RxData2[10]==0x05)
	{
		HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
		HAL_UART_Transmit(&KEYOUT,"��֤�ɹ�",10,100);
		//UnLock(960,625);
		
		rxstate=0;
		
		return 1;
	}else{
		return RxData2[9];
	}

}

uint16_t blanknum;
uint16_t Con_GetDummyTempleteNo(void)		//ָ��ģ��� ID λ�� 0 ��ʼ�Զ�����û��ע��Ŀհ� ID ��	FPM383C�޴˹���
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

uint8_t Con_ControlBLN(uint8_t FUNC,uint8_t startcolor,uint8_t endcolor,uint8_t circle)		//led�ƿ���
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

uint8_t Con_GetChipSN(void)			//��ȡоƬΨһ���к�
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

uint8_t Con_HandShake(void)				//��������ָ��
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

uint8_t Con_CheckSensor(void)			//���ʹ�����У��ָ��
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

uint8_t Con_SetPwd(uint8_t *PassWord)				//�������ÿ���ָ��
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

uint8_t Con_VfyPwd(uint8_t *PassWord)				//�������ÿ���ָ��
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

uint8_t Con_SetChipAddr(uint8_t *Addr)			//�����豸��ַ
{
	CMD_SetChipAddr(Addr);
	
	HAL_UART_Transmit(&FINGER,PS_SetChipAddr,SetChipAddrSize,1000);
	
	while(rxstate!=1);
	
	rxstate=0;
	
	if(RxData2[6]==0x07 && RxData2[9]==0x00)
	{
		return 1;									//���ɵ�ַ�ɹ�
	}
	return 0;
}

uint8_t Con_WriteNotepad(uint8_t Page,uint8_t *Content)			//д���±�
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
		return 0;				//�հ��д�
	}
	
	if(RxData2[6]==0x07 && RxData2[9]==0x1C)
	{
		return 2;				//���±�ҳ��ָ������
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
	
	if(RxData2[6]==0x07 && RxData2[9]==0x01)			//�հ��д�
	{
		return 0;
	}
	
	if(RxData2[6]==0x07 && RxData2[9]==0x1C)			//���±�ҳ��ָ������
	{
		return 2;
	}
	
}

/* 	ע��ָ��
*/
uint8_t Con_Register(uint8_t BufferID,uint16_t PageID)
{
	uint8_t errorcode = 0;
	CMD_GetImage();		//���ɻ�ȡָ��ָ��
	CMD_GenChar(1);		//������������ָ��
	CMD_RegModel();		//���ɺϲ�����ָ��
	CMD_StoreChar(BufferID,PageID);		//���ɴ洢ģ��ָ��
	
	HAL_NVIC_DisableIRQ(EXTI4_IRQn);	//����ָ�ƴ����ж�
	//HAL_NVIC_DisableIRQ(USART2_IRQn);	//���ô����ж�
	
	/* 1����ȡͼ�� */
	for(uint8_t i =0;i<4;i++){				//ѭ��4��
		while(1){
			HAL_UART_Transmit(&FINGER,PS_GetImage,GetImageSize,100);
			while(rxstate!=1);
			if(RxData2[9] == 0x02){
				HAL_UART_Transmit(&KEYOUT,"�����ָ��",10,100);
				Delay_ms(1000);
			}
			if(RxData2[9] == 0x00){
				HAL_UART_Transmit(&KEYOUT,"��ȡָ��",10,100);
				break;
			}
			if(RxData2[9] == 0x01){
				HAL_UART_Transmit(&KEYOUT,"�հ��д�",10,100);
				return errorcode++;
			}
		}
		/* 2���������� */
		while(1){
			HAL_UART_Transmit(&FINGER,PS_GenChar,GenCharSize,100);
			while(rxstate!=1);
			if(RxData2[9] != 0x00){
				if(RxData2[9] == 0x01) HAL_UART_Transmit(&KEYOUT,"�հ��д�",10,100);
				if(RxData2[9] == 0x06) HAL_UART_Transmit(&KEYOUT,"ָ��ͼ����",10,100);
				if(RxData2[9] == 0x07) HAL_UART_Transmit(&KEYOUT,"������̫��",10,100);
				if(RxData2[9] == 0x08) HAL_UART_Transmit(&KEYOUT,"����֮���޹���",10,100);
				if(RxData2[9] == 0x0a) HAL_UART_Transmit(&KEYOUT,"�ϲ�ʧ��",10,100);
				if(RxData2[9] == 0x15) HAL_UART_Transmit(&KEYOUT,"��ԭʼͼ",10,100);
				if(RxData2[9] == 0x28) HAL_UART_Transmit(&KEYOUT,"����֮���й���",10,100);
				return errorcode++;
			}else{
				HAL_UART_Transmit(&KEYOUT,"���������ɹ�",12,100);
				break;
			}
		}
	}
	/* 3���ϲ����� */
	HAL_UART_Transmit(&FINGER,PS_RegModel,RegModelSize,100);
	while(rxstate!=1);
	if(RxData2[9] != 0x00){
		return errorcode++;
	}
	HAL_UART_Transmit(&KEYOUT,"�Ƚϳɹ�",8,100);
	/* 4���洢ģ�� */
	Delay_ms(1000);
	HAL_UART_Transmit(&FINGER,PS_StoreChar,StoreCharSize,100);
	while(rxstate!=1);
	if(RxData2[9] != 0x00){
		if(RxData2[9] == 0x01) HAL_UART_Transmit(&KEYOUT,"�հ��д�",10,100);
		if(RxData2[9] == 0x0b) HAL_UART_Transmit(&KEYOUT,"Page id������Χ",20,100);
		if(RxData2[9] == 0x18) HAL_UART_Transmit(&KEYOUT,"дflash����",15,100);
		if(RxData2[9] == 0x31) HAL_UART_Transmit(&KEYOUT,"���ܵȼ���ƥ��",20,100);
		return errorcode++;
	}
	HAL_UART_Transmit(&KEYOUT,"�洢�ɹ�",8,100);
	
	Delay_ms(1000);
	HAL_NVIC_EnableIRQ(EXTI4_IRQn);
	return 0;
}











