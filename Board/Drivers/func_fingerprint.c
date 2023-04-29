#include "func_fingerprint.h"
#include "delay.h"
#include "stdlib.h"
#include "string.h"
#include "fpm383c.h"
#include "usart.h"

extern uint8_t RxData1[100];
extern uint8_t RxData2[100];

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
/**
 * @brief		�ȴ�Ӧ���
 * @param		ticks	����
 * @date		2023-3-26 17:30:34
 * @return 	ִ��״̬
 *					- 0 δ�յ���Ӧ
 *					- ����	�ȴ�ʱ��(*0.1ms)
 */
uint16_t WaitForResponse(uint16_t ticks)
{
	for(uint16_t i=0;i<ticks;i++){
		if(RxState == 1){
			RxState = 0;	//�����־
			return i;
		}
		Delay_us(100);
	}
	return 0;
}

/**
 * @brief		����Э���ʽ���������ͷ�����ݳ��Ⱥ�У���
 * @param		
 * @date		
 * @return 	
 */
uint8_t GenerateFixedCMD(uint8_t *data,uint8_t head)		
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
/**
 * @brief		��ȡ������״̬��Ϣ
 * @param		NULL
 * @date		2023-3-26 17:56:17
 * @return 	ִ��״̬
 *					- 0 ��ȡʧ��
 *					- 1	��ȡ�ɹ�
 */
uint8_t GetTableState(void)			//��ȡ��������Ϣ
{
	CMD_ReadIndexTable(0);
	
	HAL_UART_Transmit(&FINGER,PS_ReadIndexTable,ReadIndexTableSize,1000);
	
	if(WaitForResponse(1000)){
	//if(RxState == 1){
		//RxState = 0;
		for(int i=10;i<8+10;i++)
		{
			RX_TableState[i-10]=RxData2[i];
		}
		return 1;
	}
	return 0;
}

/**
 * @brief		����˯��ָ��
 * @param		NULL
 * @date		2023��3��26��17:57:51
 * @return 	ִ��״̬
 *					- 0 ��ȡʧ��
 *					- 1	��ȡ�ɹ�
 */
uint8_t Con_Sleep(void)
{
	CMD_Sleep();

	HAL_UART_Transmit(&FINGER,PS_Sleep,SleepSize,1000);

	if(WaitForResponse(1000)){
		if(RxData2[8]==0x03 && RxData2[9]==0x00) return 1;
	}
	
	return 0;
}

/**
 * @brief		�Զ�ע��ģ��
 * @param		*ID	ע��ID��
 * @param		NUM	ָ��¼�����
 * @param		*PARAM	����
 * @date		2023-3-26 21:27:42
 * @return 	NULL
 */
void Con_AutoEnroll(uint8_t *ID,uint8_t NUM,uint8_t *PARAM)
{
	uint8_t rsp[4] = {0x11,0x01,0x00,0x00};
	
	uint32_t timeout = 0;
	
	HAL_NVIC_DisableIRQ(EXTI4_IRQn);	//����ָ�ƴ����ж�
	
	CMD_AutoEnroll(ID,NUM,PARAM);
	
	HAL_UART_Transmit(&FINGER,PS_AutoEnroll,AutoEnrollSize,1000);	//�����Զ�ע��ģ��ָ��
	
	while(1)	//����ǰ״̬���͸���λ��
	{
		if(WaitForResponse(1000)){
			if(RxData2[9]==0x00){
				if(RxData2[10]==0x03){		//��ָ�ƿ�
					//rsp[0] = 0x11;
					//rsp[1] = 0x01;
					rsp[2] = ENROLL_STATE_LEAVE;
					rsp[3] = Calc_Checksum(rsp);
					HAL_UART_Transmit(&KEYOUT,rsp,4,100);
					timeout = 0;
					memset(rsp,0,4);
				}
				
				if(RxData2[10]==0x01){		//������ָ
					//rsp[0] = 0x11;
					//rsp[1] = 0x01;
					rsp[2] = ENROLL_STATE_PUT;
					rsp[3] = Calc_Checksum(rsp);
					HAL_UART_Transmit(&KEYOUT,rsp,4,100);
					timeout = 0;
					memset(rsp,0,4);
				}

				if(RxData2[10]==0x06)			//¼��ɹ�
				{
					//rsp[0] = 0x11;
					//rsp[1] = 0x01;
					rsp[2] = ENROLL_STATE_SUCCESS;
					rsp[3] = Calc_Checksum(rsp);
					HAL_UART_Transmit(&KEYOUT,rsp,4,100);
					RxState = 0;
					break;
				}
			}else{
				if(RxData2[9]==0x27 && RxData2[10]==0x05){		//ָ���ظ�
					//rsp[0] = 0x11;
					//rsp[1] = 0x01;
					rsp[2] = ENROLL_STATE_REPEAT;
					rsp[3] = Calc_Checksum(rsp);
					HAL_UART_Transmit(&KEYOUT,rsp,4,100);
					RxState = 0;
				}
				break;
			}
			RxState = 0;
		}
		timeout ++;
		if(timeout >= ENROLL_TIMEOUT){
			rsp[2] = ENROLL_STATE_TIMEOUT;
			rsp[3] = Calc_Checksum(rsp);
			HAL_UART_Transmit(&KEYOUT,rsp,4,100);
			RxState = 0;
			break;
		}
		Delay_ms(1);
	}
	HAL_NVIC_EnableIRQ(EXTI4_IRQn);
}


void Con_GenerateEnroll()
{
	HAL_NVIC_DisableIRQ(EXTI4_IRQn);	//����ָ�ƴ����ж�
	
	
}

/**
 * @brief		�Զ���ָ֤��
 * @param		*ID	ID��,0xFFFF:1-N����,����:1-1����
 * @param		*PARAM	����
 * @date		2023-3-26 21:32:07
 * @return 	�ԱȽ��
 *					- 0x00 �ɹ�
 *					- others	ʧ��ԭ��
 */
uint8_t Con_AutoIdentify(uint8_t *ID,uint8_t *PARAM)
{
	CMD_AutoIdentify(3,ID,PARAM);

	HAL_UART_Transmit(&FINGER,PS_AutoIdentify,AutoIdentifySize,1000);

	if(WaitForResponse(1000)){
		if(RxData2[9]==0x00 && RxData2[10]==0x05)	//�Աȳɹ�
		{
			
			return 0x00;
		}
	}
	return RxData2[9];
}

/**
 * @brief		ָ��ģ��� ID λ�� 0 ��ʼ�Զ�����û��ע��Ŀհ� ID ��	
 * @param		NULL
 * @date		2023-3-26 21:34:23
 * @return 	�ԱȽ��
 *					- 0xFFFF ʧ��
 *					- others	���ҵ�ID��
 * @note		FPM383C�޴˹���
 */
uint16_t blanknum;
uint16_t Con_GetDummyTempleteNo(void)
{
	CMD_GetDummyTempleteNo();
	
	HAL_UART_Transmit(&FINGER,PS_GetDummyTempleteNo,GetDummyTempleteNoSize,1000);
	
	if(WaitForResponse(1000)){
		if(RX_GetDummyTempleteNoData[9]==0x00)
		{
			blanknum=RX_GetDummyTempleteNoData[10];
			
			blanknum<<=8;
			
			blanknum|=RX_GetDummyTempleteNoData[11];
			
			return blanknum;
		}
	
	}
	
	return 0xFFFF;
}

/**
 * @brief	����LED��״̬
 * @param	FUNC:������ 1����ͨ������	2����˸��	3��������	4�����յ�
 * @param	startcolor:��ʼ��ɫ
 * @param	endcolor:������ɫ
 * @param	cycle:ѭ������ 0������ѭ��
 * @date	2023-3-21 21:13:28
 * @return 
 */
uint8_t Con_ControlBLN(uint8_t FUNC,uint8_t startcolor,uint8_t endcolor,uint8_t cycle)		//led�ƿ���
{
	CMD_ControlBLN(FUNC,startcolor,endcolor,cycle);
	
	HAL_UART_Transmit(&FINGER,PS_ControlBLN,ControlBLNSize,1000);
	
	//while(RxState!=1);
	//
	//RxState=0;
	if(WaitForResponse(1000)){
		if(RxData2[6]==0x07 && RxData2[9]==0x00)
		{
			return 1;
		}
	}
	return 0;
}

/**
 * @brief	��ȡоƬΨһ���к�
 * @param	NULL
 * @date	2023-3-26 21:38:40
 * @return ��ȡ���
 *					- 0 ʧ��
 *					- 1 �ɹ�
 */
uint8_t Con_GetChipSN(void)
{
	CMD_GetChipSN();
	
	HAL_UART_Transmit(&FINGER,PS_GetChipSN,GetChipSNSize,1000);
	
	if(WaitForResponse(1000)){
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
	}
	return 1;
}

/**
 * @brief	��������ָ��
 * @param	NULL
 * @date	2023-3-26 21:39:48
 * @return ���ֽ��
 *					- 0 ʧ��
 *					- 1 �ɹ�
 */
uint8_t Con_HandShake(void)
{
	CMD_HandShake();
	
	HAL_UART_Transmit(&FINGER,PS_HandShake,HandShakeSize,1000);
	
	if(WaitForResponse(1000)){
		
		if(RxData2[6]==0x07 && RxData2[9]==0x00)
		{
			return 1;
		}
	}
	return 0;
}

/**
 * @brief	���ʹ�����У��ָ��
 * @param	NULL
 * @date	2023-3-26 21:41:16
 * @return У����
 *					- 0 ʧ��
 *					- 1 �ɹ�
 */
uint8_t Con_CheckSensor(void)
{
	CMD_CheckSensor();
	
	HAL_UART_Transmit(&FINGER,PS_CheckSensor,CheckSensorSize,1000);
	
	if(WaitForResponse(1000)){

		if(RxData2[9]!=0x29)
		{
			return 1;
		}
	}
	return 0;
}

/**
 * @brief	�������ÿ���ָ��
 * @param	*passWord ����
 * @date	2023-3-26 21:42:48
 * @return �������ý��
 *					- 0 ʧ��
 *					- 1 �ɹ�
 */
uint8_t Con_SetPwd(uint8_t *PassWord)
{
	CMD_SetPwd(PassWord);
	
	HAL_UART_Transmit(&FINGER,PS_SetPwd,SetPwdSize,1000);
	
	if(WaitForResponse(1000)){
	
		if(RxData2[6]==0x07 && RxData2[9]==0x00)
		{
			return 1;
		}
	}
	return 0;
}

/**
 * @brief	������֤����ָ��
 * @param	*passWord ����
 * @date	2023-3-26 21:43:54
 * @return ������֤���
 *					- 0 ʧ��
 *					- 1 �ɹ�
 */
uint8_t Con_VfyPwd(uint8_t *PassWord)
{
	CMD_VfyPwd(PassWord);
	
	HAL_UART_Transmit(&FINGER,PS_VfyPwd,VfyPwdSize,1000);
	
	if(WaitForResponse(1000)){

		if(RxData2[6]==0x07 && RxData2[9]==0x00)
		{
			return 1;
		}
	}
	return 0;
}

/**
 * @brief	���������豸��ַָ��
 * @param	*Addr �豸��ַ
 * @date	2023-3-26 21:46:47
 * @return ���ý��
 *					- 0 ʧ��
 *					- 1 �ɹ�
 */
uint8_t Con_SetChipAddr(uint8_t *Addr)
{
	CMD_SetChipAddr(Addr);
	
	HAL_UART_Transmit(&FINGER,PS_SetChipAddr,SetChipAddrSize,1000);
	
	if(WaitForResponse(1000)){

		if(RxData2[6]==0x07 && RxData2[9]==0x00)	//���ɵ�ַ�ɹ�
		{
			return 1;									
		}
	}
	return 0;
}

/**
 * @brief	д���±�
 * @param	Page ���±�ҳ��
 * @param *Content ����
 * @date	2023-3-26 21:49:04
 * @return ���ý��
 *					- 1 �ɹ�
 *					- others ʧ��ԭ��
 */
uint8_t Con_WriteNotepad(uint8_t Page,uint8_t *Content)
{
	CMD_WriteNotePad(Page,Content);
	
	HAL_UART_Transmit(&FINGER,PS_WriteNotepad,WriteNotepadSize,1000);
	
	if(WaitForResponse(1000)){

		if(RxData2[6]==0x07 && RxData2[9]==0x00)
		{
			return 1;
		}
		
	}
	return RxData2[9];				//�հ��д�
	
}

/**
 * @brief	�����±�
 * @param	Page ���±�ҳ��
 * @date	2023-3-26 21:51:56
 * @return ��ȡ���
 *					- 1 �ɹ�
 *					- others ʧ��ԭ��
 */
uint8_t Con_ReadNotepad(uint8_t Page)
{
	CMD_ReadNotepad(Page);
	
	HAL_UART_Transmit(&FINGER,PS_ReadNotepad,ReadNotepadSize,1000);
	
	if(WaitForResponse(1000)){
		
		if(RxData2[6]==0x07 && RxData2[9]==0x00)
		{
			for(int i=0;i<32;i++)
			{
				RX_ReadNotepad[i]=RxData2[i+10];
			}
			
			return 1;
		}
	}
		return RxData2[9];
}

/**
 * @brief	ɾ�� flash ���ݿ���ָ�� ID �ſ�ʼ��N ��ָ��ģ��
 * @param	*PageID ָ�ƿ�ģ���
 * @param N ɾ����ģ�����
 * @date	2023-3-26 21:54:52
 * @return ɾ�����
 *					- 1 �ɹ�
 *					- 0 ʧ��
 */
uint8_t Con_DeleteChar(uint8_t *PageID,uint8_t *N)
{
	CMD_DeletChar(PageID,N);
	
	HAL_UART_Transmit(&FINGER,PS_DeletChar,DeletCharSize,1000);
	
	if(WaitForResponse(1000)){
		
		if(RxData2[6] == 0x07 && RxData2[9] == 0x00){		//ɾ���ɹ�
			return 1;
		}
		
	}
	return 0;
}


/**
 * @brief	ע��ָ��
 * @param	BufferID ģ�建����
 * @param PageID ҳID
 * @date	2023-3-26 21:58:43
 * @return ɾ�����
 *					- 1 �ɹ�
 *					- 0 ʧ��
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
			if(WaitForResponse(1000)){
				if(RxData2[9] == 0x02){
					HAL_UART_Transmit(&KEYOUT,"�����ָ��",10,100);
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
		}
		/* 2���������� */
		while(1){
			HAL_UART_Transmit(&FINGER,PS_GenChar,GenCharSize,100);
			if(WaitForResponse(1000)){
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
	}
	/* 3���ϲ����� */
	HAL_UART_Transmit(&FINGER,PS_RegModel,RegModelSize,100);
	if(WaitForResponse(1000)){
		if(RxData2[9] != 0x00){
			return errorcode++;
		}
	}
	HAL_UART_Transmit(&KEYOUT,"�Ƚϳɹ�",8,100);
	/* 4���洢ģ�� */
	HAL_UART_Transmit(&FINGER,PS_StoreChar,StoreCharSize,100);
	if(WaitForResponse(1000)){
		if(RxData2[9] != 0x00){
			if(RxData2[9] == 0x01) HAL_UART_Transmit(&KEYOUT,"�հ��д�",10,100);
			if(RxData2[9] == 0x0b) HAL_UART_Transmit(&KEYOUT,"Page id������Χ",20,100);
			if(RxData2[9] == 0x18) HAL_UART_Transmit(&KEYOUT,"дflash����",15,100);
			if(RxData2[9] == 0x31) HAL_UART_Transmit(&KEYOUT,"���ܵȼ���ƥ��",20,100);
			return errorcode++;
		}
		HAL_UART_Transmit(&KEYOUT,"�洢�ɹ�",8,100);
	}
	HAL_NVIC_EnableIRQ(EXTI4_IRQn);
	return 0;
}














