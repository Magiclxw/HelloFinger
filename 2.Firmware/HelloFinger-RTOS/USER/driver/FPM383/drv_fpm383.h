#ifndef __DRV_FPM383_H
#define __DRV_FPM383_H
#include "sys_config.h"

typedef int(*FUNC_TOUCHRECVTCB)(void);

#define FIXED_CMD_LEN (9)	//固定指令包长度(包头+设备地址+包标识+包长度)


#define	ID_CMD			0x01							//包标识（命令包）
#define	ID_DATA1		0x02							//包标识（数据包）
#define	ID_DATA2	  0x08							//包标识（结束包）
#define ID_RESP			0x07							//包标识（响应包）

#define CONFIRM_OK													(0x00)	//表示指令执行完毕或OK
#define	CONFIRM_REC_ERROR										(0x01)	//表示数据包接收错误
#define CONFIRM_NO_FINGER										(0x02)	//表示传感器上没有手指
#define CONFIRM_RECORD_FAIL 								(0x03)	//表示录入指纹图像失败
#define CONFIRM_IMAGE_DRY_LIGHT							(0x04)	//表示指纹图像太干、太淡而生不成特征
#define CONFIRM_IMAGE_WET_BREEZING					(0x05)	//表示指纹图像太湿、太糊而生不成特征
#define CONFIRM_IMAGE_MESS									(0x06)	//表示指纹图像太乱而生不成特征
#define CONFIRM_IMAGE_LACK									(0x07)	//表示指纹图像正常，但特征点太少（或面积太小）而生不成特征
#define CONFIRM_FINGER_MISS_MATCH						(0x08)	//表示指纹不匹配
#define CONFIRM_FINGER_SEARCH_FAIL					(0x09)	//表示没搜索到指纹
#define CONFIRM_FEATURE_MATCH_FAIL					(0x0A)	//表示特征合并失败
#define CONFIRM_ADDRESS_ERROR								(0x0B)	//表示访问指纹库时地址序号超出指纹库范围
#define CONFIRM_LIBRARY_READ_ERROR					(0x0C)	//表示从指纹库读模板出错或无效
#define CONFIRM_FEATURE_UPLOAD_ERROR				(0x0D)	//表示上传特征失败
#define CONFIRM_REFUSE_FOLLOW_DATA					(0x0E)	//表示模组不能接收后续数据包
#define CONFIRM_IMAGE_UPLOAD_FAIL						(0x0F)	//表示上传图像失败
#define CONFIRM_TEMPLATE_DELETE_FAIL				(0x10)	//表示删除模板失败
#define CONFIRM_CLEAR_LIBRARY_FAIL					(0x11)	//表示清空指纹库失败
#define CONFIRM_ENTER_LOW_POWER_MODE_FAIL		(0x12)	//表示不能进入低功耗状态
#define CONFIRM_CMD_ERROR										(0x13)	//表示口令不正确
#define CONFIRM_RESET_ERROR									(0x14)	//表示系统复位失败
#define CONFIRM_GENERATE_IMAGE_ERROR				(0x15)	//表示缓冲区内没有有效原始图而生不成图像
#define CONFIRM_UPDATE_ERROR								(0x16)	//表示在线升级失败
#define CONFIRM_FINGER_NO_REPLACE						(0x17)	//表示残留指纹或两次采集之间手指没有移动过
#define CONFIRM_FLASH_ERROR									(0x18)	//表示读写 FLASH 出错
#define CONFIRM_RANDOM_NUMBER_GENERATE_FAIL	(0x19)	//随机数生成失败
#define CONFIRM_INVALID_REG_NUMBER					(0x1A)	//无效寄存器号
#define CONFIRM_REG_CONTENT_ERROR						(0x1B)	//寄存器设定内容错误号
#define CONFIRM_NOTEBOOK_PAGE_ERROR					(0x1C)	//记事本页码指定错误
#define CONFIRM_PORT_ERROR									(0x1D)	//端口操作失败
#define CONFIRM_AUTO_ENROLL_FAIL						(0x1E)	//自动注册（enroll）失败
#define CONFIRM_LIBRARY_FULL								(0x1F)	//指纹库满
#define CONFIRM_ADDR_ERROR									(0x20)	//设备地址错误
#define CONFIRM_PASSWORD_ERROR							(0x21)	//密码有误
#define CONFIRM_TEMPLATE_NOT_EMPTY					(0x22)	//指纹模板非空
#define CONFIRM_TEMPLATE_EMPTY							(0x23)	//指纹模板为空
#define CONFIRM_LIBRARY_EMPTY								(0x24)	//指纹库为空
#define CONFIRM_ENROLL_TIMES_ERROR					(0x25)	//录入次数设置错误
#define CONFIRM_TIMEOUT											(0x26)	//超时
#define CONFIRM_FINGER_EXIST								(0x27)	//指纹已存在
#define CONFIRM_FINGER_FERTURE_RELATED			(0x28)	//指纹特征有关联
#define CONFIRM_SENSOR_INIT_FAIL						(0x29)	//传感器初始化失败
#define CONFIRM_DEV_INFO_NOT_EMPTY					(0x2A)	//模组信息非空
#define CONFIRM_DEV_INFO_EMPTY							(0x2B)	//模组信息为空
#define CONFIRM_OPT_FAIL										(0x2C)	//OTP 操作失败
#define CONFIRM_PRIV_KEY_GENERATE_FAIL			(0x2D)	//秘钥生成失败
#define CONFIRM_PRIV_KEY_NOT_EXIST					(0x2E)	//秘钥不存在
#define CONFIRM_SAFE_ALG_EXE_FAIL						(0x2F)	//安全算法执行失败
#define CONFIRM_SAFE_ALG_RESULT_ERROR				(0x30)	//安全算法加解密结果有误
#define CONFIRM_FUNC_SECURE_NOT_MATCH				(0x31)	//功能与加密等级不匹配
#define CONFIRM_PRIV_KEY_LOCK								(0x32)	//秘钥已锁定
#define CONFIRM_IMAGE_SMALL									(0x33)	//图像面积小


#define CHECKNUM_EXPECT_LEN	(1)
/*														指令长度																			*/
#define 					AutoEnrollSize								17
#define 					AutoIdentifySize							17
#define 					DeletCharSize									16
#define 					CancelSize										12
#define						SleepSize											12
#define 					ValidTempleteNumSize					12
#define 					ReadIndexTableSize						13
#define 					SetPwdSize										16
#define 					VfyPwdSize										16
#define 					GetChipEchoSize								12
#define 					AutoCaiSensorSize							12
#define 					ControlBLNSize								16
#define 					GetDummyTempleteNoSize				12

#define 					GetChipSNSize									13
#define 					HandShakeSize									12
#define 					CheckSensorSize								12
#define 					SetChipAddrSize								16
#define 					WriteNotepadSize							45
#define 					ReadNotepadSize								13
#define 					GetImageSize									12
#define 					GenCharSize										13
#define 					RegModelSize									12
#define 					StoreCharSize									15
#define 					MatchSize											12
/****************************************************************************/

#define 					LED_COLOR_BLUE							0x01
#define 					LED_COLOR_GREEN							0x02
#define 					LED_COLOR_RED								0x04

#define AUTOENROLL_PARAM_BACKLIGHT_ON				0x0000
#define AUTOENROLL_PARAM_BACKLIGHT_OFF			0x0001
#define AUTOENROLL_PARAM_PRETREATMENT_ON		0x0002
#define AUTOENROLL_PARAM_PRETREATMENT_OFF		0x0000
#define AUTOENROLL_PARAM_CRITICAL_STATE_ON	0x0000
#define AUTOENROLL_PARAM_CRITICAL_STATE_OFF	0x0004
#define AUTOENROLL_PARAM_ID_COVER_ON				0x0008
#define AUTOENROLL_PARAM_ID_COVER_OFF				0x0000
#define AUTOENROLL_PARAM_ENROLL_REPEAT_ON		0x0000
#define AUTOENROLL_PARAM_ENROLL_REPEAT_OFF	0x0010
#define AUTOENROLL_PARAM_FINGER_MOVE_ON			0x0000
#define AUTOENROLL_PARAM_FINGER_MOVE_OFF		0x0020

typedef enum _LED_Function_
{
	LED_FUNC_BREATHE = 1,
	LED_FUNC_BLINK,
	LED_FUNC_OPEN,
	LED_FUNC_CLOSE,
	LED_FUNC_OPEN_SLOW,
	LED_FUNC_CLOSE_SLOW,
}_LED_Function_t;

typedef struct _CMD_AutoEnroll_
{
	volatile uint8_t CMD_HEAD[2];
	volatile uint8_t CMD_ADDR[4];
	volatile uint8_t TYPE;
	volatile uint8_t LEN[2];
	volatile uint8_t CMD;
	volatile uint8_t ID[2];
	volatile uint8_t ENROLL_TIMES;
	volatile uint8_t PARAM[2];
	volatile uint8_t CHECKSUM[2];
}CMD_AutoEnroll_t;

typedef struct _CMD_AutoIdentify_
{
	volatile uint8_t CMD_HEAD[2];
	volatile uint8_t CMD_ADDR[4];
	volatile uint8_t TYPE;
	volatile uint8_t LEN[2];
	volatile uint8_t CMD;
	volatile uint8_t LEVEL;
	volatile uint8_t ID[2];
	volatile uint8_t PARAM[2];
	volatile uint8_t CHECKSUM[2];
}CMD_AutoIdentify_t;

typedef struct _CMD_DeleteChar_
{
	volatile uint8_t CMD_HEAD[2];
	volatile uint8_t CMD_ADDR[4];
	volatile uint8_t TYPE;
	volatile uint8_t LEN[2];
	volatile uint8_t CMD;
	volatile uint8_t PAGE_ID[2];
	volatile uint8_t NUM[2];
	volatile uint8_t CHECKSUM[2];
}CMD_DeleteChar_t;

typedef struct _CMD_Cancel_
{
	volatile uint8_t CMD_HEAD[2];
	volatile uint8_t CMD_ADDR[4];
	volatile uint8_t TYPE;
	volatile uint8_t LEN[2];
	volatile uint8_t CMD;
	volatile uint8_t CHECKSUM[2];
}CMD_Cancel_t;

typedef struct _CMD_Sleep_
{
	volatile uint8_t CMD_HEAD[2];
	volatile uint8_t CMD_ADDR[4];
	volatile uint8_t TYPE;
	volatile uint8_t LEN[2];
	volatile uint8_t CMD;
	volatile uint8_t CHECKSUM[2];
}CMD_Sleep_t;

typedef struct _CMD_ValidTempleteNum_
{
	volatile uint8_t CMD_HEAD[2];
	volatile uint8_t CMD_ADDR[4];
	volatile uint8_t TYPE;
	volatile uint8_t LEN[2];
	volatile uint8_t CMD;
	volatile uint8_t CHECKSUM[2];
}CMD_ValidTempleteNum_t;

typedef struct _CMD_ReadIndexTable_
{
	volatile uint8_t CMD_HEAD[2];
	volatile uint8_t CMD_ADDR[4];
	volatile uint8_t TYPE;
	volatile uint8_t LEN[2];
	volatile uint8_t CMD;
	volatile uint8_t PAGE;
	volatile uint8_t CHECKSUM[2];
}CMD_ReadIndexTable_t;

typedef struct _CMD_SetPwd_
{
	volatile uint8_t CMD_HEAD[2];
	volatile uint8_t CMD_ADDR[4];
	volatile uint8_t TYPE;
	volatile uint8_t LEN[2];
	volatile uint8_t CMD;
	volatile uint8_t PASSWORD[4];
	volatile uint8_t CHECKSUM[2];
}CMD_SetPwd_t;

typedef struct _CMD_VfyPwd_
{
	volatile uint8_t CMD_HEAD[2];
	volatile uint8_t CMD_ADDR[4];
	volatile uint8_t TYPE;
	volatile uint8_t LEN[2];
	volatile uint8_t CMD;
	volatile uint8_t PASSWORD[4];
	volatile uint8_t CHECKSUM[2];
}CMD_VfyPwd_t;

typedef struct _CMD_HandShake_
{
	volatile uint8_t CMD_HEAD[2];
	volatile uint8_t CMD_ADDR[4];
	volatile uint8_t TYPE;
	volatile uint8_t LEN[2];
	volatile uint8_t CMD;
	volatile uint8_t CHECKSUM[2];
}CMD_HandShake_t;

typedef struct _CMD_CheckSensor_
{
	volatile uint8_t CMD_HEAD[2];
	volatile uint8_t CMD_ADDR[4];
	volatile uint8_t TYPE;
	volatile uint8_t LEN[2];
	volatile uint8_t CMD;
	volatile uint8_t CHECKSUM[2];
}CMD_CheckSensor_t;

typedef struct _CMD_SetChipAddr_
{
	volatile uint8_t CMD_HEAD[2];
	volatile uint8_t CMD_ADDR[4];
	volatile uint8_t TYPE;
	volatile uint8_t LEN[2];
	volatile uint8_t CMD;
	uint8_t DEV_ADDR[4];
	volatile uint8_t CHECKSUM[2];
}CMD_SetChipAddr_t;

typedef struct _CMD_WriteNotePad_
{
	volatile uint8_t CMD_HEAD[2];
	volatile uint8_t CMD_ADDR[4];
	volatile uint8_t TYPE;
	volatile uint8_t LEN[2];
	volatile uint8_t CMD;
	volatile uint8_t PAGE;
	volatile uint8_t CONTENT[32];
	volatile uint8_t CHECKSUM[2];
}CMD_WriteNotePad_t;

typedef struct _CMD_ReadNotepad_
{
	volatile uint8_t CMD_HEAD[2];
	volatile uint8_t CMD_ADDR[4];
	volatile uint8_t TYPE;
	volatile uint8_t LEN[2];
	volatile uint8_t CMD;
	volatile uint8_t PAGE;
	volatile uint8_t CHECKSUM[2];
}CMD_ReadNotepad_t;

typedef struct _CMD_GetImage_
{
	volatile uint8_t CMD_HEAD[2];
	volatile uint8_t CMD_ADDR[4];
	volatile uint8_t TYPE;
	volatile uint8_t LEN[2];
	volatile uint8_t CMD;
	volatile uint8_t CHECKSUM[2];
}CMD_GetImage_t;

typedef struct _CMD_GenChar_
{
	volatile uint8_t CMD_HEAD[2];
	volatile uint8_t CMD_ADDR[4];
	volatile uint8_t TYPE;
	volatile uint8_t LEN[2];
	volatile uint8_t CMD;
	volatile uint8_t BUFFER_ID;
	volatile uint8_t CHECKSUM[2];
}CMD_GenChar_t;

typedef struct _CMD_RegModel_
{
	volatile uint8_t CMD_HEAD[2];
	volatile uint8_t CMD_ADDR[4];
	volatile uint8_t TYPE;
	volatile uint8_t LEN[2];
	volatile uint8_t CMD;
	volatile uint8_t CHECKSUM[2];
}CMD_RegModel_t;

typedef struct _CMD_StoreChar_
{
	volatile uint8_t CMD_HEAD[2];
	volatile uint8_t CMD_ADDR[4];
	volatile uint8_t TYPE;
	volatile uint8_t LEN[2];
	volatile uint8_t CMD;
	volatile uint8_t BUFFER_ID;
	volatile uint8_t PAGE_ID[2];
	volatile uint8_t CHECKSUM[2];
}CMD_StoreChar_t;

typedef struct _CMD_Match_
{
	volatile uint8_t CMD_HEAD[2];
	volatile uint8_t CMD_ADDR[4];
	volatile uint8_t TYPE;
	volatile uint8_t LEN[2];
	volatile uint8_t CMD;
	volatile uint8_t CHECKSUM[2];
}CMD_Match_t;

typedef struct _CMD_ControlBLN_
{
	volatile uint8_t CMD_HEAD[2];
	volatile uint8_t CMD_ADDR[4];
	volatile uint8_t TYPE;
	volatile uint8_t LEN[2];
	volatile uint8_t CMD;
	volatile uint8_t FUNC;
	volatile uint8_t S_COLOR;
	volatile uint8_t E_COLOR;
	volatile uint8_t CYCLE_TIME;	//循环次数
	volatile uint8_t CHECKSUM[2];
}CMD_ControlBLN_t;

typedef struct _CMD_ControlBLN_PRO_
{
	volatile uint8_t CMD_HEAD[2];
	volatile uint8_t CMD_ADDR[4];
	volatile uint8_t TYPE;
	volatile uint8_t LEN[2];
	volatile uint8_t CMD;
	uint8_t FUNC;
	volatile uint8_t TIME;
	volatile uint8_t COLOR1;
	volatile uint8_t COLOR2;
	volatile uint8_t COLOR3;
	volatile uint8_t COLOR4;
	volatile uint8_t COLOR5;
	volatile uint8_t CYCLE_TIME;	//循环次数
	volatile uint8_t CHECKSUM[2];
}CMD_ControlBLN_PRO_t;

typedef enum REG_NUM_
{
	REG_NUM_EnrollTimes = 1,
	REG_NUM_ImageFormat,
	REG_NUM_EnrollMode,
	REG_NUM_Baud,
	REG_NUM_COMP_Level,
	REG_NUM_PackSize,
	REG_NUM_SecureLevel,
}REG_NUM_e;

typedef struct _CMD_WriteReg_
{
	volatile uint8_t CMD_HEAD[2];
	volatile uint8_t CMD_ADDR[4];
	volatile uint8_t TYPE;
	volatile uint8_t LEN[2];
	volatile uint8_t CMD;
	REG_NUM_e reg;
	volatile uint8_t value;
	volatile uint8_t CHECKSUM[2];
}_CMD_WriteReg_t;



int RegisterFingerTouchCallBack(FUNC_TOUCHRECVTCB TOUCHRECVCBT);
int FPM383C_Init(void);
int Generate_AutoEnroll(CMD_AutoEnroll_t* autoenroll,uint16_t ID,uint8_t enrollTimes,uint16_t PARAM);
int Generate_AutoIdentify(CMD_AutoIdentify_t *autoidentify,uint8_t secureleval,uint16_t ID,uint16_t PARAM);
int Generate_StoreChar(CMD_StoreChar_t* store_char,uint8_t BufferID,uint16_t PageID);
int Generate_Sleep(CMD_Sleep_t* sleep);
int Generate_Cancel(CMD_Cancel_t *cancel);
int Generate_ReadIndexTable(CMD_ReadIndexTable_t* read_index_table,uint8_t page);
int Generate_DeletChar(CMD_DeleteChar_t *deletechar,uint16_t PageID,uint16_t number);
int Generate_ControlBLN(CMD_ControlBLN_t* control_bln,_LED_Function_t func,uint8_t startColor,uint8_t endColor,uint8_t cycle);
int Generate_ControlBLN_Program(CMD_ControlBLN_PRO_t* control_bln_pro,uint8_t time,uint8_t color_1,uint8_t color_2,uint8_t color_3,uint8_t color_4,uint8_t color_5,uint8_t cycle);
#endif
