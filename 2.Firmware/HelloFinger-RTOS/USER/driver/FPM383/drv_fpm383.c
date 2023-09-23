#include "drv_fpm383.h"
#include "app_task_key.h"
static void CMD_Init(void);
static uint16_t Generate_CMD_Checksum(uint8_t * cmd,uint16_t len);

uint8_t CMD_HEAD[2] =	{0xEF,0x01};						//包头
uint8_t CMD_ADDR[4] =	{0xFF,0xFF,0xFF,0xFF};	//芯片地址，默认0xffffffff
uint8_t CMD_HEAD_ADDR[6] = {0xEF,0x01,0xFF,0xFF,0xFF,0xFF};


CMD_AutoEnroll_t 				g_autoenroll 				= {0};	//自动注册模板结构体
CMD_AutoIdentify_t 			g_autoidentify 			= {0};	//自动验证指纹结构体
CMD_DeleteChar_t 				g_deletechar 				= {0};	//删除模板结构体
CMD_Cancel_t						g_cancel						= {0};	//取消指令结构体
CMD_Sleep_t							g_sleep							= {0};	//休眠指令结构体
CMD_ValidTempleteNum_t 	g_valid_num  				= {0};	//读有效模板个数结构体
CMD_ReadIndexTable_t	 	g_read_index_table 	= {0};	//读索引表结构体
CMD_SetPwd_t						g_set_pwd						= {0};	//设置口令结构体
CMD_VfyPwd_t						g_vfy_pwd						= {0};	//验证口令结构体
CMD_HandShake_t					g_hand_shake				= {0};	//握手指令结构体
CMD_CheckSensor_t				g_check_sensor			= {0};	//校验传感器指令结构体
CMD_SetChipAddr_t				g_set_chip_addr 		= {0};	//设置设备地址结构体
CMD_WriteNotePad_t			g_write_notepad 		= {0};	//写记事本结构体
CMD_ReadNotepad_t   		g_read_notepad  		= {0};	//读记事本结构体
CMD_GetImage_t					g_get_image					= {0};	//获取图像结构体
CMD_GenChar_t						g_gen_char					= {0};	//生成特征结构体
CMD_RegModel_t					g_reg_model					= {0};	//合并模板结构体
CMD_StoreChar_t					g_store_char				= {0};	//存储模板结构体
CMD_Match_t							g_match							= {0};	//精确对比结构体
CMD_ControlBLN_t				g_control_bln				=	{0};	//控制LED
CMD_ControlBLN_PRO_t		g_control_bln_pro		= {0};	//控制七彩LED


/*******************指令码**********************/													/***********************指令码长度*************************/
const uint8_t				AutoEnroll						=				0x31;		/*自动注册模板*/			const uint8_t 			AutoEnrollLen[2]					=				{0x00,0x08};
const uint8_t				AutoIdentify					=				0x32;		/*自动验证指纹*/			const uint8_t				AutoIdentifyLen[2]				=				{0x00,0x08};
const uint8_t				DeletChar							=				0x0C;		/*删除模板*/     			const uint8_t				DeletCharLen[2]						=				{0x00,0x07};
const uint8_t				Empty									=				0x0D;		/*清空指纹库*/     		const uint8_t				EmptyLen[2]								=				{0x00,0x03};
const uint8_t				Cancel								=				0x30;		/*取消指令*/     			const uint8_t				CancelLen[2]							=				{0x00,0x03};
const uint8_t				Sleep									=				0x33;		/*休眠指令*/     			const uint8_t				SleepLen[2]								=				{0x00,0x03};
const uint8_t				ValidTempleteNum			=				0x1D;		/*读有效模板个数*/   	const uint8_t				ValidTempleteNumLen[2]		=				{0x00,0x03};
const uint8_t				ReadIndexTable				=				0x1F;		/*读索引表*/     			const uint8_t				ReadIndexTableLen[2]			=				{0x00,0x04};
const uint8_t				SetPwd								=				0x12;		/*设置口令*/     			const uint8_t				SetPwdLen[2]							=				{0x00,0x07};
const uint8_t				VfyPwd								=				0x13;		/*验证口令*/     			const uint8_t				VfyPwdLen[2]							=				{0x00,0x07};
const uint8_t				GetImage							=				0x01;		/*获取图像*/     			const uint8_t				GetImageLen[2]						=				{0x00,0x03};
const uint8_t				GetRnrollImage				=				0x29;		/*注册用获取图像*/   	const uint8_t				GetRnrollImageLen[2]			=				{0x00,0x03};
const uint8_t				GenChar								=				0x02;		/*生成特征*/     			const uint8_t				GenCharLen[2]							=				{0x00,0x04};
const uint8_t				Match									=				0x03;		/*精确对比 */					const uint8_t				MatchLen[2]								=				{0x00,0x03};
const uint8_t				RegMB									=				0x05;		/*合并模板*/     			const uint8_t				RegMBLen[2]								=				{0x00,0x03};
const uint8_t				StorMB								=				0x06;		/*存储模板*/     			const uint8_t				StorMBLen[2]              =				{0x00,0x06};
const uint8_t				SearchMB							=				0x04;		/*搜索模板*/     			const uint8_t				SearchMBLen[2]            =       {0x00,0x08};
const uint8_t				GetChipUID						=				0x34;		/*获取芯片序列号*/   	const uint8_t				GetChipUIDLen[2]          =       {0x00,0x03};
const uint8_t				GetChipEcho						=				0x35;		/*握手命令*/     			const uint8_t				GetChipEchoLen[2]         =       {0x00,0x03};
const uint8_t				AutoCaiSensor					=				0x36;		/*校验传感器*/    		const uint8_t				AutoCaiSensorLen[2]       =       {0x00,0x03};
const uint8_t				UpImage								=				0x0A;		/*上传图像*/    	 		const uint8_t				UpImageLen[2]             =       {0x00,0x03};
const uint8_t       ReadSysPara						=				0x16;		/*读取系统基本参数*/ 	const uint8_t				ReadSysParaLen[2]         =       {0x00,0x03};
const uint8_t				ControlBLN						=				0x3C;		/*三色灯指令*/     		const uint8_t				ControlBLNLen[2]          =       {0x00,0x07};
const uint8_t				ControlBLN_PRO				=				0x3C;		/* 七彩灯 */					const uint8_t				ControlBLN_PROLen[2]			= 			{0x00,0x0B};
const uint8_t				FingerCharUp					=				0x07;		/*特征上传*/     			const uint8_t				FingerCharUpLen[2]        =       {0x00,0x03};
const uint8_t				FingerCharDown				=				0x08;		/*特征下载*/     		//const uint8_t				FingerCharDownLen[2]      =       {0x00,0x0} ;
const uint8_t 			FingerMoudleSet				=				0x0E;		/*模组设置*/     			const uint8_t				FingerMoudleSetLen[2]     =       {0x00,0x05};
const uint8_t				GetDummyTempleteNo		=				0x68;		/*获取空白存储*/     	const uint8_t				GetDummyTempleteNoLen[2]  =       {0x00,0x03};
const uint8_t				GetFingerMoudleVersion=				0x73;		/*获取模组固件版本*/ 	const uint8_t				GetFingerMoudleVersionLen[2]=     {0x00,0x03};


const uint8_t 			GetChipSN							=				0x34;		/*获取芯片唯一序列号*/const uint8_t				GetChipSNLen[2]						=				{0x00,0x04};
const uint8_t				HandShake							=				0x35;		/*握手指令*/					const uint8_t				HandShakeLen[2]						=				{0x00,0x03};
const uint8_t 			CheckSensor						=				0x36;		/*校验传感器指令 */		const uint8_t 			CheckSensorLen[2]					=				{0x00,0x03};
const uint8_t 			SetChipAddr						=				0x15;		/*设置设备地址*/			const uint8_t				SetChipAddrLen[2]					=				{0x00,0x07};
const uint8_t 			WriteNotepad					=				0x18;		/*写记事本*/					const uint8_t				WriteNotepadLen[2]				=				{0x00,0x24};
const uint8_t 			ReadNotepad						=				0x19;		/*读记事本*/					const uint8_t				ReadNotepadLen[2]					=				{0x00,0x04};

/************************************************************************************************************************************/

void FPM383C_Init(void)
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
	
	CMD_Init();
	
	Generate_Sleep();
	
	HAL_UART_Transmit(&FINGER_HANDLE,(uint8_t*)&g_sleep,g_sleep.LEN[0]<<8|g_sleep.LEN[1]+FIXED_CMD_LEN,1000);
	
}

static void CMD_Init(void)	//初始化包头和设备地址，后期可从EEPROM中读取
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

static uint16_t Generate_CMD_Checksum(uint8_t * cmd,uint16_t len)
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
void Generate_AutoEnroll(uint16_t ID,uint8_t enrollTimes,uint16_t PARAM)		//生成自动注册模板指令
{
	uint16_t checksum = 0;
	
	memcpy((uint8_t*)g_autoenroll.CMD_HEAD,CMD_HEAD,2);
	
	memcpy((uint8_t*)g_autoenroll.CMD_ADDR,CMD_ADDR,4);
	
	g_autoenroll.TYPE = ID_CMD;
	
	g_autoenroll.LEN[0] = AutoEnrollLen[0];
	
	g_autoenroll.LEN[1] = AutoEnrollLen[1];
	
	g_autoenroll.CMD = AutoEnroll;
	
	g_autoenroll.ID[0] = ID>>8;
	
	g_autoenroll.ID[1] = (uint8_t)ID;
	
	g_autoenroll.ENROLL_TIMES = enrollTimes;
	
	g_autoenroll.PARAM[0] = PARAM>>8;
	
	g_autoenroll.PARAM[1] = (uint8_t)PARAM;
	
	checksum = Generate_CMD_Checksum((uint8_t*)&g_autoenroll.TYPE,(g_autoenroll.LEN[0]<<8|g_autoenroll.LEN[1])+CHECKNUM_EXPECT_LEN);
	
	g_autoenroll.CHECKSUM[0] = checksum>>8;
	
	g_autoenroll.CHECKSUM[1] = (uint8_t)checksum;
	
}

void Generate_AutoIdentify(uint8_t secureleval,uint16_t ID,uint16_t PARAM)				//生成自动验证指纹指令
{
	uint16_t checksum=0;
	
	memcpy((uint8_t*)g_autoidentify.CMD_HEAD,CMD_HEAD,2);
	
	memcpy((uint8_t*)g_autoidentify.CMD_ADDR,CMD_ADDR,4);
	
	g_autoidentify.TYPE = ID_CMD;
	
	g_autoidentify.LEN[0] = AutoIdentifyLen[0];
	
	g_autoidentify.LEN[1] = AutoIdentifyLen[1];
	
	g_autoidentify.CMD = AutoIdentify;
	
	g_autoidentify.LEVEL = secureleval;
	
	g_autoidentify.ID[0] = ID>>8;
	
	g_autoidentify.ID[1] = (uint8_t)ID;

	g_autoidentify.PARAM[0] = PARAM>>8;
	
	g_autoidentify.PARAM[1] = (uint8_t)PARAM;
	
	checksum = Generate_CMD_Checksum((uint8_t*)&g_autoidentify.TYPE,(g_autoidentify.LEN[0]<<8|g_autoidentify.LEN[1])+CHECKNUM_EXPECT_LEN);
	
	g_autoidentify.CHECKSUM[0] = checksum>>8;
	
	g_autoidentify.CHECKSUM[1] = (uint8_t)checksum;
}

void Generate_DeletChar(uint16_t PageID,uint16_t number)		//生成删除模板指令
{
	uint16_t checksum=0;
	
	memcpy((uint8_t*)g_deletechar.CMD_HEAD,CMD_HEAD,2);
	
	memcpy((uint8_t*)g_deletechar.CMD_ADDR,CMD_ADDR,4);
	
	g_deletechar.TYPE = ID_CMD;
	
	g_deletechar.LEN[0] = DeletCharLen[0];
	
	g_deletechar.LEN[1] = DeletCharLen[1];
	
	g_deletechar.CMD = DeletChar;

	g_deletechar.PAGE_ID[0] = PageID>>8;
	
	g_deletechar.PAGE_ID[1] = (uint8_t)PageID;

	g_deletechar.NUM[0] = number>>8;
	
	g_deletechar.NUM[1] = (uint8_t)number;
	
	checksum = Generate_CMD_Checksum((uint8_t*)&g_deletechar.TYPE,(g_deletechar.LEN[0]<<8|g_deletechar.LEN[1])+CHECKNUM_EXPECT_LEN);
	
	g_deletechar.CHECKSUM[0] = checksum>>8;
	
	g_deletechar.CHECKSUM[1] = (uint8_t)checksum;
}

void Generate_Cancel(void)					//生成取消指令
{
	uint16_t checksum=0;
	
	memcpy((uint8_t*)g_cancel.CMD_HEAD,CMD_HEAD,2);
	
	memcpy((uint8_t*)g_cancel.CMD_ADDR,CMD_ADDR,4);
	
	g_cancel.TYPE = ID_CMD;
	
	g_cancel.LEN[0] = CancelLen[0];
	
	g_cancel.LEN[1] = CancelLen[1];
	
	g_cancel.CMD = Cancel;

	checksum = Generate_CMD_Checksum((uint8_t*)&g_cancel.TYPE,(g_cancel.LEN[0]<<8|g_cancel.LEN[1])+CHECKNUM_EXPECT_LEN);
	
	g_cancel.CHECKSUM[0] = checksum>>8;
	
	g_cancel.CHECKSUM[1] = (uint8_t)checksum;
}

void Generate_Sleep(void)
{
	uint16_t checksum=0;
	
	memcpy((uint8_t*)g_sleep.CMD_HEAD,CMD_HEAD,2);
	
	memcpy((uint8_t*)g_sleep.CMD_ADDR,CMD_ADDR,4);
	
	g_sleep.TYPE = ID_CMD;
	
	g_sleep.LEN[0] = SleepLen[0];
	
	g_sleep.LEN[1] = SleepLen[1];
	
	g_sleep.CMD = Sleep;

	checksum = Generate_CMD_Checksum((uint8_t*)&g_sleep.TYPE,(g_sleep.LEN[0]<<8|g_sleep.LEN[1])+CHECKNUM_EXPECT_LEN);
	
	g_sleep.CHECKSUM[0] = checksum>>8;
	
	g_sleep.CHECKSUM[1] = (uint8_t)checksum;
}


void Generate_ValidTempleteNum(void)				//生成读有效模板个数指令
{
	uint16_t checksum=0;
	
	memcpy((uint8_t*)g_valid_num.CMD_HEAD,CMD_HEAD,2);
	
	memcpy((uint8_t*)g_valid_num.CMD_ADDR,CMD_ADDR,4);
	
	g_valid_num.TYPE = ID_CMD;
	
	g_valid_num.LEN[0] = ValidTempleteNumLen[0];
	
	g_valid_num.LEN[1] = ValidTempleteNumLen[1];
	
	g_valid_num.CMD = ValidTempleteNum;

	checksum = Generate_CMD_Checksum((uint8_t*)&g_valid_num.TYPE,(g_valid_num.LEN[0]<<8|g_valid_num.LEN[1])+CHECKNUM_EXPECT_LEN);
	
	g_valid_num.CHECKSUM[0] = checksum>>8;
	
	g_valid_num.CHECKSUM[1] = (uint8_t)checksum;
}

void Generate_ReadIndexTable(uint8_t page)					//生成读索引表指令
{
	uint16_t checksum=0;
	
	memcpy((uint8_t*)g_read_index_table.CMD_HEAD,CMD_HEAD,2);
	
	memcpy((uint8_t*)g_read_index_table.CMD_ADDR,CMD_ADDR,4);
	
	g_read_index_table.TYPE = ID_CMD;
	
	g_read_index_table.LEN[0] = ReadIndexTableLen[0];
	
	g_read_index_table.LEN[1] = ReadIndexTableLen[1];
	
	g_read_index_table.CMD = ReadIndexTable;
	
	g_read_index_table.PAGE = page;

	checksum = Generate_CMD_Checksum((uint8_t*)&g_read_index_table.TYPE,(g_read_index_table.LEN[0]<<8|g_read_index_table.LEN[1])+CHECKNUM_EXPECT_LEN);
	
	g_read_index_table.CHECKSUM[0] = checksum>>8;
	
	g_read_index_table.CHECKSUM[1] = (uint8_t)checksum;
}

void Generate_SetPwd(uint32_t PassWord)			//生成设置口令
{
	uint16_t checksum=0;
	
	memcpy((uint8_t*)g_set_pwd.CMD_HEAD,CMD_HEAD,2);
	
	memcpy((uint8_t*)g_set_pwd.CMD_ADDR,CMD_ADDR,4);
	
	g_set_pwd.TYPE = ID_CMD;
	
	g_set_pwd.LEN[0] = SetPwdLen[0];
	
	g_set_pwd.LEN[1] = SetPwdLen[1];
	
	g_set_pwd.CMD = SetPwd;
	
	g_set_pwd.PASSWORD[0] = PassWord>>24;
	
	g_set_pwd.PASSWORD[0] = PassWord>>16;
	
	g_set_pwd.PASSWORD[0] = PassWord>>8;
	
	g_set_pwd.PASSWORD[0] = (uint8_t)PassWord;

	checksum = Generate_CMD_Checksum((uint8_t*)&g_set_pwd.TYPE,(g_set_pwd.LEN[0]<<8|g_set_pwd.LEN[1])+CHECKNUM_EXPECT_LEN);
	
	g_set_pwd.CHECKSUM[0] = checksum>>8;
	
	g_set_pwd.CHECKSUM[1] = (uint8_t)checksum;
}

void Generate_VfyPwd(uint32_t PassWord)				//生成验证口令
{
	uint16_t checksum=0;
	
	memcpy((uint8_t*)g_vfy_pwd.CMD_HEAD,CMD_HEAD,2);
	
	memcpy((uint8_t*)g_vfy_pwd.CMD_ADDR,CMD_ADDR,4);
	
	g_vfy_pwd.TYPE = ID_CMD;
	
	g_vfy_pwd.LEN[0] = VfyPwdLen[0];
	
	g_vfy_pwd.LEN[1] = VfyPwdLen[1];
	
	g_vfy_pwd.CMD = VfyPwd;
	
	g_vfy_pwd.PASSWORD[0] = PassWord>>24;
	
	g_vfy_pwd.PASSWORD[0] = PassWord>>16;
	
	g_vfy_pwd.PASSWORD[0] = PassWord>>8;
	
	g_vfy_pwd.PASSWORD[0] = (uint8_t)PassWord;

	checksum = Generate_CMD_Checksum((uint8_t*)&g_vfy_pwd.TYPE,(g_vfy_pwd.LEN[0]<<8|g_vfy_pwd.LEN[1])+CHECKNUM_EXPECT_LEN);
	
	g_vfy_pwd.CHECKSUM[0] = checksum>>8;
	
	g_vfy_pwd.CHECKSUM[1] = (uint8_t)checksum;
}

void Generate_HandShake(void)				//生成握手命令
{
	uint16_t checksum=0;
	
	memcpy((uint8_t*)g_hand_shake.CMD_HEAD,CMD_HEAD,2);
	
	memcpy((uint8_t*)g_hand_shake.CMD_ADDR,CMD_ADDR,4);
	
	g_hand_shake.TYPE = ID_CMD;
	
	g_hand_shake.LEN[0] = HandShakeLen[0];
	
	g_hand_shake.LEN[1] = HandShakeLen[1];
	
	g_hand_shake.CMD = HandShake;

	checksum = Generate_CMD_Checksum((uint8_t*)&g_hand_shake.TYPE,(g_hand_shake.LEN[0]<<8|g_hand_shake.LEN[1])+CHECKNUM_EXPECT_LEN);
	
	g_hand_shake.CHECKSUM[0] = checksum>>8;
	
	g_hand_shake.CHECKSUM[1] = (uint8_t)checksum;
}

void Generate_CheckSensor(void)
{
	uint16_t checksum=0;
	
	memcpy((uint8_t*)g_check_sensor.CMD_HEAD,CMD_HEAD,2);
	
	memcpy((uint8_t*)g_check_sensor.CMD_ADDR,CMD_ADDR,4);
	
	g_check_sensor.TYPE = ID_CMD;
	
	g_check_sensor.LEN[0] = CheckSensorLen[0];
	
	g_check_sensor.LEN[1] = CheckSensorLen[1];
	
	g_check_sensor.CMD = CheckSensor;

	checksum = Generate_CMD_Checksum((uint8_t*)&g_check_sensor.TYPE,(g_check_sensor.LEN[0]<<8|g_check_sensor.LEN[1])+CHECKNUM_EXPECT_LEN);
	
	g_check_sensor.CHECKSUM[0] = checksum>>8;
	
	g_check_sensor.CHECKSUM[1] = (uint8_t)checksum;
}

void Generate_SetChipAddr(uint32_t Addr)
{
	uint16_t checksum=0;
	
	memcpy((uint8_t*)g_set_chip_addr.CMD_HEAD,CMD_HEAD,2);
	
	memcpy((uint8_t*)g_set_chip_addr.CMD_ADDR,CMD_ADDR,4);
	
	g_set_chip_addr.TYPE = ID_CMD;
	
	g_set_chip_addr.LEN[0] = SetChipAddrLen[0];
	
	g_set_chip_addr.LEN[1] = SetChipAddrLen[1];
	
	g_set_chip_addr.CMD = SetChipAddr;
	
	g_set_chip_addr.DEV_ADDR[0] = Addr>>24;
	
	g_set_chip_addr.DEV_ADDR[1] = Addr>>16;
	
	g_set_chip_addr.DEV_ADDR[2] = Addr>>8;
	
	g_set_chip_addr.DEV_ADDR[3] = (uint8_t)Addr;

	checksum = Generate_CMD_Checksum((uint8_t*)&g_set_chip_addr.TYPE,(g_set_chip_addr.LEN[0]<<8|g_set_chip_addr.LEN[1])+CHECKNUM_EXPECT_LEN);
	
	g_set_chip_addr.CHECKSUM[0] = checksum>>8;
	
	g_set_chip_addr.CHECKSUM[1] = (uint8_t)checksum;
}

void Generate_WriteNotePad(uint8_t Page,uint8_t *Content)
{
	uint16_t checksum=0;
	
	memcpy((uint8_t*)g_write_notepad.CMD_HEAD,CMD_HEAD,2);
	
	memcpy((uint8_t*)g_write_notepad.CMD_ADDR,CMD_ADDR,4);
	
	g_write_notepad.TYPE = ID_CMD;
	
	g_write_notepad.LEN[0] = WriteNotepadLen[0];
	
	g_write_notepad.LEN[1] = WriteNotepadLen[1];
	
	g_write_notepad.CMD = WriteNotepad;
	
	g_write_notepad.PAGE = Page;
	
	memcpy((uint8_t*)g_write_notepad.CONTENT,Content,32);

	checksum = Generate_CMD_Checksum((uint8_t*)&g_write_notepad.TYPE,(g_write_notepad.LEN[0]<<8|g_write_notepad.LEN[1])+CHECKNUM_EXPECT_LEN);
	
	g_write_notepad.CHECKSUM[0] = checksum>>8;
	
	g_write_notepad.CHECKSUM[1] = (uint8_t)checksum;
}

void Generate_ReadNotepad(uint8_t Page)
{
	uint16_t checksum=0;
	
	memcpy((uint8_t*)g_read_notepad.CMD_HEAD,CMD_HEAD,2);
	
	memcpy((uint8_t*)g_read_notepad.CMD_ADDR,CMD_ADDR,4);
	
	g_read_notepad.TYPE = ID_CMD;
	
	g_read_notepad.LEN[0] = ReadNotepadLen[0];
	
	g_read_notepad.LEN[1] = ReadNotepadLen[1];
	
	g_read_notepad.CMD = ReadNotepad;
	
	g_read_notepad.PAGE = Page;

	checksum = Generate_CMD_Checksum((uint8_t*)&g_read_notepad.TYPE,(g_read_notepad.LEN[0]<<8|g_read_notepad.LEN[1])+CHECKNUM_EXPECT_LEN);
	
	g_read_notepad.CHECKSUM[0] = checksum>>8;
	
	g_read_notepad.CHECKSUM[1] = (uint8_t)checksum;
}

void Generate_GetImage(void)		//生成获取图像指令
{
	uint16_t checksum=0;
	
	memcpy((uint8_t*)g_get_image.CMD_HEAD,CMD_HEAD,2);
	
	memcpy((uint8_t*)g_get_image.CMD_ADDR,CMD_ADDR,4);
	
	g_get_image.TYPE = ID_CMD;
	
	g_get_image.LEN[0] = GetImageLen[0];
	
	g_get_image.LEN[1] = GetImageLen[1];
	
	g_get_image.CMD = GetImage;

	checksum = Generate_CMD_Checksum((uint8_t*)&g_get_image.TYPE,(g_get_image.LEN[0]<<8|g_get_image.LEN[1])+CHECKNUM_EXPECT_LEN);
	
	g_get_image.CHECKSUM[0] = checksum>>8;
	
	g_get_image.CHECKSUM[1] = (uint8_t)checksum;
}

void Generate_GenChar(uint8_t BufferID)			//生成生成模板指令
{
	uint16_t checksum=0;
	
	memcpy((uint8_t*)g_gen_char.CMD_HEAD,CMD_HEAD,2);
	
	memcpy((uint8_t*)g_gen_char.CMD_ADDR,CMD_ADDR,4);
	
	g_gen_char.TYPE = ID_CMD;
	
	g_gen_char.LEN[0] = GenCharLen[0];
	
	g_gen_char.LEN[1] = GenCharLen[1];
	
	g_gen_char.CMD = GenChar;
	
	g_gen_char.BUFFER_ID = BufferID;

	checksum = Generate_CMD_Checksum((uint8_t*)&g_gen_char.TYPE,(g_gen_char.LEN[0]<<8|g_gen_char.LEN[1])+CHECKNUM_EXPECT_LEN);
	
	g_gen_char.CHECKSUM[0] = checksum>>8;
	
	g_gen_char.CHECKSUM[1] = (uint8_t)checksum;
}

void Generate_RegModel(void)				//生成合并特征（生成模板）指令
{
	uint16_t checksum=0;
	
	memcpy((uint8_t*)g_reg_model.CMD_HEAD,CMD_HEAD,2);
	
	memcpy((uint8_t*)g_reg_model.CMD_ADDR,CMD_ADDR,4);
	
	g_reg_model.TYPE = ID_CMD;
	
	g_reg_model.LEN[0] = RegMBLen[0];
	
	g_reg_model.LEN[1] = RegMBLen[1];
	
	g_reg_model.CMD = RegMB;
	
	checksum = Generate_CMD_Checksum((uint8_t*)&g_reg_model.TYPE,(g_reg_model.LEN[0]<<8|g_reg_model.LEN[1])+CHECKNUM_EXPECT_LEN);
	
	g_reg_model.CHECKSUM[0] = checksum>>8;
	
	g_reg_model.CHECKSUM[1] = (uint8_t)checksum;
}

void Generate_StoreChar(uint8_t BufferID,uint16_t PageID)
{
	uint16_t checksum=0;
	
	memcpy((uint8_t*)g_store_char.CMD_HEAD,CMD_HEAD,2);
	
	memcpy((uint8_t*)g_store_char.CMD_ADDR,CMD_ADDR,4);
	
	g_store_char.TYPE = ID_CMD;
	
	g_store_char.LEN[0] = StorMBLen[0];
	
	g_store_char.LEN[1] = StorMBLen[1];
	
	g_store_char.CMD = StorMB;
	
	g_store_char.BUFFER_ID = BufferID;
	
	g_store_char.PAGE_ID[0] = PageID>>8;
	
	g_store_char.PAGE_ID[1] = (uint8_t)PageID;
	
	checksum = Generate_CMD_Checksum((uint8_t*)&g_store_char.TYPE,(g_store_char.LEN[0]<<8|g_store_char.LEN[1])+CHECKNUM_EXPECT_LEN);
	
	g_store_char.CHECKSUM[0] = checksum>>8;
	
	g_store_char.CHECKSUM[1] = (uint8_t)checksum;
}

void Generate_Match(void)			//精确对比
{
	uint16_t checksum=0;
	
	memcpy((uint8_t*)g_match.CMD_HEAD,CMD_HEAD,2);
	
	memcpy((uint8_t*)g_match.CMD_ADDR,CMD_ADDR,4);
	
	g_match.TYPE = ID_CMD;
	
	g_match.LEN[0] = MatchLen[0];
	
	g_match.LEN[1] = MatchLen[1];
	
	g_match.CMD = Match;
	
	checksum = Generate_CMD_Checksum((uint8_t*)&g_match.TYPE,(g_match.LEN[0]<<8|g_match.LEN[1])+CHECKNUM_EXPECT_LEN);
	
	g_match.CHECKSUM[0] = checksum>>8;
	
	g_match.CHECKSUM[1] = (uint8_t)checksum;
}

void Generate_ControlBLN(_LED_Function_t func,uint8_t startColor,uint8_t endColor,uint8_t cycle)
{
	uint16_t checksum=0;
	
	memcpy((uint8_t*)g_control_bln.CMD_HEAD,CMD_HEAD,2);
	
	memcpy((uint8_t*)g_control_bln.CMD_ADDR,CMD_ADDR,4);
	
	g_control_bln.TYPE = ID_CMD;
	
	g_control_bln.LEN[0] = ControlBLNLen[0];
	
	g_control_bln.LEN[1] = ControlBLNLen[1];
	
	g_control_bln.CMD = ControlBLN;
	
	g_control_bln.FUNC = func;
	
	g_control_bln.S_COLOR = startColor;
	
	g_control_bln.E_COLOR = endColor;
	
	g_control_bln.CYCLE_TIME = cycle;
	
	checksum = Generate_CMD_Checksum((uint8_t*)&g_control_bln.TYPE,(g_control_bln.LEN[0]<<8|g_control_bln.LEN[1])+CHECKNUM_EXPECT_LEN);
	
	g_control_bln.CHECKSUM[0] = checksum>>8;
	
	g_control_bln.CHECKSUM[1] = (uint8_t)checksum;
}

void Generate_ControlBLN_Program(uint8_t time,uint8_t color_1,uint8_t color_2,uint8_t color_3,uint8_t color_4,uint8_t color_5,uint8_t cycle)
{
	uint16_t checksum=0;
	
	memcpy((uint8_t*)g_control_bln_pro.CMD_HEAD,CMD_HEAD,2);
	
	memcpy((uint8_t*)g_control_bln_pro.CMD_ADDR,CMD_ADDR,4);
	
	g_control_bln_pro.TYPE = ID_CMD;
	
	g_control_bln_pro.LEN[0] = ControlBLN_PROLen[0];
	
	g_control_bln_pro.LEN[1] = ControlBLN_PROLen[1];
	
	g_control_bln_pro.CMD = ControlBLN_PRO;
	
	g_control_bln_pro.FUNC = 7;
	
	g_control_bln_pro.TIME = time;
	
	g_control_bln_pro.COLOR1 = color_1;
	g_control_bln_pro.COLOR2 = color_2;
	g_control_bln_pro.COLOR3 = color_3;
	g_control_bln_pro.COLOR4 = color_4;
	g_control_bln_pro.COLOR5 = color_5;
	
	g_control_bln_pro.CYCLE_TIME = cycle;
	
	checksum = Generate_CMD_Checksum((uint8_t*)&g_control_bln_pro.TYPE,(g_control_bln_pro.LEN[0]<<8|g_control_bln_pro.LEN[1])+CHECKNUM_EXPECT_LEN);
	
	g_control_bln_pro.CHECKSUM[0] = checksum>>8;
	
	g_control_bln_pro.CHECKSUM[1] = (uint8_t)checksum;
}




