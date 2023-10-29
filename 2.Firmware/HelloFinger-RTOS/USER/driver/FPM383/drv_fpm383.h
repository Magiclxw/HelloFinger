#ifndef __DRV_FPM383_H
#define __DRV_FPM383_H
#include "sys_config.h"

typedef int(*FUNC_TOUCHRECVTCB)(void);

#define FIXED_CMD_LEN (9)	//�̶�ָ�������(��ͷ+�豸��ַ+����ʶ+������)


#define	ID_CMD			0x01							//����ʶ���������
#define	ID_DATA1		0x02							//����ʶ�����ݰ���
#define	ID_DATA2	  0x08							//����ʶ����������
#define ID_RESP			0x07							//����ʶ����Ӧ����

#define CONFIRM_OK													(0x00)	//��ʾָ��ִ����ϻ�OK
#define	CONFIRM_REC_ERROR										(0x01)	//��ʾ���ݰ����մ���
#define CONFIRM_NO_FINGER										(0x02)	//��ʾ��������û����ָ
#define CONFIRM_RECORD_FAIL 								(0x03)	//��ʾ¼��ָ��ͼ��ʧ��
#define CONFIRM_IMAGE_DRY_LIGHT							(0x04)	//��ʾָ��ͼ��̫�ɡ�̫��������������
#define CONFIRM_IMAGE_WET_BREEZING					(0x05)	//��ʾָ��ͼ��̫ʪ��̫��������������
#define CONFIRM_IMAGE_MESS									(0x06)	//��ʾָ��ͼ��̫�Ҷ�����������
#define CONFIRM_IMAGE_LACK									(0x07)	//��ʾָ��ͼ����������������̫�٣������̫С��������������
#define CONFIRM_FINGER_MISS_MATCH						(0x08)	//��ʾָ�Ʋ�ƥ��
#define CONFIRM_FINGER_SEARCH_FAIL					(0x09)	//��ʾû������ָ��
#define CONFIRM_FEATURE_MATCH_FAIL					(0x0A)	//��ʾ�����ϲ�ʧ��
#define CONFIRM_ADDRESS_ERROR								(0x0B)	//��ʾ����ָ�ƿ�ʱ��ַ��ų���ָ�ƿⷶΧ
#define CONFIRM_LIBRARY_READ_ERROR					(0x0C)	//��ʾ��ָ�ƿ��ģ��������Ч
#define CONFIRM_FEATURE_UPLOAD_ERROR				(0x0D)	//��ʾ�ϴ�����ʧ��
#define CONFIRM_REFUSE_FOLLOW_DATA					(0x0E)	//��ʾģ�鲻�ܽ��պ������ݰ�
#define CONFIRM_IMAGE_UPLOAD_FAIL						(0x0F)	//��ʾ�ϴ�ͼ��ʧ��
#define CONFIRM_TEMPLATE_DELETE_FAIL				(0x10)	//��ʾɾ��ģ��ʧ��
#define CONFIRM_CLEAR_LIBRARY_FAIL					(0x11)	//��ʾ���ָ�ƿ�ʧ��
#define CONFIRM_ENTER_LOW_POWER_MODE_FAIL		(0x12)	//��ʾ���ܽ���͹���״̬
#define CONFIRM_CMD_ERROR										(0x13)	//��ʾ�����ȷ
#define CONFIRM_RESET_ERROR									(0x14)	//��ʾϵͳ��λʧ��
#define CONFIRM_GENERATE_IMAGE_ERROR				(0x15)	//��ʾ��������û����Чԭʼͼ��������ͼ��
#define CONFIRM_UPDATE_ERROR								(0x16)	//��ʾ��������ʧ��
#define CONFIRM_FINGER_NO_REPLACE						(0x17)	//��ʾ����ָ�ƻ����βɼ�֮����ָû���ƶ���
#define CONFIRM_FLASH_ERROR									(0x18)	//��ʾ��д FLASH ����
#define CONFIRM_RANDOM_NUMBER_GENERATE_FAIL	(0x19)	//���������ʧ��
#define CONFIRM_INVALID_REG_NUMBER					(0x1A)	//��Ч�Ĵ�����
#define CONFIRM_REG_CONTENT_ERROR						(0x1B)	//�Ĵ����趨���ݴ����
#define CONFIRM_NOTEBOOK_PAGE_ERROR					(0x1C)	//���±�ҳ��ָ������
#define CONFIRM_PORT_ERROR									(0x1D)	//�˿ڲ���ʧ��
#define CONFIRM_AUTO_ENROLL_FAIL						(0x1E)	//�Զ�ע�ᣨenroll��ʧ��
#define CONFIRM_LIBRARY_FULL								(0x1F)	//ָ�ƿ���
#define CONFIRM_ADDR_ERROR									(0x20)	//�豸��ַ����
#define CONFIRM_PASSWORD_ERROR							(0x21)	//��������
#define CONFIRM_TEMPLATE_NOT_EMPTY					(0x22)	//ָ��ģ��ǿ�
#define CONFIRM_TEMPLATE_EMPTY							(0x23)	//ָ��ģ��Ϊ��
#define CONFIRM_LIBRARY_EMPTY								(0x24)	//ָ�ƿ�Ϊ��
#define CONFIRM_ENROLL_TIMES_ERROR					(0x25)	//¼��������ô���
#define CONFIRM_TIMEOUT											(0x26)	//��ʱ
#define CONFIRM_FINGER_EXIST								(0x27)	//ָ���Ѵ���
#define CONFIRM_FINGER_FERTURE_RELATED			(0x28)	//ָ�������й���
#define CONFIRM_SENSOR_INIT_FAIL						(0x29)	//��������ʼ��ʧ��
#define CONFIRM_DEV_INFO_NOT_EMPTY					(0x2A)	//ģ����Ϣ�ǿ�
#define CONFIRM_DEV_INFO_EMPTY							(0x2B)	//ģ����ϢΪ��
#define CONFIRM_OPT_FAIL										(0x2C)	//OTP ����ʧ��
#define CONFIRM_PRIV_KEY_GENERATE_FAIL			(0x2D)	//��Կ����ʧ��
#define CONFIRM_PRIV_KEY_NOT_EXIST					(0x2E)	//��Կ������
#define CONFIRM_SAFE_ALG_EXE_FAIL						(0x2F)	//��ȫ�㷨ִ��ʧ��
#define CONFIRM_SAFE_ALG_RESULT_ERROR				(0x30)	//��ȫ�㷨�ӽ��ܽ������
#define CONFIRM_FUNC_SECURE_NOT_MATCH				(0x31)	//��������ܵȼ���ƥ��
#define CONFIRM_PRIV_KEY_LOCK								(0x32)	//��Կ������
#define CONFIRM_IMAGE_SMALL									(0x33)	//ͼ�����С


#define CHECKNUM_EXPECT_LEN	(1)
/*														ָ���																			*/
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
	volatile uint8_t CYCLE_TIME;	//ѭ������
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
	volatile uint8_t CYCLE_TIME;	//ѭ������
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
