#ifndef __CH9329_H
#define __CH9329_H
#include "stm32f1xx.h"

#define buffersize 20

/**�������Ʋ���*/
//uint8_t KeyUP[8]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
//uint8_t KeyUP[20]={0x57,0xAB,0x00,0x02,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0C,0x0A};
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
						
 /**����shift��*/						
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
	
 /**����shift��*/	
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

/**��ý��*/
extern uint8_t 					VoiceDown							[13]						;
extern uint8_t 					VoiceUp								[13]						;
extern uint8_t 					Mute									[13]						;
extern uint8_t 					Calculator						[13]						;
extern uint8_t 					EMail									[13]						;
extern uint8_t 					Search								[13]						;
extern uint8_t 					Explorer							[13]						;

extern uint8_t 					ScreenSave						[13]						;
extern uint8_t 					KeyRelease						[13]						;

typedef struct
{
	uint8_t WorkState;
	uint8_t SerialMode;
	uint8_t SerialAddr;
	uint8_t SerialBaudRate[4];
	uint8_t SerialInterval[2];
	uint8_t Vid[2];
	uint8_t Pid[2];
	uint8_t UploadInterval[2];
	uint8_t KeyReleaseInterval[2];
	uint8_t AutoEnterFlag;
	uint8_t EnterSymbol[8];
	uint8_t Filter[8];
	uint8_t StringEnable;
	uint8_t QuickUpload;
}Para_Cfg;










void Combine(uint8_t *head,uint8_t *body);
void SendCommand(uint8_t *body);
void SendWords(uint8_t *w1,uint8_t *w2,uint8_t *w3,uint8_t *w4,uint8_t *w5,
							 uint8_t *w6, uint8_t *w7, uint8_t *w8, uint8_t *w9, uint8_t *w10, uint8_t num);
void toASCLL( uint8_t *asc);
void Sendtest( uint8_t *asc);
void CH9329_Init(void);
void Get_Cfg(void);
void Set_Cfg(void);

#endif
