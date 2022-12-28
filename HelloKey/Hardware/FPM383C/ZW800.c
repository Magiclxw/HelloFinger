#include "ZW800.h"
#include "func.h"

uint8_t 			CMD[7];				//ָ���ͷ+оƬ��ַ+����ʶ
volatile	uint8_t 			SUM[2];
uint8_t 			LEN=0;				//���ݳ���
uint8_t 			HEAD[2]							=							{0xEF,0x01}										;							//��ͷ
uint8_t 			ADDR[4]							=							{0xFF,0xFF,0xFF,0xFF}					;							//оƬ��ַ��Ĭ��0xffffffff
uint8_t				IDCMD								=							0x01													;							//����ʶ���������
uint8_t				IDDATA1							=							0x02													;							//����ʶ�����ݰ���
uint8_t				IDDATA2							=							0x08													;							//����ʶ����������


/*******************ָ����**********************/													/***********************ָ���볤��*************************/
uint8_t				AutoEnroll						=				0x31;		/*�Զ�ע��ģ��*/			uint8_t 			AutoEnrollLen[2]					=				{0x00,0x08};
uint8_t				AutoIdentify					=				0x32;		/*�Զ���ָ֤��*/			uint8_t				AutoIdentifyLen[2]				=				{0x00,0x08};
uint8_t				DeletChar							=				0x0C;		/*ɾ��ģ��*/     			uint8_t				DeletCharLen[2]						=				{0x00,0x07};
uint8_t				Empty									=				0x0D;		/*���ָ�ƿ�*/     		uint8_t				EmptyLen[2]								=				{0x00,0x03};
uint8_t				Cancel								=				0x30;		/*ȡ��ָ��*/     			uint8_t				CancelLen[2]							=				{0x00,0x03};
uint8_t				Sleep									=				0x33;		/*����ָ��*/     			uint8_t				SleepLen[2]								=				{0x00,0x03};
uint8_t				ValidTempleteNum			=				0x1D;		/*����Чģ�����*/   	uint8_t				ValidTempleteNumLen[2]		=				{0x00,0x03};
uint8_t				ReadIndexTable				=				0x1F;		/*��������*/     			uint8_t				ReadIndexTableLen[2]			=				{0x00,0x04};
uint8_t				SetPwd								=				0x12;		/*���ÿ���*/     			uint8_t				SetPwdLen[2]							=				{0x00,0x07};
uint8_t				VfyPwd								=				0x13;		/*��֤����*/     			uint8_t				VfyPwdLen[2]							=				{0x00,0x07};
uint8_t				GetImage							=				0x01;		/*��ȡͼ��*/     			uint8_t				GetImageLen[2]						=				{0x00,0x03};
uint8_t				GetRnrollImage				=				0x29;		/*ע���û�ȡͼ��*/   	uint8_t				GetRnrollImageLen[2]			=				{0x00,0x03};
uint8_t				GenChar								=				0x02;		/*��������*/     			uint8_t				GenCharLen[2]							=				{0x00,0x04};
uint8_t				Match									=				0x03;		/* ��ȷ�Ա� */				uint8_t				MatchLen[2]								=				{0x00,0x03};
uint8_t				RegMB									=				0x05;		/*�ϲ�ģ��*/     			uint8_t				RegMBLen[2]								=				{0x00,0x03};
uint8_t				StorMB								=				0x06;		/*�洢ģ��*/     			uint8_t				StorMBLen[2]              =				{0x00,0x06};
uint8_t				SearchMB							=				0x04;		/*����ģ��*/     			uint8_t				SearchMBLen[2]            =       {0x00,0x08};
uint8_t				GetChipUID						=				0x34;		/*��ȡоƬ���к�*/   	uint8_t				GetChipUIDLen[2]          =       {0x00,0x03};
uint8_t				GetChipEcho						=				0x35;		/*��������*/     			uint8_t				GetChipEchoLen[2]         =       {0x00,0x03};
uint8_t				AutoCaiSensor					=				0x36;		/*У�鴫����*/    		uint8_t				AutoCaiSensorLen[2]       =       {0x00,0x03};
uint8_t				UpImage								=				0x0A;		/*�ϴ�ͼ��*/    	 		uint8_t				UpImageLen[2]             =       {0x00,0x03};
uint8_t       ReadSysPara						=				0x16;		/*��ȡϵͳ��������*/ 	uint8_t				ReadSysParaLen[2]         =       {0x00,0x03};
uint8_t				ControlBLN						=				0x3C;		/*��ɫ��ָ��*/     		uint8_t				ControlBLNLen[2]          =       {0x00,0x07};
uint8_t				FingerCharUp					=				0x07;		/*�����ϴ�*/     			uint8_t				FingerCharUpLen[2]        =       {0x00,0x03};
uint8_t				FingerCharDown				=				0x08;		/*��������*/     		//uint8_t				FingerCharDownLen[2]      =       {0x00,0x0} ;
uint8_t 			FingerMoudleSet				=				0x0E;		/*ģ������*/     			uint8_t				FingerMoudleSetLen[2]     =       {0x00,0x05};
uint8_t				GetDummyTempleteNo		=				0x68;		/*��ȡ�հ״洢*/     	uint8_t				GetDummyTempleteNoLen[2]  =       {0x00,0x03};
uint8_t				GetFingerMoudleVersion=				0x73;		/*��ȡģ��̼��汾*/ 	uint8_t				GetFingerMoudleVersionLen[2]=     {0x00,0x03};


uint8_t 			GetChipSN							=				0x34;		/*��ȡоƬΨһ���к�*/uint8_t				GetChipSNLen[2]						=				{0x00,0x04};
uint8_t				HandShake							=				0x35;		/*����ָ��*/					uint8_t				HandShakeLen[2]						=				{0x00,0x03};
uint8_t 			CheckSenser						=				0x36;		/*У�鴫����ָ�� */		uint8_t 			CheckSenserLen[2]					=				{0x00,0x03};
uint8_t 			SetChipAddr						=				0x15;		/*�����豸��ַ*/			uint8_t				SetChipAddrLen[2]					=				{0x00,0x07};
uint8_t 			WriteNotepad					=				0x18;		/*д���±�*/					uint8_t				WriteNotepadLen[2]				=				{0x00,0x24};
uint8_t 			ReadNotepad						=				0x19;		/*�����±�*/					uint8_t				ReadNotepadLen[2]					=				{0x00,0x04};

/***************************************************************************************************************************************/

/*---------------------------------------------����ָ��---------------------------------------------------*/
uint8_t PS_AutoEnroll[AutoEnrollSize];
uint8_t PS_AutoIdentify[AutoIdentifySize]={0};
uint8_t PS_DeletChar[DeletCharSize];
uint8_t PS_Cancel[CancelSize];
uint8_t PS_Sleep[SleepSize];
uint8_t PS_ValidTempleteNum[ValidTempleteNumSize];
uint8_t PS_ReadIndexTable[ReadIndexTableSize];
uint8_t PS_SetPwd[SetPwdSize];
uint8_t PS_VfyPwd[VfyPwdSize];
uint8_t PS_GetChipEcho[GetChipEchoSize];
uint8_t PS_AutoCaiSensor[AutoCaiSensorSize];
uint8_t PS_ControlBLN[ControlBLNSize];
uint8_t PS_GetDummyTempleteNo[GetDummyTempleteNoSize];

uint8_t PS_GetChipSN[GetChipSNSize];
uint8_t PS_HandShake[HandShakeSize];
uint8_t PS_CheckSensor[CheckSensorSize];
uint8_t PS_SetChipAddr[SetChipAddrSize];
uint8_t PS_WriteNotepad[WriteNotepadSize];
uint8_t PS_ReadNotepad[ReadNotepadSize];
uint8_t	PS_GetImage[GetImageSize];
uint8_t PS_GenChar[GenCharSize];
uint8_t PS_RegModel[RegModelSize];
uint8_t PS_StoreChar[StoreCharSize];
uint8_t PS_Match[MatchSize];
/*---------------------------------------------------------------------------------------------------------*/


uint8_t *CmdConnect(void)				//�ϲ���ͷ+оƬ��ַ+����ʶ
{
	for(int i=0;i<2;i++){
		CMD[i]=HEAD[i];
	}
	for(int j=0;j<4;j++){
		CMD[j+2]=ADDR[j];
	}
	CMD[6]=IDCMD;
	
	return CMD;
}

void Check_Sum_Div(uint16_t sum)			//��У��ͷ�Ϊ�����ֽ�
{
	SUM[0]=sum>>8;
	SUM[1]=(uint8_t)sum;
}

void CMD_Init()
{
	
}

/*
func:generate AutoEnrool Command.
para:ID:Position of finger.
NUM:Record times.
PARAM:Parameter.
return:Address of CMD.
*/
uint8_t * CMD_AutoEnroll(uint8_t *ID,uint8_t NUM,uint8_t *PARAM)		//�����Զ�ע��ģ��ָ��
{
	uint8_t i=0;
	uint16_t checksum=0;
	while(1){
		PS_AutoEnroll[i]=CMD[i];
		i++;
		if(i==7){
			break;
		}
	}
	PS_AutoEnroll[i]=AutoEnrollLen[0];
	i++;
	PS_AutoEnroll[i]=AutoEnrollLen[1];
	i++;
	
	PS_AutoEnroll[i]=AutoEnroll;
	i++;
	
	PS_AutoEnroll[i]=ID[0];
	i++;
	PS_AutoEnroll[i]=ID[1];
	i++;
	
	PS_AutoEnroll[i]=NUM;
	i++;
	
	PS_AutoEnroll[i]=PARAM[0];
	i++;
	PS_AutoEnroll[i]=PARAM[1];
	i++;
	
	for(int s=6;s<15;s++){
		checksum+=PS_AutoEnroll[s];
	}
	
	Check_Sum_Div(checksum);
	
	PS_AutoEnroll[i]=SUM[0];
	i++;
	PS_AutoEnroll[i]=SUM[1];
	i++;
	
	LEN=i;
	
	return PS_AutoEnroll;
}

uint8_t *CMD_AutoIdentify(uint8_t secureleval,uint8_t *ID,uint8_t *PARAM)				//�����Զ���ָ֤��ָ��
{
	uint8_t i=0;
	uint16_t checksum=0;
	while(1){
		PS_AutoIdentify[i]=CMD[i];
		i++;
		if(i==7){
			break;
		}
	}
	PS_AutoIdentify[i]=AutoIdentifyLen[0];
	i++;
	PS_AutoIdentify[i]=AutoIdentifyLen[1];
	i++;
	
	PS_AutoIdentify[i]=AutoIdentify;
	i++;
	
	PS_AutoIdentify[i]=secureleval;
	i++;
	
	PS_AutoIdentify[i]=ID[0];
	i++;
	PS_AutoIdentify[i]=ID[1];
	i++;
	
	PS_AutoIdentify[i]=PARAM[0];
	i++;
	PS_AutoIdentify[i]=PARAM[1];
	i++;
	
	for(int s=6;s<15;s++){
		checksum+=PS_AutoIdentify[s];
	}
	
	Check_Sum_Div(checksum);
	
	PS_AutoIdentify[i]=SUM[0];
	i++;
	PS_AutoIdentify[i]=SUM[1];
	i++;
	
	LEN=i;
	
	return PS_AutoIdentify;
}

uint8_t *CMD_DeletChar(uint8_t *PageID,uint8_t *N)		//����ɾ��ģ��ָ��
{
	uint8_t i=0;
	uint16_t checksum=0;
	while(1){
		PS_DeletChar[i]=CMD[i];
		i++;
		if(i==7){
			break;
		}
	}
	
	PS_DeletChar[i]=DeletCharLen[0];
	i++;
	PS_DeletChar[i]=DeletCharLen[1];
	i++;
	
	PS_DeletChar[i]=DeletChar;
	i++;
	
	PS_DeletChar[i]=PageID[0];
	i++;
	PS_DeletChar[i]=PageID[1];
	i++;
	
	PS_DeletChar[i]=N[0];
	i++;
	PS_DeletChar[i]=N[1];
	i++;
	
	for(int s=6;s<14;s++){
		checksum+=PS_DeletChar[s];
	}
	
	Check_Sum_Div(checksum);
	
	PS_DeletChar[i]=SUM[0];
	i++;
	PS_DeletChar[i]=SUM[1];
	i++;
	
	LEN=i;
	
	return PS_DeletChar;
	
}

uint8_t *CMD_Cancel(void)					//����ȡ��ָ��
{
	uint8_t i=0;
	uint16_t checksum=0;
	while(1){
		PS_Cancel[i]=CMD[i];
		i++;
		if(i==7){
			break;
		}
	}
	
	PS_Cancel[i]=CancelLen[0];
	i++;
	PS_Cancel[i]=CancelLen[1];
	i++;
	
	PS_Cancel[i]=Cancel;
	i++;
	
	for(int s=6;s<10;s++){
		checksum+=PS_Cancel[s];
	}
	
	Check_Sum_Div(checksum);
	
	PS_Cancel[i]=SUM[0];
	i++;
	PS_Cancel[i]=SUM[1];
	i++;
	
	LEN=i;
	
	return PS_Cancel;
	
}

uint8_t *CMD_Sleep(void)
{
	uint8_t i=0;
	
	uint16_t checksum=0;
	
	while(1){
		
		PS_Sleep[i]=CMD[i];
		
		i++;
		
		if(i==7){
			break;
		}
	}
	PS_Sleep[i++]=SleepLen[0];
	
	PS_Sleep[i++]=SleepLen[1];
	
	PS_Sleep[i++]=Sleep;
	
	for(int s=6;s<10;s++){
		checksum+=PS_Sleep[s];
	}
	
	Check_Sum_Div(checksum);
	
	PS_Sleep[i++]=SUM[0];
	
	PS_Sleep[i++]=SUM[1];
	
	LEN=i;
	
	return PS_Sleep;
	
}

uint8_t *CMD_ValidTempleteNum(void)				//���ɶ���Чģ�����ָ��
{
	uint8_t i=0;
	uint16_t checksum=0;
	while(1){
		PS_ValidTempleteNum[i]=CMD[i];
		i++;
		if(i==7){
			break;
		}
	}
	
	PS_ValidTempleteNum[i]=ValidTempleteNumLen[0];
	i++;
	PS_ValidTempleteNum[i]=ValidTempleteNumLen[1];
	i++;
	
	PS_ValidTempleteNum[i]=ValidTempleteNum;
	i++;
	
	for(int s=6;s<10;s++){
		checksum+=PS_ValidTempleteNum[s];
	}
	
	Check_Sum_Div(checksum);
	
	PS_ValidTempleteNum[i]=SUM[0];
	i++;
	PS_ValidTempleteNum[i]=SUM[1];
	i++;
	
	LEN=i;
	
	return PS_ValidTempleteNum;
	
}

uint8_t *CMD_ReadIndexTable(uint8_t page)					//���ɶ�������ָ��
{
	uint8_t i=0;
	uint16_t checksum=0;
	while(1){
		PS_ReadIndexTable[i]=CMD[i];
		i++;
		if(i==7){
			break;
		}
	}
	
	PS_ReadIndexTable[i]=ReadIndexTableLen[0];
	i++;
	PS_ReadIndexTable[i]=ReadIndexTableLen[1];
	i++;
	
	PS_ReadIndexTable[i]=ReadIndexTable;
	i++;
	
	PS_ReadIndexTable[i]=page;
	i++;
	
	for(int s=6;s<11;s++){
		checksum+=PS_ReadIndexTable[s];
	}
	
	Check_Sum_Div(checksum);
	
	PS_ReadIndexTable[i]=SUM[0];
	i++;
	PS_ReadIndexTable[i]=SUM[1];
	i++;
	
	LEN=i;
	
	return PS_ReadIndexTable;
	
}

uint8_t *CMD_SetPwd(uint8_t *PassWord)			//�������ÿ���
{
	uint8_t i=0;
	uint16_t checksum=0;
	while(1){
		PS_SetPwd[i]=CMD[i];
		i++;
		if(i==7){
			break;
		}
	}
	
	PS_SetPwd[i]=SetPwdLen[0];
	i++;
	PS_SetPwd[i]=SetPwdLen[1];
	i++;
	
	PS_SetPwd[i]=SetPwd;
	i++;
	
	PS_SetPwd[i]=PassWord[0];
	i++;
	PS_SetPwd[i]=PassWord[1];
	i++;
	PS_SetPwd[i]=PassWord[2];
	i++;
	PS_SetPwd[i]=PassWord[3];
	i++;
	
	for(int s=6;s<14;s++){
		checksum+=PS_SetPwd[s];
	}
	
	Check_Sum_Div(checksum);
	
	PS_SetPwd[i]=SUM[0];
	i++;
	PS_SetPwd[i]=SUM[1];
	i++;
	
	LEN=i;
	
	return PS_SetPwd;
	
}

uint8_t *CMD_VfyPwd(uint8_t *PassWord)				//������֤����
{
	uint8_t i=0;
	uint16_t checksum=0;
	while(1){
		PS_VfyPwd[i]=CMD[i];
		i++;
		if(i==7){
			break;
		}
	}
	
	PS_VfyPwd[i]=VfyPwdLen[0];
	i++;
	PS_VfyPwd[i]=VfyPwdLen[1];
	i++;
	
	PS_VfyPwd[i]=VfyPwd;
	i++;
	
	PS_VfyPwd[i]=PassWord[0];
	i++;
	PS_VfyPwd[i]=PassWord[1];
	i++;
	PS_VfyPwd[i]=PassWord[2];
	i++;
	PS_VfyPwd[i]=PassWord[3];
	i++;
	
	for(int s=6;s<14;s++){
		checksum+=PS_VfyPwd[s];
	}
	
	Check_Sum_Div(checksum);
	
	PS_VfyPwd[i]=SUM[0];
	i++;
	PS_VfyPwd[i]=SUM[1];
	i++;
	
	LEN=i;
	
	return PS_VfyPwd;
}

uint8_t *CMD_GetChipEcho(void)				//������������
{
	uint8_t i=0;
	uint16_t checksum=0;
	while(1){
		PS_GetChipEcho[i]=CMD[i];
		i++;
		if(i==7){
			break;
		}
	}
	
	PS_GetChipEcho[i]=GetChipEchoLen[0];
	i++;
	PS_GetChipEcho[i]=GetChipEchoLen[1];
	i++;
	
	PS_GetChipEcho[i]=GetChipEcho;
	i++;
	
	for(int s=6;s<10;s++){
		checksum+=PS_GetChipEcho[s];
	}
	
	Check_Sum_Div(checksum);
	
	PS_GetChipEcho[i]=SUM[0];
	i++;
	PS_GetChipEcho[i]=SUM[1];
	i++;
	
	LEN=i;
	
	return PS_GetChipEcho;
	
}

uint8_t *CMD_AutoCaiSensor(void)				//����У�鴫����ָ��
{
	uint8_t i=0;
	uint16_t checksum=0;
	while(1){
		PS_AutoCaiSensor[i]=CMD[i];
		i++;
		if(i==7){
			break;
		}
	}
	
	PS_AutoCaiSensor[i]=AutoCaiSensorLen[0];
	i++;
	PS_AutoCaiSensor[i]=AutoCaiSensorLen[1];
	i++;
	
	PS_AutoCaiSensor[i]=AutoCaiSensor;
	i++;
	
	for(int s=6;s<10;s++){
		checksum+=PS_AutoCaiSensor[s];
	}
	
	Check_Sum_Div(checksum);
	
	PS_AutoCaiSensor[i]=SUM[0];
	i++;
	PS_AutoCaiSensor[i]=SUM[1];
	i++;
	
	LEN=i;
	
	return PS_AutoCaiSensor;
}

uint8_t *CMD_ControlBLN(uint8_t FUNC,uint8_t startcolor,uint8_t endcolor,uint8_t circle)					//������ɫ��ָ��
{
	uint8_t i=0;
	uint16_t checksum=0;
	while(1){
		PS_ControlBLN[i]=CMD[i];
		i++;
		if(i==7){
			break;
		}
	}
	
	PS_ControlBLN[i]=ControlBLNLen[0];
	i++;
	PS_ControlBLN[i]=ControlBLNLen[1];
	i++;
	
	PS_ControlBLN[i]=ControlBLN;
	i++;
	
	PS_ControlBLN[i]=FUNC;
	i++;
	
	PS_ControlBLN[i]=startcolor;
	i++;
	
	PS_ControlBLN[i]=endcolor;
	i++;
	
	PS_ControlBLN[i]=circle;
	i++;
	
	for(int s=6;s<14;s++){
		checksum+=PS_ControlBLN[s];
	}
	
	Check_Sum_Div(checksum);
	
	PS_ControlBLN[i]=SUM[0];
	i++;
	PS_ControlBLN[i]=SUM[1];
	i++;
	
	LEN=i;
	
	return PS_ControlBLN;
	
}


void CMD_GetDummyTempleteNo(void)					//���ɻ�ȡ�հ״洢ָ��
{
	uint8_t i=0;
	uint16_t checksum=0;
	while(1){
		PS_GetDummyTempleteNo[i]=CMD[i];
		i++;
		if(i==7){
			break;
		}
	}
	PS_GetDummyTempleteNo[i]=GetDummyTempleteNoLen[0];
	i++;
	PS_GetDummyTempleteNo[i]=GetDummyTempleteNoLen[1];
	i++;
	
	PS_GetDummyTempleteNo[i]=GetDummyTempleteNo;
	i++;
	
	for(int s=6;s<10;s++){
		checksum+=PS_GetDummyTempleteNo[s];
	}
	
	Check_Sum_Div(checksum);
	
	PS_GetDummyTempleteNo[i]=SUM[0];
	i++;
	PS_GetDummyTempleteNo[i]=SUM[1];
	i++;
	
	LEN=i;
	
}

void CMD_GetChipSN(void)					//���ɻ�ȡоƬΨһ���к�ָ��
{
	uint8_t i=0;
	uint16_t checksum=0;
	while(1)
	{
		PS_GetChipSN[i]=CMD[i];
		
		i++;
		
		if(i==7)
		{
			break;
		}
	}
	PS_GetChipSN[i++]=GetChipSNLen[0];
	
	PS_GetChipSN[i++]=GetChipSNLen[1];
	
	PS_GetChipSN[i++]=GetChipSN;
	
	for(int s=6;s<10;s++)
	{
		checksum+=PS_GetChipSN[s];
	}
	
	PS_GetChipSN[i++]=0x00;
	
	Check_Sum_Div(checksum);
	
	PS_GetChipSN[i++]=SUM[0];
	
	PS_GetChipSN[i++]=SUM[1];

	LEN=i;
}


void CMD_HandShake(void)			//�ϳ�����ָ��
{
	uint8_t i=0;
	uint16_t checksum=0;
	while(1)
	{
		PS_HandShake[i]=CMD[i];
		
		i++;
		
		if(i==7)
		{
			break;
		}
	}
	PS_HandShake[i++]=HandShakeLen[0];
	
	PS_HandShake[i++]=HandShakeLen[1];
	
	PS_HandShake[i++]=HandShake;
	
	for(int s=6;s<10;s++)
	{
		checksum+=PS_HandShake[s];
	}
	
	Check_Sum_Div(checksum);
	
	PS_HandShake[i++]=SUM[0];
	
	PS_HandShake[i++]=SUM[1];
	
	LEN=i;
	
}

void CMD_CheckSensor(void)
{
	uint8_t i=0;
	uint16_t checksum=0;
	while(1)
	{
		PS_CheckSensor[i]=CMD[i];
		
		i++;
		
		if(i==7)
		{
			break;
		}
	}
	
	PS_CheckSensor[i++]=CheckSenserLen[0];
	
	PS_CheckSensor[i++]=CheckSenserLen[1];
	
	PS_CheckSensor[i++]=CheckSenser;
	
	for(int s=6;s<10;s++)
	{
		checksum+=PS_CheckSensor[s];
	}
	
	Check_Sum_Div(checksum);
	
	PS_CheckSensor[i++]=SUM[0];
	
	PS_CheckSensor[i++]=SUM[1];
	
	LEN=i;
	
}

void CMD_SetChipAddr(uint8_t *Addr)
{
	uint8_t i=0;
	uint16_t checksum=0;
	while(1)
	{
		PS_SetChipAddr[i]=CMD[i];
		
		i++;
		
		if(i==7)
		{
			break;
		}
	}
	PS_SetChipAddr[i++]=SetChipAddrLen[0];
	
	PS_SetChipAddr[i++]=SetChipAddrLen[1];
	
	PS_SetChipAddr[i++]=SetChipAddr;
	
	PS_SetChipAddr[i++]=Addr[0];
	
	PS_SetChipAddr[i++]=Addr[1];
	
	PS_SetChipAddr[i++]=Addr[2];
	
	PS_SetChipAddr[i++]=Addr[3];
	
	for(int s=6;s<14;s++)
	{
		checksum+=PS_SetChipAddr[s];
	}
	
	Check_Sum_Div(checksum);
	
	PS_SetChipAddr[i++]=SUM[0];
	
	PS_SetChipAddr[i++]=SUM[1];
	
	LEN=i;
}

void CMD_WriteNotePad(uint8_t Page,uint8_t *Content)
{
	uint8_t i=0;
	uint16_t checksum=0;
	while(1)
	{
		PS_WriteNotepad[i]=CMD[i];
		
		i++;
		
		if(i==7)
		{
			break;
		}
	}
	PS_WriteNotepad[i++]=WriteNotepadLen[0];
	
	PS_WriteNotepad[i++]=WriteNotepadLen[1];
	
	PS_WriteNotepad[i++]=WriteNotepad;
	
	PS_WriteNotepad[i++]=Page;
	
	for(int c=0;c<32;c++)
	{
		PS_WriteNotepad[i+c]=Content[c];
	}
	i+=32;
	for(int s=6;s<43;s++)
	{
		checksum+=PS_WriteNotepad[s];
	}
	
	Check_Sum_Div(checksum);
	
	PS_WriteNotepad[i++]=SUM[0];
	
	PS_WriteNotepad[i++]=SUM[1];
	
	LEN=i;
}

void CMD_ReadNotepad(uint8_t Page)
{
	uint8_t i=0;
	uint16_t checksum=0;
	while(1)
	{
		PS_ReadNotepad[i]=CMD[i];
		
		i++;
		
		if(i==7)
		{
			break;
		}
	}
	PS_ReadNotepad[i++]=ReadNotepadLen[0];
	
	PS_ReadNotepad[i++]=ReadNotepadLen[1];
	
	PS_ReadNotepad[i++]=ReadNotepad;
	
	PS_ReadNotepad[i++]=Page;
	
	for(int s=6;s<11;s++)
	{
		checksum+=PS_ReadNotepad[s];
	}
	
	Check_Sum_Div(checksum);
	
	PS_ReadNotepad[i++]=SUM[0];
	
	PS_ReadNotepad[i++]=SUM[1];
	
	LEN=i;
}

void CMD_GetImage(void)		//���ɻ�ȡͼ��ָ��
{
	uint8_t i = 0;
	uint16_t checksum = 0;
	while(1){
		PS_GetImage[i] = CMD[i];
		i++;
		if(i==7){
			break;
		}
	}
	PS_GetImage[i++] = GetImageLen[0];
	
	PS_GetImage[i++] = GetImageLen[1];
	
	PS_GetImage[i++] = GetImage;
	
	for(int s=6;s<10;s++){
		checksum += PS_GetImage[s];
	}
	
	Check_Sum_Div(checksum);
	
	PS_GetImage[i++] = SUM[0];
	
	PS_GetImage[i++] = SUM[1];
	
	LEN = i;
}

void CMD_GenChar(uint8_t BufferID)			//��������ģ��ָ��
{
	uint8_t i = 0;
	uint16_t checksum = 0;
	while(1){
		PS_GenChar[i] = CMD[i];
		i++;
		if(i==7){
			break;
		}
	}
	PS_GenChar[i++] = GenCharLen[0];
	
	PS_GenChar[i++] = GenCharLen[1];
	
	PS_GenChar[i++] = GenChar;
	
	PS_GenChar[i++] = BufferID;
	
	for(int s=6;s<11;s++){
		checksum += PS_GenChar[s];
	}
	Check_Sum_Div(checksum);
	
	PS_GenChar[i++] = SUM[0];
	
	PS_GenChar[i++] = SUM[1];
	
	LEN = i;
}


void CMD_RegModel(void)				//���ɺϲ�����������ģ�壩ָ��
{
	uint8_t i = 0;
	uint16_t checksum = 0;
	while(1){
		PS_RegModel[i] = CMD[i];
		i++;
		if(i==7){
			break;
		}
	}
	PS_RegModel[i++] = RegMBLen[0];
	
	PS_RegModel[i++] = RegMBLen[1];
	
	PS_RegModel[i++] = RegMB;
	
	for(int s=6;s<10;s++){
		checksum += PS_RegModel[s];
	}
	
	Check_Sum_Div(checksum);
	
	PS_RegModel[i++] = SUM[0];
	
	PS_RegModel[i++] = SUM[1];
	
	LEN = i;
}

void CMD_StoreChar(uint8_t BufferID,uint16_t PageID)
{
	uint8_t i = 0;
	uint16_t checksum = 0;
	uint8_t pageid[2];
	while(1){
		PS_StoreChar[i] = CMD[i];
		i++;
		if(i==7){
			break;
		}
	}
	PS_StoreChar[i++] = StorMBLen[0];
	
	PS_StoreChar[i++] = StorMBLen[1];
	
	PS_StoreChar[i++] = StorMB;
	
	PS_StoreChar[i++] = BufferID;
	
	pageid[0] = PageID;
	
	pageid[1] = PageID>>8;
	
	PS_StoreChar[i++] = pageid[1];
	
	PS_StoreChar[i++] = pageid[0];
	
	for(int s=6;s<13;s++){
		checksum += PS_StoreChar[s];
	}
	
	Check_Sum_Div(checksum);
	
	PS_StoreChar[i++] = SUM[0];
	
	PS_StoreChar[i++] = SUM[1];
	
	LEN = i;
}

void CMD_Match(void)			//��ȷ�Ա�
{
	uint8_t i = 0;
	uint16_t checksum = 0;
	while(1){
		PS_Match[i] = CMD[i];
		i++;
		if(i==7){
			break;
		}
	}
	PS_Match[i++] = MatchLen[0];
	
	PS_Match[i++] = MatchLen[1];
	
	PS_Match[i++] = Match;
	
	for(int s=6;s<10;s++){
		checksum += PS_Match[s];
	}
	
	PS_Match[i++] = SUM[0];
	
	PS_Match[i++] = SUM[1];
	
	LEN = i;
}























