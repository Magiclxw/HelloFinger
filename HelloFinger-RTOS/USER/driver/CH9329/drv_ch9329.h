#ifndef __DRV_CH9329_H
#define __DRV_CH9329_H
#include "sys_config.h"

/* 配置前后需要一定延时 */
#define SET_EN	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_SET)	//CH9329芯片参数配置引脚使能
#define SET_DEN	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_RESET)	//CH9329芯片参数配置引脚禁止

#define CH9329_CHECKSUM_LEN	(2)
#define CH9329_TRANS_MAX_DATA_LEN (65)

/* 协议传输指令类型 */
#define CMD_GET_INFO							0x01
#define CMD_SEND_KB_GENERAL_DATA	0x02
#define CMD_SEND_KB_MEDIA_DATA		0x03
#define CMD_SEND_MS_ABS_DATA			0x04
#define CMD_SEND_MS_REL_DATA			0x05
#define CMD_SEND_MY_HID_DATA			0x06
#define CMD_READ_MY_HID_DATA			0x87
#define CMD_GET_PARA_CFG					0x08
#define CMD_SET_PARA_CFG					0x09
#define CMD_GET_USB_STRING				0x0A

#define CFG_WORKMODE_SOFT_0		0x00
#define CFG_WORKMODE_SOFT_1		0x01
#define CFG_WORKMODE_SOFT_2		0x02
#define CFG_WORKMODE_SOFT_3		0x03
#define CFG_WORKMODE_HARD_0		0x80
#define CFG_WORKMODE_HARD_1		0x81
#define CFG_WORKMODE_HARD_2		0x82
#define CFG_WORKMODE_HARD_3		0x83

#define CFG_SERIALMODE_SOFT_0				0x00
#define CFG_SERIALMODE_SOFT_1				0x01
#define CFG_SERIALMODE_SOFT_2				0x02
#define CFG_SERIALMODE_HARD_0				0x80
#define CFG_SERIALMODE_HARD_1				0x81
#define CFG_SERIALMODE_HARD_2				0x82

#define CFG_ADDR	0x00

#define CFG_BAUD1	0x00
#define CFG_BAUD2	0x00
#define CFG_BAUD3	0x25
#define CFG_BAUD4	0x80

#define CFG_PACK_INTERVAL1	0x00
#define CFG_PACK_INTERVAL2	0x03

#define CFG_VID1	0x86
#define CFG_VID2  0x1A
#define CFG_PID1	0x29
#define CFG_PID2	0xE1

#define CFG_UPLOAD_INTERVAL1 0x00
#define CFG_UPLOAD_INTERVAL2 0x00

#define CFG_KEY_RELASE_DELAY1	0x00
#define CFG_KEY_RELASE_DELAY2	0x01

#define CFG_AUTOENTER		0x00

#define CFG_ENTER_SYMBOL1_1	0x0D
#define CFG_ENTER_SYMBOL1_2	0x00
#define CFG_ENTER_SYMBOL1_3	0x00
#define CFG_ENTER_SYMBOL1_4	0x00
#define CFG_ENTER_SYMBOL2_1	0x00
#define CFG_ENTER_SYMBOL2_2	0x00
#define CFG_ENTER_SYMBOL2_3	0x00
#define CFG_ENTER_SYMBOL2_4	0x00

#define CFG_FILITER_START1	0x00
#define CFG_FILITER_START2	0x00
#define CFG_FILITER_START3	0x00
#define CFG_FILITER_START4	0x00
#define CFG_FILITER_STOP1	0x00
#define CFG_FILITER_STOP2	0x00
#define CFG_FILITER_STOP3	0x00
#define CFG_FILITER_STOP4	0x00

#define CFG_STR_EN_FLAG		0x00

#define CFG_KEY_FLAST_UPLOAD_FLAG	0x00

/* 按键对应键码，用于填充指令 */
#define KEY_Pie									0x35	/*'`'						*/
#define KEY_One									0x1E  /*'1'					  */
#define KEY_Two									0x1F  /*'2'					  */
#define KEY_Three								0x20  /*'3'					  */
#define KEY_Four								0x21  /*'4'					  */
#define KEY_Five								0x22  /*'5'					  */
#define KEY_Six									0x23  /*'6'					  */
#define KEY_Seven								0x24  /*'7'					  */
#define KEY_Eight								0x25  /*'8'					  */
#define KEY_Nine								0x26  /*'9'					  */
#define KEY_Zero								0x27  /*'0'					  */
#define KEY_Line								0x2D  /*'-'					  */
#define KEY_Equal								0x2E  /*'='           */
#define KEY_Keycode14						0x89  /*Keycode14     */
#define KEY_BackSpace						0x2A  /*'BackSpace'   */
#define KEY_Tab									0x2B  /*'Tab'         */
#define KEY_q										0x14  /*'q'           */
#define KEY_w										0x1A  /*'w'           */
#define KEY_e										0x08  /*'e'           */
#define KEY_r										0x15  /*'r'           */
#define KEY_t										0x17  /*'t'           */
#define KEY_y										0x1C  /*'y'           */
#define KEY_u										0x18  /*'u'           */
#define KEY_i										0x0C  /*'i'           */
#define KEY_o										0x12  /*'o'           */
#define KEY_p										0x13  /*'p'           */
#define KEY_LeftSquareBrackets	0x2F  /*'['           */
#define KEY_RightSquareBrackets	0x30  /*']'           */
#define KEY_Backlash						0x31  /*'\'           */
#define KEY_CapsLock						0x39  /*'CapsLock'    */
#define KEY_a										0x04  /*'a'           */
#define KEY_s										0x16  /*'s'           */
#define KEY_d										0x07  /*'d'           */
#define KEY_f										0x09  /*'f'           */
#define KEY_g										0x0A  /*'g'           */
#define KEY_h										0x0B  /*'h'           */
#define KEY_j										0x0D  /*'j'           */
#define KEY_k										0x0E  /*'k'           */
#define KEY_l										0x0F  /*'l'           */
#define KEY_Semicolon						0x33  /*';'           */
#define KEY_SingleQuotes				0x34  /*'''           */
#define KEY_Keycode42						0x32  /*'Keycode42'   */
#define KEY_LeftEnter						0x28  /*'LeftEnter'   */
#define KEY_LeftShift						0xE1  /*'LeftShift'   */
#define KEY_Keycode45						0x64  /*'Keycode45'   */
#define KEY_z										0x1D  /*'z'           */
#define KEY_x										0x1B  /*'x'           */
#define KEY_c										0x06  /*'c'           */
#define KEY_v										0x19  /*'v'           */
#define KEY_b										0x05  /*'b'           */
#define KEY_n										0x11  /*'n'           */
#define KEY_m										0x10  /*'m'           */
#define KEY_Comma								0x36  /*','           */
#define KEY_Point								0x37  /*'.'           */
#define KEY_ObliqueLine					0x38  /*'/'           */
#define KEY_Keycode56						0x87  /*'Keycode56'   */
#define KEY_RightShift					0xE5  /*'RightShift'  */
#define KEY_LeftCtrl						0xE0  /*'LeftCtrl'    */
#define KEY_LeftAlt							0xE2  /*'LeftAlt'     */
#define KEY_Space								0x2C  /*'Space'       */
#define KEY_RightAlt						0xE6  /*'RightAlt'    */
#define KEY_RightCtrl						0xE4  /*'RightCtrl'   */
#define KEY_Insert							0x49  /*'Insert'      */
#define KEY_Delete							0x4C  /*'Delete'      */
#define KEY_LeftArrow						0x50  /*'LeftArrow'   */
#define KEY_Home								0x4A  /*'Home'        */
#define KEY_End									0x4D  /*'End'         */
#define KEY_UpArrow							0x52  /*'UpArrow'     */
#define KEY_DownArrow						0x51  /*'DownArrow'   */
#define KEY_PgUp								0x4B  /*'PgUp'        */
#define KEY_PgDn								0x4E  /*'PgDn'        */
#define KEY_RightArrow					0x4F  /*'RightArrow'  */
#define KEY_NumLock							0x53  /*'NumLock'     */
#define KEY_sSeven							0x5F  /*'7'           */
#define KEY_sFour								0x5C  /*'4'           */
#define KEY_sOne								0x59  /*'1'           */
#define KEY_Divide							0x54  /*'/'           */
#define KEY_sEight							0x60  /*'8'           */
#define KEY_sFive								0x5D  /*'5'           */
#define KEY_sTwo								0x5A  /*'2'           */
#define KEY_sZero								0x62  /*'0'           */
#define KEY_sStar								0x55  /*'*'           */
#define KEY_sNine								0x61  /*'9'           */
#define KEY_sSix								0x5E  /*'6'           */
#define KEY_sThree							0x5B  /*'3'           */
#define KEY_sDot								0x63  /*'.'           */
#define KEY_sSub								0x56  /*'-'           */
#define KEY_sPlus								0x57  /*'+'           */
#define KEY_Keycode107					0x85  /*'Keycode107'  */
#define KEY_RightEnter					0x58  /*'RightEnter'  */
#define KEY_Esc									0x29  /*'Esc'         */
#define KEY_F1									0x3A  /*'F1'          */
#define KEY_F2									0x3B  /*'F2'          */
#define KEY_F3									0x3C  /*'F3'          */
#define KEY_F4									0x3D  /*'F4'          */
#define KEY_F5									0x3E  /*'F5'          */
#define KEY_F6									0x3F  /*'F6'          */
#define KEY_F7									0x40  /*'F7'          */
#define KEY_F8									0x41  /*'F8'          */
#define KEY_F9									0x42  /*'F9'          */
#define KEY_F10									0x43  /*'F10'         */
#define KEY_F11									0x44  /*'F11'         */
#define KEY_F12									0x45  /*'F12'         */
#define KEY_PrintScreen					0x46  /*'PrintScreen' */
#define KEY_ScrollLock					0x47  /*'ScrollLock'  */
#define KEY_Pause								0x48  /*'Pause'       */

#define KEY_Wave									  0x35	/*	'~'   */
#define KEY_Exclamation						  0x1E	/*	'!'   */
#define KEY_At										  0x1F	/*	'@'   */
#define KEY_Well									  0x20	/*	'#'   */
#define KEY_Dollar								  0x21	/*	'$'   */
#define KEY_Percent								  0x22	/*	'%'   */
#define KEY_UpAngleBrackets				  0x23	/*	'^'   */
#define KEY_And										  0x24	/*	'&'   */
#define KEY_Star									  0x25	/*	'*'   */
#define KEY_LeftParenthesis				  0x26	/*	'('   */
#define KEY_RightParenthesis			  0x27	/*	')'   */
#define KEY_DownLine							  0x2D	/*	'_'   */
#define KEY_Plus									  0x2E	/*	'+'   */
#define KEY_Q											  0x14	/*	'Q'   */
#define KEY_W											  0x1A	/*	'W'   */
#define KEY_E											  0x08	/*	'E'   */
#define KEY_R											  0x15	/*	'R'   */
#define KEY_T											  0x17	/*	'T'   */
#define KEY_Y											  0x1C	/*	'Y'   */
#define KEY_U											  0x18	/*	'U'   */
#define KEY_I											  0x0C	/*	'I'   */
#define KEY_O											  0x12	/*	'O'   */
#define KEY_P											  0x13	/*	'P'   */
#define KEY_Leftbrace							  0x2F	/*	'{'   */
#define KEY_Rightbrace						  0x30	/*	'}'   */
#define KEY_PerpendicularLine			  0x31	/*	'|'   */
#define KEY_A											  0x04	/*	'A'   */
#define KEY_S											  0x16	/*	'S'   */
#define KEY_D											  0x07	/*	'D'   */
#define KEY_F											  0x09	/*	'F'   */
#define KEY_G											  0x0A	/*	'G'   */
#define KEY_H											  0x0B	/*	'H'   */
#define KEY_J											  0x0D	/*	'J'   */
#define KEY_K											  0x0E	/*	'K'   */
#define KEY_L											  0x0F	/*	'L'   */
#define KEY_Colon									  0x33	/*	':'   */
#define KEY_DoubleQuotationMarks	  0x34	/*	'"'   */
#define KEY_Z											  0x1D	/*	'Z'   */
#define KEY_X											  0x1B	/*	'X'   */
#define KEY_C											  0x06	/*	'C'   */
#define KEY_V											  0x19	/*	'V'   */
#define KEY_B											  0x05	/*	'B'   */
#define KEY_N											  0x11	/*	'N'   */
#define KEY_M											  0x10	/*	'M'   */
#define KEY_LeftAngleBracket			  0x36	/*	'<'   */
#define	KEY_RightAngleBracket			  0x37	/*	'>'   */
#define	KEY_QuestionMark					  0x38	/*	'?'   */

/* 多媒体按键值 */
#define KEY_RELEASE				(0x000000)
#define KEY_MEDIA					(0x000001)
#define KEY_EXPLORER			(0x000002)
#define KEY_CALCULATOR		(0x000004)
#define KEY_SCREEN_SAVE		(0x000008)
#define KEY_MY_COMPUTER		(0x000010)
#define KEY_MINIMIZE			(0x000020)
#define KEY_RECORD				(0x000040)
#define KEY_REWIND				(0x000080)
#define KEY_EMAIL					(0x000100)
#define KEY_WB_SEARCH			(0x000200)
#define KEY_WB_FAVORITES	(0x000400)
#define KEY_WB_HOME				(0x000800)
#define KEY_WB_BACK				(0x001000)
#define KEY_WB_FORWARD		(0x002000)
#define KEY_WB_STOP				(0x004000)
#define KEY_REFRESH				(0x008000)
#define KEY_VOLUME_ADD		(0x010000)
#define KEY_VOLUME_SUM		(0x020000)
#define KEY_MUTE					(0x040000)
#define KEY_PLAY_PAUSE		(0x080000)
#define KEY_NEXT_TRACK		(0x100000)
#define KEY_PREV_TRACK		(0x200000)
#define KEY_CD_STOP				(0x400000)
#define KEY_EJECT					(0x800000)

/* 电源功能按键值 */
#define KEY_POWER		(0x01)
#define KEY_SLEEP		(0x02)
#define KEY_WAKE_UP	(0x04)

#define R_WINDOWS	(0x80)
#define R_ALT			(0x40)
#define R_SHIFT		(0x20)
#define R_CTRL		(0x10)
#define L_WINDOWS	(0x08)
#define L_ALT			(0x04)
#define L_SHIFT		(0x02)
#define L_CTRL		(0x01)
#define NO_CTRL		(0x00)

typedef struct CMD_FORMAT
{
	volatile uint8_t head1;
	volatile uint8_t head2;
	volatile uint8_t addr;
	volatile uint8_t cmd;
	volatile uint8_t len;		//仅包含后续数据部分，不包括帧头字节、地址码、命令码和累加和字节
	volatile uint8_t data[CH9329_TRANS_MAX_DATA_LEN+1];	//累加和放在data最后一个字节
}CMD_FORMAT_t;

typedef enum KEY_TYPE
{
	KEY_TYPE_GENERAL_KEY = 0,
	KEY_TYPE_MEDIA_KEY,
	KEY_TYPE_POWER_KEY
}KEY_TYPE_e;

#define CMD_GENERAL_KEY_LEN	8				//普通按键结构体长度
typedef struct CMD_GENERAL_KEY_DATA	//普通按键
{
	volatile uint8_t key_ctrl;
	volatile uint8_t null;
	volatile uint8_t key1;
	volatile uint8_t key2;
	volatile uint8_t key3;
	volatile uint8_t key4;
	volatile uint8_t key5;
	volatile uint8_t key6;
}CMD_GENERAL_KEY_DATA_t;

typedef enum MEDIA_KEY_TYPE
{
	MEDIA_KEY_TYPE_KEY_RELEASE = 0,
	MEDIA_KEY_TYPE_KEY_MEDIA,
	MEDIA_KEY_TYPE_KEY_EXPLORER,
	MEDIA_KEY_TYPE_KEY_CALCULATOR,
	MEDIA_KEY_TYPE_KEY_SCREEN_SAVE,
	MEDIA_KEY_TYPE_KEY_MY_COMPUTER,
	MEDIA_KEY_TYPE_KEY_MINIMIZE,
	MEDIA_KEY_TYPE_KEY_RECORD,
	MEDIA_KEY_TYPE_KEY_REWIND,
	MEDIA_KEY_TYPE_KEY_EMAIL,
	MEDIA_KEY_TYPE_KEY_WB_SEARCH,
	MEDIA_KEY_TYPE_KEY_WB_FAVORITES,
	MEDIA_KEY_TYPE_KEY_WB_HOME,
	MEDIA_KEY_TYPE_KEY_WB_BACK,
	MEDIA_KEY_TYPE_KEY_WB_FORWARD,
	MEDIA_KEY_TYPE_KEY_WB_STOP,
	MEDIA_KEY_TYPE_KEY_REFRESH,
	MEDIA_KEY_TYPE_KEY_VOLUME_ADD,
	MEDIA_KEY_TYPE_KEY_VOLUME_SUM,
	MEDIA_KEY_TYPE_KEY_MUTE,
	MEDIA_KEY_TYPE_KEY_PLAY_PAUSE,
	MEDIA_KEY_TYPE_KEY_NEXT_TRACK,
	MEDIA_KEY_TYPE_KEY_PREV_TRACK,
	MEDIA_KEY_TYPE_KEY_CD_STOP,
	MEDIA_KEY_TYPE_KEY_EJECT,
}MEDIA_KEY_TYPE_e;

#define CMD_MEDIA_KEY_LEN	4				//多媒体按键结构体长度
typedef struct CMD_MEDIA_KEY_DATA	//多媒体按键
{
	volatile uint8_t report_id;	//固定为0x02
	volatile uint8_t media_key1;
	volatile uint8_t media_key2;
	volatile uint8_t media_key3;
}CMD_MEDIA_KEY_DATA_t;

typedef enum POWER_KEY_TYPE
{
	POWER_KEY_TYPE_KEY_RELEASE = 0,
	POWER_KEY_TYPE_KEY_POWER,
	POWER_KEY_TYPE_KEY_SLEEP,
	POWER_KEY_TYPE_KEY_WAKE_UP
}POWER_KEY_TYPE_e;

#define CMD_POWER_KEY_LEN	2				//电源结构体长度
typedef struct CMD_POWER_KEY_DATA
{
	volatile uint8_t report_id;	//固定为0x01
	volatile uint8_t power_key;
}CMD_POWER_KEY_DATA_t;

typedef enum CH9329_CONFIG_INDEX
{
	CH9329_CONFIG_INDEX_WORK_MODE = 0,							//0x00
	CH9329_CONFIG_INDEX_PORT_MODE,									//0x01
	CH9329_CONFIG_INDEX_ADDR,												//0x02
	CH9329_CONFIG_INDEX_BAUD_1,											//0x03
	CH9329_CONFIG_INDEX_BAUD_2,											//0x04
	CH9329_CONFIG_INDEX_BAUD_3,                     //0x05
	CH9329_CONFIG_INDEX_BAUD_4,                     //0x06
	CH9329_CONFIG_INDEX_RESERVE0,                   //0x07
	CH9329_CONFIG_INDEX_RESERVE1,                   //0x08
	CH9329_CONFIG_INDEX_PACK_INTERVAL_1,            //0x09
	CH9329_CONFIG_INDEX_PACK_INTERVAL_2,            //0x0A
	CH9329_CONFIG_INDEX_VID_1,                      //0x0B
	CH9329_CONFIG_INDEX_VID_2,                      //0x0C
	CH9329_CONFIG_INDEX_PID_1,                      //0x0D
	CH9329_CONFIG_INDEX_PID_2,                      //0x0E
	CH9329_CONFIG_INDEX_UPLOAD_INTERVAL_1,          //0x0F
	CH9329_CONFIG_INDEX_UPLOAD_INTERVAL_2,          //0x10
	CH9329_CONFIG_INDEX_KEY_RELEASE_INTERVAL_1,     //0x11
	CH9329_CONFIG_INDEX_KEY_RELEASE_INTERVAL_2,     //0x12
	CH9329_CONFIG_INDEX_AUTO_ENTER,                 //0x13
	CH9329_CONFIG_INDEX_ENTER_SYMBOL1_1,            //0x14
	CH9329_CONFIG_INDEX_ENTER_SYMBOL1_2,            //0x15
	CH9329_CONFIG_INDEX_ENTER_SYMBOL1_3,            //0x16
	CH9329_CONFIG_INDEX_ENTER_SYMBOL1_4,            //0x17
	CH9329_CONFIG_INDEX_ENTER_SYMBOL2_1,            //0x18
	CH9329_CONFIG_INDEX_ENTER_SYMBOL2_2,            //0x19
	CH9329_CONFIG_INDEX_ENTER_SYMBOL2_3,            //0x1A
	CH9329_CONFIG_INDEX_ENTER_SYMBOL2_4,            //0x1B
	CH9329_CONFIG_INDEX_FILITER_START1,             //0x1C
	CH9329_CONFIG_INDEX_FILITER_START2,             //0x1D
	CH9329_CONFIG_INDEX_FILITER_START3,             //0x1F
	CH9329_CONFIG_INDEX_FILITER_START4,             //0x20
	CH9329_CONFIG_INDEX_FILITER_STOP1,              //0x21
	CH9329_CONFIG_INDEX_FILITER_STOP2,              //0x22
	CH9329_CONFIG_INDEX_FILITER_STOP3,              //0x23
	CH9329_CONFIG_INDEX_FILITER_STOP4,              //0x24
	CH9329_CONFIG_INDEX_STR_EN_FLAG,                //0x25
	CH9329_CONFIG_INDEX_KEY_FLAST_UPLOAD_FLAG,      //0x26
}CH9329_CONFIG_INDEX_e;

typedef enum _BUTTON_VALUE_{
	button_NULL = 0,
	button_LEFT = 1,
	button_RIGHT= 2,
	button_MID  = 4
}BUTTON_VALUE_e;

void CH9329_Init(void);
void CH9329_WorkMode_Config(uint8_t workmode);
void CH9329_SerialMode_Config(uint8_t serialmode);
void CH9329_SerialAddr_Config(uint8_t addr);;
void CH9329_SerialBaudRate_Config(uint8_t* baudrate);
void CH9329_Get_Cfg(void);
void CH9329_Set_Cfg(void);

void CH9329_Index_to_Ascii(uint8_t *ascii);
void CH9329_Generate_KEY_CMD(KEY_TYPE_e type,char key_value);
void CH9329_Input_Ascii(char *ascii);
uint8_t CH9329_CAL_SUM(uint8_t *cmd,uint8_t len);
int Send_HID_Data(uint8_t *data,uint8_t len);
int ABD_Mouse_Ctrl(uint8_t step,uint8_t* pos_x,uint8_t* pos_y,BUTTON_VALUE_e button);
int REL_Mouse_Ctrl(uint8_t step,uint8_t dir_x,uint8_t dir_y,BUTTON_VALUE_e button);
#endif
