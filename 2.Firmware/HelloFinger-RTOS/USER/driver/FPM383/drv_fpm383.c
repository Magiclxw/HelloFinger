#include "drv_fpm383.h"
#include "app_task_key.h"
static void FPM383C_CMD_Init(void);
static uint16_t FPM383C_Generate_CMD_Checksum(uint8_t * cmd,uint16_t len);

uint8_t CMD_HEAD[2] =	{0xEF,0x01};						//��ͷ
uint8_t CMD_ADDR[4] =	{0xFF,0xFF,0xFF,0xFF};	//оƬ��ַ��Ĭ��0xffffffff
uint8_t CMD_HEAD_ADDR[6] = {0xEF,0x01,0xFF,0xFF,0xFF,0xFF};


/*******************ָ����**********************/													/***********************ָ���볤��*************************/
const uint8_t				AutoEnroll						=				0x31;		/*�Զ�ע��ģ��*/			const uint8_t 			AutoEnrollLen[2]					=				{0x00,0x08};
const uint8_t				AutoIdentify					=				0x32;		/*�Զ���ָ֤��*/			const uint8_t				AutoIdentifyLen[2]				=				{0x00,0x08};
const uint8_t				DeletChar							=				0x0C;		/*ɾ��ģ��*/     			const uint8_t				DeletCharLen[2]						=				{0x00,0x07};
const uint8_t				Empty									=				0x0D;		/*���ָ�ƿ�*/     		const uint8_t				EmptyLen[2]								=				{0x00,0x03};
const uint8_t				Cancel								=				0x30;		/*ȡ��ָ��*/     			const uint8_t				CancelLen[2]							=				{0x00,0x03};
const uint8_t				Sleep									=				0x33;		/*����ָ��*/     			const uint8_t				SleepLen[2]								=				{0x00,0x03};
const uint8_t				ValidTempleteNum			=				0x1D;		/*����Чģ�����*/   	const uint8_t				ValidTempleteNumLen[2]		=				{0x00,0x03};
const uint8_t				ReadIndexTable				=				0x1F;		/*��������*/     			const uint8_t				ReadIndexTableLen[2]			=				{0x00,0x04};
const uint8_t				SetPwd								=				0x12;		/*���ÿ���*/     			const uint8_t				SetPwdLen[2]							=				{0x00,0x07};
const uint8_t				VfyPwd								=				0x13;		/*��֤����*/     			const uint8_t				VfyPwdLen[2]							=				{0x00,0x07};
const uint8_t				GetImage							=				0x01;		/*��ȡͼ��*/     			const uint8_t				GetImageLen[2]						=				{0x00,0x03};
const uint8_t				GetRnrollImage				=				0x29;		/*ע���û�ȡͼ��*/   	const uint8_t				GetRnrollImageLen[2]			=				{0x00,0x03};
const uint8_t				GenChar								=				0x02;		/*��������*/     			const uint8_t				GenCharLen[2]							=				{0x00,0x04};
const uint8_t				Match									=				0x03;		/*��ȷ�Ա� */					const uint8_t				MatchLen[2]								=				{0x00,0x03};
const uint8_t				RegMB									=				0x05;		/*�ϲ�ģ��*/     			const uint8_t				RegMBLen[2]								=				{0x00,0x03};
const uint8_t				StorMB								=				0x06;		/*�洢ģ��*/     			const uint8_t				StorMBLen[2]              =				{0x00,0x06};
const uint8_t				SearchMB							=				0x04;		/*����ģ��*/     			const uint8_t				SearchMBLen[2]            =       {0x00,0x08};
const uint8_t				GetChipUID						=				0x34;		/*��ȡоƬ���к�*/   	const uint8_t				GetChipUIDLen[2]          =       {0x00,0x03};
const uint8_t				GetChipEcho						=				0x35;		/*��������*/     			const uint8_t				GetChipEchoLen[2]         =       {0x00,0x03};
const uint8_t				AutoCaiSensor					=				0x36;		/*У�鴫����*/    		const uint8_t				AutoCaiSensorLen[2]       =       {0x00,0x03};
const uint8_t				UpImage								=				0x0A;		/*�ϴ�ͼ��*/    	 		const uint8_t				UpImageLen[2]             =       {0x00,0x03};
const uint8_t       ReadSysPara						=				0x16;		/*��ȡϵͳ��������*/ 	const uint8_t				ReadSysParaLen[2]         =       {0x00,0x03};
const uint8_t				ControlBLN						=				0x3C;		/*��ɫ��ָ��*/     		const uint8_t				ControlBLNLen[2]          =       {0x00,0x07};
const uint8_t				ControlBLN_PRO				=				0x3C;		/* �߲ʵ� */					const uint8_t				ControlBLN_PROLen[2]			= 			{0x00,0x0B};
const uint8_t				FingerCharUp					=				0x07;		/*�����ϴ�*/     			const uint8_t				FingerCharUpLen[2]        =       {0x00,0x03};
const uint8_t				FingerCharDown				=				0x08;		/*��������*/     		//const uint8_t				FingerCharDownLen[2]      =       {0x00,0x0} ;
const uint8_t 			FingerMoudleSet				=				0x0E;		/*ģ������*/     			const uint8_t				FingerMoudleSetLen[2]     =       {0x00,0x05};
const uint8_t				GetDummyTempleteNo		=				0x68;		/*��ȡ�հ״洢*/     	const uint8_t				GetDummyTempleteNoLen[2]  =       {0x00,0x03};
const uint8_t				GetFingerMoudleVersion=				0x73;		/*��ȡģ��̼��汾*/ 	const uint8_t				GetFingerMoudleVersionLen[2]=     {0x00,0x03};


const uint8_t 			GetChipSN							=				0x34;		/*��ȡоƬΨһ���к�*/const uint8_t				GetChipSNLen[2]						=				{0x00,0x04};
const uint8_t				HandShake							=				0x35;		/*����ָ��*/					const uint8_t				HandShakeLen[2]						=				{0x00,0x03};
const uint8_t 			CheckSensor						=				0x36;		/*У�鴫����ָ�� */		const uint8_t 			CheckSensorLen[2]					=				{0x00,0x03};
const uint8_t 			SetChipAddr						=				0x15;		/*�����豸��ַ*/			const uint8_t				SetChipAddrLen[2]					=				{0x00,0x07};
const uint8_t 			WriteNotepad					=				0x18;		/*д���±�*/					const uint8_t				WriteNotepadLen[2]				=				{0x00,0x24};
const uint8_t 			ReadNotepad						=				0x19;		/*�����±�*/					const uint8_t				ReadNotepadLen[2]					=				{0x00,0x04};

/************************************************************************************************************************************/

FUNC_TOUCHRECVTCB TOUCHRECVCallback = NULL;

int RegisterFingerTouchCallBack(FUNC_TOUCHRECVTCB TOUCHRECVCBT)
{
	TOUCHRECVCallback = TOUCHRECVCBT;
	return OPERATE_SUCCESS;
}

int FPM383C_Init(void)
{
	GPIO_InitTypeDef gpio;
	__HAL_RCC_GPIOA_CLK_ENABLE();
	
	gpio.Mode = GPIO_MODE_IT_RISING;
	gpio.Pin = GPIO_PIN_4;
	gpio.Pull = GPIO_PULLDOWN;
	gpio.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA,&gpio);

	HAL_NVIC_SetPriority(EXTI4_IRQn,6,0);
	HAL_NVIC_EnableIRQ(EXTI4_IRQn);
	
	FPM383C_CMD_Init();
	
	CMD_Sleep_t							g_sleep							= {0};	//����ָ��ṹ��
	
	Generate_Sleep(&g_sleep);
	
	HAL_UART_Transmit(&FINGER_HANDLE,(uint8_t*)&g_sleep,g_sleep.LEN[0]<<8|g_sleep.LEN[1]+FIXED_CMD_LEN,1000);
	
	return OPERATE_SUCCESS;
}

static void FPM383C_CMD_Init(void)	//��ʼ����ͷ���豸��ַ�����ڿɴ�EEPROM�ж�ȡ
{
	CMD_HEAD[0] = 0xEF;
	CMD_HEAD[1] = 0x01;
	
	CMD_ADDR[0] = 0xFF;
	CMD_ADDR[1] = 0xFF;
	CMD_ADDR[2] = 0xFF;
	CMD_ADDR[3] = 0xFF;
	
	CMD_HEAD_ADDR[0] = 0xEF;
	CMD_HEAD_ADDR[1] = 0x01;
	CMD_HEAD_ADDR[2] = 0xFF;
	CMD_HEAD_ADDR[3] = 0xFF;
	CMD_HEAD_ADDR[4] = 0xFF;
	CMD_HEAD_ADDR[5] = 0xFF;
}

static uint16_t FPM383C_Generate_CMD_Checksum(uint8_t * cmd,uint16_t len)
{
	uint16_t checksum = 0;
	for(uint16_t i = 0; i<len; i++)
	{
		checksum += cmd[i];
	}
	return checksum;
}

/**
	*@brief	generate AutoEnrool Command.
	*@param	ID:Position of finger.
	*@param	enrollTimes:Record times.
	*@param	Parameter.
	*@return Address of CMD.
	*/
int Generate_AutoEnroll(CMD_AutoEnroll_t* autoenroll,uint16_t ID,uint8_t enrollTimes,uint16_t PARAM)		//�����Զ�ע��ģ��ָ��
{
	uint16_t checksum = 0;
	
	memcpy((uint8_t*)autoenroll->CMD_HEAD,CMD_HEAD,2);
	
	memcpy((uint8_t*)autoenroll->CMD_ADDR,CMD_ADDR,4);
	
	autoenroll->TYPE = ID_CMD;
	
	autoenroll->LEN[0] = AutoEnrollLen[0];
	
	autoenroll->LEN[1] = AutoEnrollLen[1];
	
	autoenroll->CMD = AutoEnroll;
	
	autoenroll->ID[0] = ID>>8;
	
	autoenroll->ID[1] = (uint8_t)ID;
	
	autoenroll->ENROLL_TIMES = enrollTimes;
	
	autoenroll->PARAM[0] = PARAM>>8;
	
	autoenroll->PARAM[1] = (uint8_t)PARAM;
	
	checksum = FPM383C_Generate_CMD_Checksum((uint8_t*)&autoenroll->TYPE,(autoenroll->LEN[0]<<8|autoenroll->LEN[1])+CHECKNUM_EXPECT_LEN);
	
	autoenroll->CHECKSUM[0] = checksum>>8;
	
	autoenroll->CHECKSUM[1] = (uint8_t)checksum;
	
	return OPERATE_SUCCESS;
}

int Generate_AutoIdentify(CMD_AutoIdentify_t *autoidentify,uint8_t secureleval,uint16_t ID,uint16_t PARAM)				//�����Զ���ָ֤��ָ��
{
	uint16_t checksum=0;
	
	memcpy((uint8_t*)autoidentify->CMD_HEAD,CMD_HEAD,2);
	
	memcpy((uint8_t*)autoidentify->CMD_ADDR,CMD_ADDR,4);
	
	autoidentify->TYPE = ID_CMD;
	
	autoidentify->LEN[0] = AutoIdentifyLen[0];
	
	autoidentify->LEN[1] = AutoIdentifyLen[1];
	
	autoidentify->CMD = AutoIdentify;
	
	autoidentify->LEVEL = secureleval;
	
	autoidentify->ID[0] = ID>>8;
	
	autoidentify->ID[1] = (uint8_t)ID;

	autoidentify->PARAM[0] = PARAM>>8;
	
	autoidentify->PARAM[1] = (uint8_t)PARAM;
	
	checksum = FPM383C_Generate_CMD_Checksum((uint8_t*)&autoidentify->TYPE,(autoidentify->LEN[0]<<8|autoidentify->LEN[1])+CHECKNUM_EXPECT_LEN);
	
	autoidentify->CHECKSUM[0] = checksum>>8;
	
	autoidentify->CHECKSUM[1] = (uint8_t)checksum;
	
	return OPERATE_SUCCESS;
}

int Generate_DeletChar(CMD_DeleteChar_t *deletechar,uint16_t PageID,uint16_t number)		//����ɾ��ģ��ָ��
{
	uint16_t checksum=0;
	
	memcpy((uint8_t*)deletechar->CMD_HEAD,CMD_HEAD,2);
	
	memcpy((uint8_t*)deletechar->CMD_ADDR,CMD_ADDR,4);
	
	deletechar->TYPE = ID_CMD;
	
	deletechar->LEN[0] = DeletCharLen[0];
	
	deletechar->LEN[1] = DeletCharLen[1];
	
	deletechar->CMD = DeletChar;

	deletechar->PAGE_ID[0] = PageID>>8;
	
	deletechar->PAGE_ID[1] = (uint8_t)PageID;

	deletechar->NUM[0] = number>>8;
	
	deletechar->NUM[1] = (uint8_t)number;
	
	checksum = FPM383C_Generate_CMD_Checksum((uint8_t*)&deletechar->TYPE,(deletechar->LEN[0]<<8|deletechar->LEN[1])+CHECKNUM_EXPECT_LEN);
	
	deletechar->CHECKSUM[0] = checksum>>8;
	
	deletechar->CHECKSUM[1] = (uint8_t)checksum;
	
	return OPERATE_SUCCESS;
}

int Generate_Cancel(CMD_Cancel_t *cancel)					//����ȡ��ָ��
{
	uint16_t checksum=0;
	
	memcpy((uint8_t*)cancel->CMD_HEAD,CMD_HEAD,2);
	
	memcpy((uint8_t*)cancel->CMD_ADDR,CMD_ADDR,4);
	
	cancel->TYPE = ID_CMD;
	
	cancel->LEN[0] = CancelLen[0];
	
	cancel->LEN[1] = CancelLen[1];
	
	cancel->CMD = Cancel;

	checksum = FPM383C_Generate_CMD_Checksum((uint8_t*)&cancel->TYPE,(cancel->LEN[0]<<8|cancel->LEN[1])+CHECKNUM_EXPECT_LEN);
	
	cancel->CHECKSUM[0] = checksum>>8;
	
	cancel->CHECKSUM[1] = (uint8_t)checksum;
	
	return OPERATE_SUCCESS;
}

int Generate_Sleep(CMD_Sleep_t* sleep)
{
	uint16_t checksum=0;
	
	memcpy((uint8_t*)sleep->CMD_HEAD,CMD_HEAD,2);
	
	memcpy((uint8_t*)sleep->CMD_ADDR,CMD_ADDR,4);
	
	sleep->TYPE = ID_CMD;
	
	sleep->LEN[0] = SleepLen[0];
	
	sleep->LEN[1] = SleepLen[1];
	
	sleep->CMD = Sleep;

	checksum = FPM383C_Generate_CMD_Checksum((uint8_t*)&sleep->TYPE,(sleep->LEN[0]<<8|sleep->LEN[1])+CHECKNUM_EXPECT_LEN);
	
	sleep->CHECKSUM[0] = checksum>>8;
	
	sleep->CHECKSUM[1] = (uint8_t)checksum;
	
	return OPERATE_SUCCESS;
}


int Generate_ValidTempleteNum(CMD_ValidTempleteNum_t* valid_num)				//���ɶ���Чģ�����ָ��
{
	uint16_t checksum=0;
	
	memcpy((uint8_t*)valid_num->CMD_HEAD,CMD_HEAD,2);
	
	memcpy((uint8_t*)valid_num->CMD_ADDR,CMD_ADDR,4);
	
	valid_num->TYPE = ID_CMD;
	
	valid_num->LEN[0] = ValidTempleteNumLen[0];
	
	valid_num->LEN[1] = ValidTempleteNumLen[1];
	
	valid_num->CMD = ValidTempleteNum;

	checksum = FPM383C_Generate_CMD_Checksum((uint8_t*)&valid_num->TYPE,(valid_num->LEN[0]<<8|valid_num->LEN[1])+CHECKNUM_EXPECT_LEN);
	
	valid_num->CHECKSUM[0] = checksum>>8;
	
	valid_num->CHECKSUM[1] = (uint8_t)checksum;
	
	return OPERATE_SUCCESS;
}

int Generate_ReadIndexTable(CMD_ReadIndexTable_t* read_index_table,uint8_t page)					//���ɶ�������ָ��
{
	uint16_t checksum=0;
	
	memcpy((uint8_t*)read_index_table->CMD_HEAD,CMD_HEAD,2);
	
	memcpy((uint8_t*)read_index_table->CMD_ADDR,CMD_ADDR,4);
	
	read_index_table->TYPE = ID_CMD;
	
	read_index_table->LEN[0] = ReadIndexTableLen[0];
	
	read_index_table->LEN[1] = ReadIndexTableLen[1];
	
	read_index_table->CMD = ReadIndexTable;
	
	read_index_table->PAGE = page;

	checksum = FPM383C_Generate_CMD_Checksum((uint8_t*)&read_index_table->TYPE,(read_index_table->LEN[0]<<8|read_index_table->LEN[1])+CHECKNUM_EXPECT_LEN);
	
	read_index_table->CHECKSUM[0] = checksum>>8;
	
	read_index_table->CHECKSUM[1] = (uint8_t)checksum;
	
	return OPERATE_SUCCESS;
}

int Generate_SetPwd(CMD_SetPwd_t* set_pwd,uint32_t PassWord)			//�������ÿ���
{
	uint16_t checksum=0;
	
	memcpy((uint8_t*)set_pwd->CMD_HEAD,CMD_HEAD,2);
	
	memcpy((uint8_t*)set_pwd->CMD_ADDR,CMD_ADDR,4);
	
	set_pwd->TYPE = ID_CMD;
	
	set_pwd->LEN[0] = SetPwdLen[0];
	
	set_pwd->LEN[1] = SetPwdLen[1];
	
	set_pwd->CMD = SetPwd;
	
	set_pwd->PASSWORD[0] = PassWord>>24;
	
	set_pwd->PASSWORD[0] = PassWord>>16;
	
	set_pwd->PASSWORD[0] = PassWord>>8;
	
	set_pwd->PASSWORD[0] = (uint8_t)PassWord;

	checksum = FPM383C_Generate_CMD_Checksum((uint8_t*)&set_pwd->TYPE,(set_pwd->LEN[0]<<8|set_pwd->LEN[1])+CHECKNUM_EXPECT_LEN);
	
	set_pwd->CHECKSUM[0] = checksum>>8;
	
	set_pwd->CHECKSUM[1] = (uint8_t)checksum;
	
	return OPERATE_SUCCESS;
}

int Generate_VfyPwd(CMD_VfyPwd_t *vfy_pwd,uint32_t PassWord)				//������֤����
{
	uint16_t checksum=0;
	
	memcpy((uint8_t*)vfy_pwd->CMD_HEAD,CMD_HEAD,2);
	
	memcpy((uint8_t*)vfy_pwd->CMD_ADDR,CMD_ADDR,4);
	
	vfy_pwd->TYPE = ID_CMD;
	
	vfy_pwd->LEN[0] = VfyPwdLen[0];
	
	vfy_pwd->LEN[1] = VfyPwdLen[1];
	
	vfy_pwd->CMD = VfyPwd;
	
	vfy_pwd->PASSWORD[0] = PassWord>>24;
	
	vfy_pwd->PASSWORD[0] = PassWord>>16;
	
	vfy_pwd->PASSWORD[0] = PassWord>>8;
	
	vfy_pwd->PASSWORD[0] = (uint8_t)PassWord;

	checksum = FPM383C_Generate_CMD_Checksum((uint8_t*)&vfy_pwd->TYPE,(vfy_pwd->LEN[0]<<8|vfy_pwd->LEN[1])+CHECKNUM_EXPECT_LEN);
	
	vfy_pwd->CHECKSUM[0] = checksum>>8;
	
	vfy_pwd->CHECKSUM[1] = (uint8_t)checksum;
	
	return OPERATE_SUCCESS;
}

int Generate_HandShake(CMD_HandShake_t* hand_shake)				//������������
{
	uint16_t checksum=0;
	
	memcpy((uint8_t*)hand_shake->CMD_HEAD,CMD_HEAD,2);
	
	memcpy((uint8_t*)hand_shake->CMD_ADDR,CMD_ADDR,4);
	
	hand_shake->TYPE = ID_CMD;
	
	hand_shake->LEN[0] = HandShakeLen[0];
	
	hand_shake->LEN[1] = HandShakeLen[1];
	
	hand_shake->CMD = HandShake;

	checksum = FPM383C_Generate_CMD_Checksum((uint8_t*)&hand_shake->TYPE,(hand_shake->LEN[0]<<8|hand_shake->LEN[1])+CHECKNUM_EXPECT_LEN);
	
	hand_shake->CHECKSUM[0] = checksum>>8;
	
	hand_shake->CHECKSUM[1] = (uint8_t)checksum;
	
	return OPERATE_SUCCESS;
}

int Generate_CheckSensor(CMD_CheckSensor_t *check_sensor)
{
	uint16_t checksum=0;
	
	memcpy((uint8_t*)check_sensor->CMD_HEAD,CMD_HEAD,2);
	
	memcpy((uint8_t*)check_sensor->CMD_ADDR,CMD_ADDR,4);
	
	check_sensor->TYPE = ID_CMD;
	
	check_sensor->LEN[0] = CheckSensorLen[0];
	
	check_sensor->LEN[1] = CheckSensorLen[1];
	
	check_sensor->CMD = CheckSensor;

	checksum = FPM383C_Generate_CMD_Checksum((uint8_t*)&check_sensor->TYPE,(check_sensor->LEN[0]<<8|check_sensor->LEN[1])+CHECKNUM_EXPECT_LEN);
	
	check_sensor->CHECKSUM[0] = checksum>>8;
	
	check_sensor->CHECKSUM[1] = (uint8_t)checksum;
	
	return OPERATE_SUCCESS;
}

int Generate_SetChipAddr(CMD_SetChipAddr_t* set_chip_addr,uint32_t Addr)
{
	uint16_t checksum=0;
	
	memcpy((uint8_t*)set_chip_addr->CMD_HEAD,CMD_HEAD,2);
	
	memcpy((uint8_t*)set_chip_addr->CMD_ADDR,CMD_ADDR,4);
	
	set_chip_addr->TYPE = ID_CMD;
	
	set_chip_addr->LEN[0] = SetChipAddrLen[0];
	
	set_chip_addr->LEN[1] = SetChipAddrLen[1];
	
	set_chip_addr->CMD = SetChipAddr;
	
	set_chip_addr->DEV_ADDR[0] = Addr>>24;
	
	set_chip_addr->DEV_ADDR[1] = Addr>>16;
	
	set_chip_addr->DEV_ADDR[2] = Addr>>8;
	
	set_chip_addr->DEV_ADDR[3] = (uint8_t)Addr;

	checksum = FPM383C_Generate_CMD_Checksum((uint8_t*)&set_chip_addr->TYPE,(set_chip_addr->LEN[0]<<8|set_chip_addr->LEN[1])+CHECKNUM_EXPECT_LEN);
	
	set_chip_addr->CHECKSUM[0] = checksum>>8;
	
	set_chip_addr->CHECKSUM[1] = (uint8_t)checksum;
	
	return OPERATE_SUCCESS;
}

int Generate_WriteNotePad(CMD_WriteNotePad_t* write_notepad,uint8_t Page,uint8_t *Content)
{
	uint16_t checksum=0;
	
	memcpy((uint8_t*)write_notepad->CMD_HEAD,CMD_HEAD,2);
	
	memcpy((uint8_t*)write_notepad->CMD_ADDR,CMD_ADDR,4);
	
	write_notepad->TYPE = ID_CMD;
	
	write_notepad->LEN[0] = WriteNotepadLen[0];
	
	write_notepad->LEN[1] = WriteNotepadLen[1];
	
	write_notepad->CMD = WriteNotepad;
	
	write_notepad->PAGE = Page;
	
	memcpy((uint8_t*)write_notepad->CONTENT,Content,32);

	checksum = FPM383C_Generate_CMD_Checksum((uint8_t*)&write_notepad->TYPE,(write_notepad->LEN[0]<<8|write_notepad->LEN[1])+CHECKNUM_EXPECT_LEN);
	
	write_notepad->CHECKSUM[0] = checksum>>8;
	
	write_notepad->CHECKSUM[1] = (uint8_t)checksum;
	
	return OPERATE_SUCCESS;
}

int Generate_ReadNotepad(CMD_ReadNotepad_t* read_notepad,uint8_t Page)
{
	uint16_t checksum=0;
	
	memcpy((uint8_t*)read_notepad->CMD_HEAD,CMD_HEAD,2);
	
	memcpy((uint8_t*)read_notepad->CMD_ADDR,CMD_ADDR,4);
	
	read_notepad->TYPE = ID_CMD;
	
	read_notepad->LEN[0] = ReadNotepadLen[0];
	
	read_notepad->LEN[1] = ReadNotepadLen[1];
	
	read_notepad->CMD = ReadNotepad;
	
	read_notepad->PAGE = Page;

	checksum = FPM383C_Generate_CMD_Checksum((uint8_t*)&read_notepad->TYPE,(read_notepad->LEN[0]<<8|read_notepad->LEN[1])+CHECKNUM_EXPECT_LEN);
	
	read_notepad->CHECKSUM[0] = checksum>>8;
	
	read_notepad->CHECKSUM[1] = (uint8_t)checksum;
	
	return OPERATE_SUCCESS;
}

int Generate_GetImage(CMD_GetImage_t* get_image)		//���ɻ�ȡͼ��ָ��
{
	uint16_t checksum=0;
	
	memcpy((uint8_t*)get_image->CMD_HEAD,CMD_HEAD,2);
	
	memcpy((uint8_t*)get_image->CMD_ADDR,CMD_ADDR,4);
	
	get_image->TYPE = ID_CMD;
	
	get_image->LEN[0] = GetImageLen[0];
	
	get_image->LEN[1] = GetImageLen[1];
	
	get_image->CMD = GetImage;

	checksum = FPM383C_Generate_CMD_Checksum((uint8_t*)&get_image->TYPE,(get_image->LEN[0]<<8|get_image->LEN[1])+CHECKNUM_EXPECT_LEN);
	
	get_image->CHECKSUM[0] = checksum>>8;
	
	get_image->CHECKSUM[1] = (uint8_t)checksum;
	
	return OPERATE_SUCCESS;
}

int Generate_GenChar(CMD_GenChar_t* gen_char,uint8_t BufferID)			//��������ģ��ָ��
{
	uint16_t checksum=0;
	
	memcpy((uint8_t*)gen_char->CMD_HEAD,CMD_HEAD,2);
	
	memcpy((uint8_t*)gen_char->CMD_ADDR,CMD_ADDR,4);
	
	gen_char->TYPE = ID_CMD;
	
	gen_char->LEN[0] = GenCharLen[0];
	
	gen_char->LEN[1] = GenCharLen[1];
	
	gen_char->CMD = GenChar;
	
	gen_char->BUFFER_ID = BufferID;

	checksum = FPM383C_Generate_CMD_Checksum((uint8_t*)&gen_char->TYPE,(gen_char->LEN[0]<<8|gen_char->LEN[1])+CHECKNUM_EXPECT_LEN);
	
	gen_char->CHECKSUM[0] = checksum>>8;
	
	gen_char->CHECKSUM[1] = (uint8_t)checksum;
	
	return OPERATE_SUCCESS;
}

int Generate_RegModel(CMD_RegModel_t* reg_model)				//���ɺϲ�����������ģ�壩ָ��
{
	uint16_t checksum=0;
	
	memcpy((uint8_t*)reg_model->CMD_HEAD,CMD_HEAD,2);
	
	memcpy((uint8_t*)reg_model->CMD_ADDR,CMD_ADDR,4);
	
	reg_model->TYPE = ID_CMD;
	
	reg_model->LEN[0] = RegMBLen[0];
	
	reg_model->LEN[1] = RegMBLen[1];
	
	reg_model->CMD = RegMB;
	
	checksum = FPM383C_Generate_CMD_Checksum((uint8_t*)&reg_model->TYPE,(reg_model->LEN[0]<<8|reg_model->LEN[1])+CHECKNUM_EXPECT_LEN);
	
	reg_model->CHECKSUM[0] = checksum>>8;
	
	reg_model->CHECKSUM[1] = (uint8_t)checksum;
	
	return OPERATE_SUCCESS;
}

int Generate_StoreChar(CMD_StoreChar_t* store_char,uint8_t BufferID,uint16_t PageID)
{
	uint16_t checksum=0;
	
	memcpy((uint8_t*)store_char->CMD_HEAD,CMD_HEAD,2);
	
	memcpy((uint8_t*)store_char->CMD_ADDR,CMD_ADDR,4);
	
	store_char->TYPE = ID_CMD;
	
	store_char->LEN[0] = StorMBLen[0];
	
	store_char->LEN[1] = StorMBLen[1];
	
	store_char->CMD = StorMB;
	
	store_char->BUFFER_ID = BufferID;
	
	store_char->PAGE_ID[0] = PageID>>8;
	
	store_char->PAGE_ID[1] = (uint8_t)PageID;
	
	checksum = FPM383C_Generate_CMD_Checksum((uint8_t*)&store_char->TYPE,(store_char->LEN[0]<<8|store_char->LEN[1])+CHECKNUM_EXPECT_LEN);
	
	store_char->CHECKSUM[0] = checksum>>8;
	
	store_char->CHECKSUM[1] = (uint8_t)checksum;
	
	return OPERATE_SUCCESS;
}

int Generate_Match(CMD_Match_t* match)			//��ȷ�Ա�
{
	uint16_t checksum=0;
	
	memcpy((uint8_t*)match->CMD_HEAD,CMD_HEAD,2);
	
	memcpy((uint8_t*)match->CMD_ADDR,CMD_ADDR,4);
	
	match->TYPE = ID_CMD;
	
	match->LEN[0] = MatchLen[0];
	
	match->LEN[1] = MatchLen[1];
	
	match->CMD = Match;
	
	checksum = FPM383C_Generate_CMD_Checksum((uint8_t*)&match->TYPE,(match->LEN[0]<<8|match->LEN[1])+CHECKNUM_EXPECT_LEN);
	
	match->CHECKSUM[0] = checksum>>8;
	
	match->CHECKSUM[1] = (uint8_t)checksum;
	
	return OPERATE_SUCCESS;
}

int Generate_ControlBLN(CMD_ControlBLN_t* control_bln,_LED_Function_t func,uint8_t startColor,uint8_t endColor,uint8_t cycle)
{
	uint16_t checksum=0;
	
	memcpy((uint8_t*)control_bln->CMD_HEAD,CMD_HEAD,2);
	
	memcpy((uint8_t*)control_bln->CMD_ADDR,CMD_ADDR,4);
	
	control_bln->TYPE = ID_CMD;
	
	control_bln->LEN[0] = ControlBLNLen[0];
	
	control_bln->LEN[1] = ControlBLNLen[1];
	
	control_bln->CMD = ControlBLN;
	
	control_bln->FUNC = func;
	
	control_bln->S_COLOR = startColor;
	
	control_bln->E_COLOR = endColor;
	
	control_bln->CYCLE_TIME = cycle;
	
	checksum = FPM383C_Generate_CMD_Checksum((uint8_t*)&control_bln->TYPE,(control_bln->LEN[0]<<8|control_bln->LEN[1])+CHECKNUM_EXPECT_LEN);
	
	control_bln->CHECKSUM[0] = checksum>>8;
	
	control_bln->CHECKSUM[1] = (uint8_t)checksum;
	
	return OPERATE_SUCCESS;
}

int Generate_ControlBLN_Program(CMD_ControlBLN_PRO_t* control_bln_pro,uint8_t time,uint8_t color_1,uint8_t color_2,uint8_t color_3,uint8_t color_4,uint8_t color_5,uint8_t cycle)
{
	uint16_t checksum=0;
	
	memcpy((uint8_t*)control_bln_pro->CMD_HEAD,CMD_HEAD,2);
	
	memcpy((uint8_t*)control_bln_pro->CMD_ADDR,CMD_ADDR,4);
	
	control_bln_pro->TYPE = ID_CMD;
	
	control_bln_pro->LEN[0] = ControlBLN_PROLen[0];
	
	control_bln_pro->LEN[1] = ControlBLN_PROLen[1];
	
	control_bln_pro->CMD = ControlBLN_PRO;
	
	control_bln_pro->FUNC = 7;
	
	control_bln_pro->TIME = time;
	
	control_bln_pro->COLOR1 = color_1;
	control_bln_pro->COLOR2 = color_2;
	control_bln_pro->COLOR3 = color_3;
	control_bln_pro->COLOR4 = color_4;
	control_bln_pro->COLOR5 = color_5;
	
	control_bln_pro->CYCLE_TIME = cycle;
	
	checksum = FPM383C_Generate_CMD_Checksum((uint8_t*)&control_bln_pro->TYPE,(control_bln_pro->LEN[0]<<8|control_bln_pro->LEN[1])+CHECKNUM_EXPECT_LEN);
	
	control_bln_pro->CHECKSUM[0] = checksum>>8;
	
	control_bln_pro->CHECKSUM[1] = (uint8_t)checksum;
	
	return OPERATE_SUCCESS;
}




