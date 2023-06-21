#ifndef __CH9329_H
#define __CH9329_H
#include "stm32f1xx.h"

/* 配置前后需要一定延时 */
#define SET_EN	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_SET)	//CH9329芯片参数配置引脚使能
#define SET_DEN	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_RESET)	//CH9329芯片参数配置引脚禁止

#define WORKMODE_SOFT_0		0x00
#define WORKMODE_SOFT_1		0x01
#define WORKMODE_SOFT_2		0x02
#define WORKMODE_SOFT_3		0x03
#define WORKMODE_HARD_0		0x80
#define WORKMODE_HARD_1		0x81
#define WORKMODE_HARD_2		0x82
#define WORKMODE_HARD_3		0x83

#define SERIALMODE_SOFT_0				0x00
#define SERIALMODE_SOFT_1				0x01
#define SERIALMODE_SOFT_2				0x02
#define SERIALMODE_HARD_0				0x80
#define SERIALMODE_HARD_1				0x81
#define SERIALMODE_HARD_2				0x82

#define AUTOENTERFLAG_ENABLE		0x01
#define AUTOENTERFLAG_DISABLE		0x00

/* 按键对应键码，用于填充指令 */
#define KEY_Pie									0x35
#define KEY_One									0x1E
#define KEY_Two									0x1F
#define KEY_Three								0x20
#define KEY_Four								0x21
#define KEY_Five								0x22
#define KEY_Six									0x23
#define KEY_Seven								0x24
#define KEY_Eight								0x25
#define KEY_Nine								0x26
#define KEY_Zero								0x27
#define KEY_Line								0x2D
#define KEY_Equal								0x2E
#define KEY_Keycode14						0x89
#define KEY_BackSpace						0x2A
#define KEY_Tab									0x2B
#define KEY_q										0x14
#define KEY_w										0x1A
#define KEY_e										0x08
#define KEY_r										0x15
#define KEY_t										0x17
#define KEY_y										0x1C
#define KEY_u										0x18
#define KEY_i										0x0C
#define KEY_o										0x12
#define KEY_p										0x13
#define KEY_LeftSquareBrackets	0x2F
#define KEY_RightSquareBrackets	0x30
#define KEY_Backlash						0x31
#define KEY_CapsLock						0x39
#define KEY_a										0x04
#define KEY_s										0x16
#define KEY_d										0x07
#define KEY_f										0x09
#define KEY_g										0x0A
#define KEY_h										0x0B
#define KEY_j										0x0D
#define KEY_k										0x0E
#define KEY_l										0x0F
#define KEY_Semicolon						0x33
#define KEY_SingleQuotes				0x34
#define KEY_Keycode42						0x32
#define KEY_LeftEnter						0x28
#define KEY_LeftShift						0xE1
#define KEY_Keycode45						0x64
#define KEY_z										0x1D
#define KEY_x										0x1B
#define KEY_c										0x06
#define KEY_v										0x19
#define KEY_b										0x05
#define KEY_n										0x11
#define KEY_m										0x10
#define KEY_Comma								0x36
#define KEY_Point								0x37
#define KEY_ObliqueLine					0x38
#define KEY_Keycode56						0x87
#define KEY_RightShift					0xE5
#define KEY_LeftCtrl						0xE0
#define KEY_LeftAlt							0xE2
#define KEY_Space								0x2C
#define KEY_RightAlt						0xE6
#define KEY_RightCtrl						0xE4
#define KEY_Insert							0x49
#define KEY_Delete							0x4C
#define KEY_LeftArrow						0x50
#define KEY_Home								0x4A
#define KEY_End									0x4D
#define KEY_UpArrow							0x52
#define KEY_DownArrow						0x51
#define KEY_PgUp								0x4B
#define KEY_PgDn								0x4E
#define KEY_RightArrow					0x4F
#define KEY_NumLock							0x53
#define KEY_sSeven							0x5F
#define KEY_sFour								0x5C
#define KEY_sOne								0x59
#define KEY_Divide							0x54
#define KEY_sEight							0x60
#define KEY_sFive								0x5D
#define KEY_sTwo								0x5A
#define KEY_sZero								0x62
#define KEY_sStar								0x55
#define KEY_sNine								0x61
#define KEY_sSix								0x5E
#define KEY_sThree							0x5B
#define KEY_sDot								0x63
#define KEY_sSub								0x56
#define KEY_sPlus								0x57
#define KEY_Keycode107					0x85
#define KEY_RightEnter					0x58
#define KEY_Esc									0x29
#define KEY_F1									0x3A
#define KEY_F2									0x3B
#define KEY_F3									0x3C
#define KEY_F4									0x3D
#define KEY_F5									0x3E
#define KEY_F6									0x3F
#define KEY_F7									0x40
#define KEY_F8									0x41
#define KEY_F9									0x42
#define KEY_F10									0x43
#define KEY_F11									0x44
#define KEY_F12									0x45
#define KEY_PrintScreen					0x46
#define KEY_ScrollLock					0x47
#define KEY_Pause								0x48















extern uint8_t CH9329_CONFIG[50];
extern uint8_t g_keystate;
extern uint8_t g_connectstate;
extern uint8_t result[103];

extern uint8_t 					INFO									[9]							;

extern uint8_t 					RWindows							[8]							;
extern uint8_t 					RAlt									[8]							;
extern uint8_t 					RShift								[8]							;
extern uint8_t 					RCtrl									[8]							;
extern uint8_t 					LWindows							[8]							;
extern uint8_t 					LAlt									[8]							;
extern uint8_t 					LShift								[8]							;
extern uint8_t 					LCtrl									[8]							;
extern uint8_t 					CMD_HEAD							[5]							;
extern uint8_t 					KeyUP									[20]						;
												
extern uint8_t 					Paste									[8]							;
						
 /**（无shift）*/						
extern uint8_t 					Pie										[8]							;						
extern uint8_t 					One										[8]							;						
extern uint8_t 					Two										[8]							;							
extern uint8_t 					Three									[8]							;					
extern uint8_t 					Four									[8]							;						
extern uint8_t 					Five									[8]							;							
extern uint8_t 					Six										[8]							;							
extern uint8_t 					Seven									[8]							;							
extern uint8_t 					Eight									[8]							;						
extern uint8_t 					Nine									[8]							;						
extern uint8_t 					Zero									[8]							;						
extern uint8_t 					Line									[8]							;							
extern uint8_t 					Equal									[8]							;							
extern uint8_t 					Keycode14							[8]							;
extern uint8_t 					BackSpace							[8]							;
extern uint8_t 					Tab										[8]							;							
extern uint8_t 					q											[8]							;						
extern uint8_t 					w											[8]							;						
extern uint8_t 					e											[8]							;						
extern uint8_t 					r											[8]							;						
extern uint8_t 					t											[8]							;						
extern uint8_t 					y											[8]							;						
extern uint8_t 					u											[8]							;						
extern uint8_t 					i											[8]							;						
extern uint8_t 					o											[8]							;						
extern uint8_t 					p											[8]							;						
extern uint8_t 					LeftSquareBrackets		[8]							;
extern uint8_t 					RightSquareBrackets		[8]							;
extern uint8_t 					Backlash							[8]							;			
extern uint8_t 					CapsLock							[8]							;				
extern uint8_t 					a											[8]							;							
extern uint8_t 					s											[8]							;							
extern uint8_t 					d											[8]							;							
extern uint8_t 					f											[8]							;							
extern uint8_t 					g											[8]							;							
extern uint8_t 					h											[8]							;							
extern uint8_t 					j											[8]							;							
extern uint8_t 					k											[8]							;							
extern uint8_t 					l											[8]							;							
extern uint8_t 					Semicolon							[8]							;				
extern uint8_t 					SingleQuotes					[8]							;		
extern uint8_t 					Keycode42							[8]							;
extern uint8_t 					LeftEnter							[8]							;
extern uint8_t 					LeftShift							[8]							;
extern uint8_t 					Keycode45							[8]							;
extern uint8_t 					z											[8]							;							
extern uint8_t 					x											[8]							;							
extern uint8_t 					c											[8]							;							
extern uint8_t 					v											[8]							;							
extern uint8_t 					b											[8]							;							
extern uint8_t 					n											[8]							;							
extern uint8_t 					m											[8]							;							
extern uint8_t 					Comma									[8]							;						
extern uint8_t					Point									[8]							;	 
extern uint8_t					ObliqueLine						[8]					    ;   
extern uint8_t					Keycode56							[8]						  ;   
extern uint8_t					RightShift						[8]						  ;   
extern uint8_t					LeftCtrl							[8]							;   
extern uint8_t					LeftAlt								[8]							;   
extern uint8_t					Space									[8]						  ;   
extern uint8_t					RightAlt							[8]							;   
extern uint8_t					RightCtrl							[8]						  ;   
extern uint8_t					Insert								[8]							;	 
extern uint8_t					Delete								[8]							;	 
extern uint8_t					LeftArrow							[8]						  ;   
extern uint8_t					Home									[8]							;		
extern uint8_t					End										[8]							;		
extern uint8_t					UpArrow								[8]							;   
extern uint8_t					DownArrow							[8]						  ;   
extern uint8_t					PgUp									[8]							;		
extern uint8_t					PgDn									[8]							;		
extern uint8_t					RightArrow						[8]						  ;   
extern uint8_t					NumLock								[8]							;   
extern uint8_t					sSeven								[8]							;	 
extern uint8_t					sFour									[8]							;	 
extern uint8_t					sOne									[8]							;		
extern uint8_t					Divide								[8]							;	 
extern uint8_t					sEight								[8]							;	 
extern uint8_t					sFive									[8]							;	 
extern uint8_t					sTwo									[8]							;		
extern uint8_t					sZero									[8]							;	 
extern uint8_t					sStar									[8]							;	 
extern uint8_t					sNine									[8]							;	 
extern uint8_t					sSix									[8]							;		
extern uint8_t					sThree								[8]							;	 
extern uint8_t					sDot									[8]							;		
extern uint8_t					sSub									[8]							;		
extern uint8_t					sPlus									[8]							;	 
extern uint8_t					Keycode107						[8]						  ;   
extern uint8_t					RightEnter						[8]						  ;   
extern uint8_t					Esc										[8]							;		
extern uint8_t					F1										[8]							;		
extern uint8_t					F2										[8]							;		
extern uint8_t					F3										[8]							;		
extern uint8_t					F4										[8]							;		
extern uint8_t					F5										[8]							;		
extern uint8_t					F6										[8]							;		
extern uint8_t					F7										[8]							;		
extern uint8_t					F8										[8]							;		
extern uint8_t					F9										[8]							;		
extern uint8_t					F10										[8]							;		
extern uint8_t					F11										[8]							;		
extern uint8_t					F12										[8]							;		
extern uint8_t					PrintScreen						[8]					    ;   
extern uint8_t					ScrollLock						[8]					    ;   
extern uint8_t					Pause									[8]					  	;	 
	
 /**（有shift）*/	
extern uint8_t 					Wave									[8]							;	
extern uint8_t 					Exclamation						[8]							;	
extern uint8_t 					At										[8]							;		
extern uint8_t 					Well									[8]							;						
extern uint8_t 					Dollar								[8]							;
extern uint8_t 					Percent								[8]							;
extern uint8_t 					UpArrow								[8]							;
extern uint8_t 					And										[8]							;
extern uint8_t 					Star									[8]							;
extern uint8_t 					LeftParenthesis				[8]							;
extern uint8_t 					RightParenthesis			[8]							;
extern uint8_t 					DownLine							[8]							;
extern uint8_t 					Plus									[8]							;		
extern uint8_t 					Q											[8]							;
extern uint8_t 					W											[8]							;
extern uint8_t 					E											[8]							;
extern uint8_t 					R											[8]							;
extern uint8_t 					T											[8]							;
extern uint8_t 					Y											[8]							;
extern uint8_t 					U											[8]							;
extern uint8_t 					I											[8]							;
extern uint8_t 					O											[8]							;
extern uint8_t 					P											[8]							;
extern uint8_t 					Leftbrace							[8]						  ;
extern uint8_t 					Rightbrace						[8]						  ;
extern uint8_t 					PerpendicularLine			[8]							;
extern uint8_t 					A											[8]							;
extern uint8_t 					S											[8]							;
extern uint8_t 					D											[8]							;
extern uint8_t 					F											[8]							;
extern uint8_t 					G											[8]							;
extern uint8_t 					H											[8]							;
extern uint8_t 					J											[8]							;
extern uint8_t 					K											[8]							;
extern uint8_t 					L											[8]							;
extern uint8_t 					Colon									[8]							;
extern uint8_t 					DoubleQuotationMarks	[8]	            ;
extern uint8_t 					Z											[8]							;
extern uint8_t 					X											[8]							;
extern uint8_t 					C											[8]							;
extern uint8_t 					V											[8]							;
extern uint8_t 					B											[8]							;
extern uint8_t 					N											[8]							;
extern uint8_t 					M											[8]							;
extern uint8_t 					LeftAngleBracket			[8]			        ;
extern uint8_t					RightAngleBracket			[8]		          ;
extern uint8_t					QuestionMark					[8]					    ;

extern uint32_t ascll[127];

/**多媒体*/
extern uint8_t 					VoiceDown							[13]						;
extern uint8_t 					VoiceUp								[13]						;
extern uint8_t 					Mute									[13]						;
extern uint8_t 					Calculator						[13]						;
extern uint8_t 					EMail									[13]						;
extern uint8_t 					Search								[13]						;
extern uint8_t 					Explorer							[13]						;

extern uint8_t 					ScreenSave						[13]						;
extern uint8_t 					KeyRelease						[13]						;






void CH9329_WorkMode_Config(uint8_t workmode);
void CH9329_SerialMode_Config(uint8_t serialmode);
void CH9329_SerialAddr_Config(uint8_t addr);
void CH9329_SerialBaudRate_Config(uint8_t* baudrate);
void CH9329_SerialInterval_Config(uint8_t* interval);
void CH9329_Vid_Pid_Config(uint16_t vid,uint16_t pid);
void CH9329_Get_Cfg(void);
void CH9329_Set_Cfg(void);
void CH9329_Init(void);
void CH9329_Reset(void);
uint8_t CH9329_Generate_Checksum(uint8_t* cmd,uint8_t len);
uint8_t CMD_GET_INFO(void);
uint16_t toASCLL( uint8_t *asc);
uint8_t *Combination_Key( uint8_t control, uint8_t *key);
void SendCommand( uint8_t *body);
void CMD_Media_Sleep(void);
uint8_t CH9329_GenerateCheckSum(uint8_t *data,uint8_t length);

#endif
