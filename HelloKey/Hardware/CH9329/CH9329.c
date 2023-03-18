#include "CH9329.h"
#include "delay.h"
#include "string.h"
#include "func.h"
/* Suppress warning messages */
#if defined(__CC_ARM)
// Suppress warning message: extended constant initialiser used
#pragma diag_suppress 1296
#elif defined(__ICCARM__)
#elif defined(__GNUC__)
#endif

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;

/**   完整数组末尾一定要加0x0A!!!!!!!!!!!*/

static	uint8_t CB[8];

uint8_t FIXED[20];
uint8_t 					FIXED_HEAD							[5]								={0x57,0xAB,0x00,0x02,0x08};		//命令头
uint8_t 					INFO									[9]								={0x57,0xAB,0x00,0x01,0x00,0x03,0xFF,0x0D,0x0A};
uint8_t 					KeyUP									[20]							={0x57,0xAB,0x00,0x02,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0C,0xFF,0x0D,0x0A};

uint8_t CHECK;	//累加和
/**按键控制部分*/
//uint8_t KeyUP[8]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
//uint8_t KeyUP[20]={0x57,0xAB,0x00,0x02,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0C,0x0A};
uint8_t 					RWindows							[8]								={0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
uint8_t 					RAlt									[8]								={0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
uint8_t 					RShift								[8]								={0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
uint8_t 					RCtrl									[8]								={0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
uint8_t 					LWindows							[8]								={0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
uint8_t 					LAlt									[8]								={0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
uint8_t 					LShift								[8]								={0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
uint8_t 					LCtrl									[8]								={0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
//组合按键
uint8_t 					Paste									[8]								={0x01,0x00,0x19,0x00,0x00,0x00,0x00,0x00};

/******************************************************基本按键*****************************************************************/
/**（无shift）*/
uint8_t 					Pie										[8]								=	{0x00,0x00,0x35,0x00,0x00,0x00,0x00,0x00};					//'`'
uint8_t 					One										[8]								=	{0x00,0x00,0x1E,0x00,0x00,0x00,0x00,0x00};					//'1'					
uint8_t 					Two										[8]								=	{0x00,0x00,0x1F,0x00,0x00,0x00,0x00,0x00};					//'2'					
uint8_t 					Three									[8]								=	{0x00,0x00,0x20,0x00,0x00,0x00,0x00,0x00};					//'3'					
uint8_t 					Four									[8]								=	{0x00,0x00,0x21,0x00,0x00,0x00,0x00,0x00};					//'4'					
uint8_t 					Five									[8]								=	{0x00,0x00,0x22,0x00,0x00,0x00,0x00,0x00};					//'5'					
uint8_t 					Six										[8]								=	{0x00,0x00,0x23,0x00,0x00,0x00,0x00,0x00};					//'6'					
uint8_t 					Seven									[8]								=	{0x00,0x00,0x24,0x00,0x00,0x00,0x00,0x00};					//'7'					
uint8_t 					Eight									[8]								=	{0x00,0x00,0x25,0x00,0x00,0x00,0x00,0x00};					//'8'					
uint8_t 					Nine									[8]								=	{0x00,0x00,0x26,0x00,0x00,0x00,0x00,0x00};					//'9'					
uint8_t 					Zero									[8]								=	{0x00,0x00,0x27,0x00,0x00,0x00,0x00,0x00};					//'0'					
uint8_t 					Line									[8]								=	{0x00,0x00,0x2D,0x00,0x00,0x00,0x00,0x00};					//'-'					
uint8_t 					Equal									[8]								=	{0x00,0x00,0x2E,0x00,0x00,0x00,0x00,0x00};					//'='
uint8_t 					Keycode14							[8]								=	{0x00,0x00,0x89,0x00,0x00,0x00,0x00,0x00};					//Keycode14
uint8_t 					BackSpace							[8]								=	{0x00,0x00,0x2A,0x00,0x00,0x00,0x00,0x00};					//'BackSpace'
uint8_t 					Tab										[8]								=	{0x00,0x00,0x2B,0x00,0x00,0x00,0x00,0x00};					//'Tab'
uint8_t 					q											[8]								=	{0x00,0x00,0x14,0x00,0x00,0x00,0x00,0x00};					//'q'
uint8_t 					w											[8]								=	{0x00,0x00,0x1A,0x00,0x00,0x00,0x00,0x00};					//'w'
uint8_t 					e											[8]								=	{0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00};					//'e'
uint8_t 					r											[8]								=	{0x00,0x00,0x15,0x00,0x00,0x00,0x00,0x00};					//'r'
uint8_t 					t											[8]								=	{0x00,0x00,0x17,0x00,0x00,0x00,0x00,0x00};					//'t'
uint8_t 					y											[8]								=	{0x00,0x00,0x1C,0x00,0x00,0x00,0x00,0x00};					//'y'
uint8_t 					u											[8]								=	{0x00,0x00,0x18,0x00,0x00,0x00,0x00,0x00};					//'u'
uint8_t 					i											[8]								=	{0x00,0x00,0x0C,0x00,0x00,0x00,0x00,0x00};					//'i'
uint8_t 					o											[8]								=	{0x00,0x00,0x12,0x00,0x00,0x00,0x00,0x00};					//'o'
uint8_t 					p											[8]								=	{0x00,0x00,0x13,0x00,0x00,0x00,0x00,0x00};					//'p'
uint8_t 					LeftSquareBrackets		[8]								=	{0x00,0x00,0x2F,0x00,0x00,0x00,0x00,0x00};					//'['
uint8_t 					RightSquareBrackets		[8]								=	{0x00,0x00,0x30,0x00,0x00,0x00,0x00,0x00};					//']'
uint8_t 					Backlash							[8]								=	{0x00,0x00,0x31,0x00,0x00,0x00,0x00,0x00};					//'\'
uint8_t 					CapsLock							[8]								=	{0x00,0x00,0x39,0x00,0x00,0x00,0x00,0x00};					//'CapsLock'
uint8_t 					a											[8]								=	{0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x00};					//'a'
uint8_t 					s											[8]								=	{0x00,0x00,0x16,0x00,0x00,0x00,0x00,0x00};					//'s'
uint8_t 					d											[8]								=	{0x00,0x00,0x07,0x00,0x00,0x00,0x00,0x00};					//'d'
uint8_t 					f											[8]								=	{0x00,0x00,0x09,0x00,0x00,0x00,0x00,0x00};					//'f'
uint8_t 					g											[8]								=	{0x00,0x00,0x0A,0x00,0x00,0x00,0x00,0x00};					//'g'
uint8_t 					h											[8]								=	{0x00,0x00,0x0B,0x00,0x00,0x00,0x00,0x00};					//'h'
uint8_t 					j											[8]								=	{0x00,0x00,0x0D,0x00,0x00,0x00,0x00,0x00};					//'j'
uint8_t 					k											[8]								=	{0x00,0x00,0x0E,0x00,0x00,0x00,0x00,0x00};					//'k'
uint8_t 					l											[8]								=	{0x00,0x00,0x0F,0x00,0x00,0x00,0x00,0x00};					//'l'
uint8_t 					Semicolon							[8]								=	{0x00,0x00,0x33,0x00,0x00,0x00,0x00,0x00};					//';'
uint8_t 					SingleQuotes					[8]								=	{0x00,0x00,0x34,0x00,0x00,0x00,0x00,0x00};					//'''
uint8_t 					Keycode42							[8]								=	{0x00,0x00,0x32,0x00,0x00,0x00,0x00,0x00};					//'Keycode42'
uint8_t 					LeftEnter							[8]								=	{0x00,0x00,0x28,0x00,0x00,0x00,0x00,0x00};					//'LeftEnter'
uint8_t 					LeftShift							[8]								=	{0x00,0x00,0xE1,0x00,0x00,0x00,0x00,0x00};					//'LeftShift'
uint8_t 					Keycode45							[8]								=	{0x00,0x00,0x64,0x00,0x00,0x00,0x00,0x00};					//'Keycode45'
uint8_t 					z											[8]								=	{0x00,0x00,0x1D,0x00,0x00,0x00,0x00,0x00};					//'z'
uint8_t 					x											[8]								=	{0x00,0x00,0x1B,0x00,0x00,0x00,0x00,0x00};					//'x'
uint8_t 					c											[8]								=	{0x00,0x00,0x06,0x00,0x00,0x00,0x00,0x00};					//'c'
uint8_t 					v											[8]								=	{0x00,0x00,0x19,0x00,0x00,0x00,0x00,0x00};					//'v'
uint8_t 					b											[8]								=	{0x00,0x00,0x05,0x00,0x00,0x00,0x00,0x00};					//'b'
uint8_t 					n											[8]								=	{0x00,0x00,0x11,0x00,0x00,0x00,0x00,0x00};					//'n'
uint8_t 					m											[8]								=	{0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00};					//'m'
uint8_t 					Comma									[8]								=	{0x00,0x00,0x36,0x00,0x00,0x00,0x00,0x00};					//','
uint8_t						Point									[8]								=	{0x00,0x00,0x37,0x00,0x00,0x00,0x00,0x00};					//'.'
uint8_t						ObliqueLine						[8]								=	{0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x00};					//'/'
uint8_t						Keycode56							[8]								=	{0x00,0x00,0x87,0x00,0x00,0x00,0x00,0x00};					//'Keycode56'
uint8_t						RightShift						[8]								=	{0x00,0x00,0xE5,0x00,0x00,0x00,0x00,0x00};					//'RightShift'
uint8_t						LeftCtrl							[8]								=	{0x00,0x00,0xE0,0x00,0x00,0x00,0x00,0x00};					//'LeftCtrl'
uint8_t						LeftAlt								[8]								=	{0x00,0x00,0xE2,0x00,0x00,0x00,0x00,0x00};					//'LeftAlt'
uint8_t						Space									[8]								=	{0x00,0x00,0x2C,0x00,0x00,0x00,0x00,0x00};					//'Space'
uint8_t						RightAlt							[8]								=	{0x00,0x00,0xE6,0x00,0x00,0x00,0x00,0x00};					//'RightAlt'
uint8_t						RightCtrl							[8]								=	{0x00,0x00,0xE4,0x00,0x00,0x00,0x00,0x00};					//'RightCtrl'
uint8_t						Insert								[8]								=	{0x00,0x00,0x49,0x00,0x00,0x00,0x00,0x00};					//'Insert'
uint8_t						Delete								[8]								=	{0x00,0x00,0x4C,0x00,0x00,0x00,0x00,0x00};					//'Delete'
uint8_t						LeftArrow							[8]								=	{0x00,0x00,0x50,0x00,0x00,0x00,0x00,0x00};					//'LeftArrow'
uint8_t						Home									[8]								=	{0x00,0x00,0x4A,0x00,0x00,0x00,0x00,0x00};					//'Home'
uint8_t						End										[8]								=	{0x00,0x00,0x4D,0x00,0x00,0x00,0x00,0x00};					//'End'
uint8_t						UpArrow								[8]								=	{0x00,0x00,0x52,0x00,0x00,0x00,0x00,0x00};					//'UpArrow'
uint8_t						DownArrow							[8]								=	{0x00,0x00,0x51,0x00,0x00,0x00,0x00,0x00};					//'DownArrow'
uint8_t						PgUp									[8]								=	{0x00,0x00,0x4B,0x00,0x00,0x00,0x00,0x00};					//'PgUp'
uint8_t						PgDn									[8]								=	{0x00,0x00,0x4E,0x00,0x00,0x00,0x00,0x00};					//'PgDn'
uint8_t						RightArrow						[8]								=	{0x00,0x00,0x4F,0x00,0x00,0x00,0x00,0x00};					//'RightArrow'
uint8_t						NumLock								[8]								=	{0x00,0x00,0x53,0x00,0x00,0x00,0x00,0x00};					//'NumLock'
uint8_t						sSeven								[8]								=	{0x00,0x00,0x5F,0x00,0x00,0x00,0x00,0x00};					//'7'
uint8_t						sFour									[8]								=	{0x00,0x00,0x5C,0x00,0x00,0x00,0x00,0x00};					//'4'
uint8_t						sOne									[8]								=	{0x00,0x00,0x59,0x00,0x00,0x00,0x00,0x00};					//'1'
uint8_t						Divide								[8]								=	{0x00,0x00,0x54,0x00,0x00,0x00,0x00,0x00};					//'/'
uint8_t						sEight								[8]								=	{0x00,0x00,0x60,0x00,0x00,0x00,0x00,0x00};					//'8'
uint8_t						sFive									[8]								=	{0x00,0x00,0x5D,0x00,0x00,0x00,0x00,0x00};					//'5'
uint8_t						sTwo									[8]								=	{0x00,0x00,0x5A,0x00,0x00,0x00,0x00,0x00};					//'2'
uint8_t						sZero									[8]								=	{0x00,0x00,0x62,0x00,0x00,0x00,0x00,0x00};					//'0'
uint8_t						sStar									[8]								=	{0x00,0x00,0x55,0x00,0x00,0x00,0x00,0x00};					//'*'
uint8_t						sNine									[8]								=	{0x00,0x00,0x61,0x00,0x00,0x00,0x00,0x00};					//'9'
uint8_t						sSix									[8]								=	{0x00,0x00,0x5E,0x00,0x00,0x00,0x00,0x00};					//'6'
uint8_t						sThree								[8]								=	{0x00,0x00,0x5B,0x00,0x00,0x00,0x00,0x00};					//'3'
uint8_t						sDot									[8]								=	{0x00,0x00,0x63,0x00,0x00,0x00,0x00,0x00};					//'.'
uint8_t						sSub									[8]								=	{0x00,0x00,0x56,0x00,0x00,0x00,0x00,0x00};					//'-'
uint8_t						sPlus									[8]								=	{0x00,0x00,0x57,0x00,0x00,0x00,0x00,0x00};					//'+'
uint8_t						Keycode107						[8]								=	{0x00,0x00,0x85,0x00,0x00,0x00,0x00,0x00};					//'Keycode107'
uint8_t						RightEnter						[8]								=	{0x00,0x00,0x58,0x00,0x00,0x00,0x00,0x00};					//'RightEnter'
uint8_t						Esc										[8]								=	{0x00,0x00,0x29,0x00,0x00,0x00,0x00,0x00};					//'Esc'
uint8_t						F1										[8]								=	{0x00,0x00,0x3A,0x00,0x00,0x00,0x00,0x00};					//'F1'
uint8_t						F2										[8]								=	{0x00,0x00,0x3B,0x00,0x00,0x00,0x00,0x00};					//'F2'
uint8_t						F3										[8]								=	{0x00,0x00,0x3C,0x00,0x00,0x00,0x00,0x00};					//'F3'
uint8_t						F4										[8]								=	{0x00,0x00,0x3D,0x00,0x00,0x00,0x00,0x00};					//'F4'
uint8_t						F5										[8]								=	{0x00,0x00,0x3E,0x00,0x00,0x00,0x00,0x00};					//'F5'
uint8_t						F6										[8]								=	{0x00,0x00,0x3F,0x00,0x00,0x00,0x00,0x00};					//'F6'
uint8_t						F7										[8]								=	{0x00,0x00,0x40,0x00,0x00,0x00,0x00,0x00};					//'F7'
uint8_t						F8										[8]								=	{0x00,0x00,0x41,0x00,0x00,0x00,0x00,0x00};					//'F8'
uint8_t						F9										[8]								=	{0x00,0x00,0x42,0x00,0x00,0x00,0x00,0x00};					//'F9'
uint8_t						F10										[8]								=	{0x00,0x00,0x43,0x00,0x00,0x00,0x00,0x00};					//'F10'
uint8_t						F11										[8]								=	{0x00,0x00,0x44,0x00,0x00,0x00,0x00,0x00};					//'F11'
uint8_t						F12										[8]								=	{0x00,0x00,0x45,0x00,0x00,0x00,0x00,0x00};					//'F12'
uint8_t						PrintScreen						[8]								=	{0x00,0x00,0x46,0x00,0x00,0x00,0x00,0x00};					//'PrintScreen'
uint8_t						ScrollLock						[8]					  		=	{0x00,0x00,0x47,0x00,0x00,0x00,0x00,0x00};					//'ScrollLock'
uint8_t						Pause									[8]					  		=	{0x00,0x00,0x48,0x00,0x00,0x00,0x00,0x00};					//'Pause'

 /**（有shift）*/
uint8_t 					Wave									[8]								=	{0x02,0x00,0x35,0x00,0x00,0x00,0x00,0x00};					//'~'
uint8_t 					Exclamation						[8]								=	{0x02,0x00,0x1E,0x00,0x00,0x00,0x00,0x00};					//'!'
uint8_t 					At										[8]								=	{0x02,0x00,0x1F,0x00,0x00,0x00,0x00,0x00};					//'@'
uint8_t 					Well									[8]								=	{0x02,0x00,0x20,0x00,0x00,0x00,0x00,0x00};					//'#'
uint8_t 					Dollar								[8]								=	{0x02,0x00,0x21,0x00,0x00,0x00,0x00,0x00};					//'$'
uint8_t 					Percent								[8]								=	{0x02,0x00,0x22,0x00,0x00,0x00,0x00,0x00};					//'%'
uint8_t 					UpAngleBrackets				[8]								=	{0x02,0x00,0x23,0x00,0x00,0x00,0x00,0x00};					//'^'
uint8_t 					And										[8]								=	{0x02,0x00,0x24,0x00,0x00,0x00,0x00,0x00};					//'&'
uint8_t 					Star									[8]								=	{0x02,0x00,0x25,0x00,0x00,0x00,0x00,0x00};					//'*'
uint8_t 					LeftParenthesis				[8]								=	{0x02,0x00,0x26,0x00,0x00,0x00,0x00,0x00};					//'('
uint8_t 					RightParenthesis			[8]								=	{0x02,0x00,0x27,0x00,0x00,0x00,0x00,0x00};					//')'
uint8_t 					DownLine							[8]								=	{0x02,0x00,0x2D,0x00,0x00,0x00,0x00,0x00};					//'_'
uint8_t 					Plus									[8]								=	{0x02,0x00,0x2E,0x00,0x00,0x00,0x00,0x00};					//'+'
uint8_t 					Q											[8]								=	{0x02,0x00,0x14,0x00,0x00,0x00,0x00,0x00};					//'Q'
uint8_t 					W											[8]								=	{0x02,0x00,0x1A,0x00,0x00,0x00,0x00,0x00};					//'W'
uint8_t 					E											[8]								=	{0x02,0x00,0x08,0x00,0x00,0x00,0x00,0x00};					//'E'
uint8_t 					R											[8]								=	{0x02,0x00,0x15,0x00,0x00,0x00,0x00,0x00};					//'R'
uint8_t 					T											[8]								=	{0x02,0x00,0x17,0x00,0x00,0x00,0x00,0x00};					//'T'
uint8_t 					Y											[8]								=	{0x02,0x00,0x1C,0x00,0x00,0x00,0x00,0x00};					//'Y'
uint8_t 					U											[8]								=	{0x02,0x00,0x18,0x00,0x00,0x00,0x00,0x00};					//'U'
uint8_t 					I											[8]								=	{0x02,0x00,0x0C,0x00,0x00,0x00,0x00,0x00};					//'I'
uint8_t 					O											[8]								=	{0x02,0x00,0x12,0x00,0x00,0x00,0x00,0x00};					//'O'
uint8_t 					P											[8]								=	{0x02,0x00,0x13,0x00,0x00,0x00,0x00,0x00};					//'P'
uint8_t 					Leftbrace							[8]								=	{0x02,0x00,0x2F,0x00,0x00,0x00,0x00,0x00};					//'{'
uint8_t 					Rightbrace						[8]								=	{0x02,0x00,0x30,0x00,0x00,0x00,0x00,0x00};					//'}'
uint8_t 					PerpendicularLine			[8]								=	{0x02,0x00,0x31,0x00,0x00,0x00,0x00,0x00};					//'|'
uint8_t 					A											[8]								=	{0x02,0x00,0x04,0x00,0x00,0x00,0x00,0x00};					//'A'
uint8_t 					S											[8]								=	{0x02,0x00,0x16,0x00,0x00,0x00,0x00,0x00};					//'S'
uint8_t 					D											[8]								=	{0x02,0x00,0x07,0x00,0x00,0x00,0x00,0x00};					//'D'
uint8_t 					F											[8]								=	{0x02,0x00,0x09,0x00,0x00,0x00,0x00,0x00};					//'F'
uint8_t 					G											[8]								=	{0x02,0x00,0x0A,0x00,0x00,0x00,0x00,0x00};					//'G'
uint8_t 					H											[8]								=	{0x02,0x00,0x0B,0x00,0x00,0x00,0x00,0x00};					//'H'
uint8_t 					J											[8]								=	{0x02,0x00,0x0D,0x00,0x00,0x00,0x00,0x00};					//'J'
uint8_t 					K											[8]								=	{0x02,0x00,0x0E,0x00,0x00,0x00,0x00,0x00};					//'K'
uint8_t 					L											[8]								=	{0x02,0x00,0x0F,0x00,0x00,0x00,0x00,0x00};					//'L'
uint8_t 					Colon									[8]								=	{0x02,0x00,0x33,0x00,0x00,0x00,0x00,0x00};					//':'
uint8_t 					DoubleQuotationMarks	[8]								=	{0x02,0x00,0x34,0x00,0x00,0x00,0x00,0x00};					//'"'
uint8_t 					Z											[8]								=	{0x02,0x00,0x1D,0x00,0x00,0x00,0x00,0x00};					//'Z'
uint8_t 					X											[8]								=	{0x02,0x00,0x1B,0x00,0x00,0x00,0x00,0x00};					//'X'
uint8_t 					C											[8]								=	{0x02,0x00,0x06,0x00,0x00,0x00,0x00,0x00};					//'C'
uint8_t 					V											[8]								=	{0x02,0x00,0x19,0x00,0x00,0x00,0x00,0x00};					//'V'
uint8_t 					B											[8]								=	{0x02,0x00,0x05,0x00,0x00,0x00,0x00,0x00};					//'B'
uint8_t 					N											[8]								=	{0x02,0x00,0x11,0x00,0x00,0x00,0x00,0x00};					//'N'
uint8_t 					M											[8]								=	{0x02,0x00,0x10,0x00,0x00,0x00,0x00,0x00};					//'M'
uint8_t 					LeftAngleBracket			[8]								=	{0x02,0x00,0x36,0x00,0x00,0x00,0x00,0x00};					//'<'
uint8_t						RightAngleBracket			[8]								=	{0x02,0x00,0x37,0x00,0x00,0x00,0x00,0x00};					//'>'
uint8_t						QuestionMark					[8]								=	{0x02,0x00,0x38,0x00,0x00,0x00,0x00,0x00};					//'?'
/***********************************************************************************************************************/



/**-------------------------------------多媒体部分--------------------------------------------------------------*/
//电源控制部分
uint8_t 					sleep									[11]							={0x57,0xAB,0x00,0x03,0x02,0x01,0x82,0x8A,0xFF,0x0D,0x0A};							//睡眠
uint8_t 					Power									[11]							={0x57,0xAB,0x00,0x03,0x02,0x01,0x81,0x89,0xFF,0x0D,0x0A};							//关机？
uint8_t 					WakeUp								[11]							={0x57,0xAB,0x00,0x03,0x02,0x01,0x84,0x8C,0xFF,0x0D,0x0A};							//唤醒
uint8_t 					up										[11]							={0x57,0xAB,0x00,0x03,0x02,0x01,0x00,0x08,0xFF,0x0D,0x0A};							//按键释放

//多媒体控制部分
uint8_t 					VolumeDec							[13]							={0x57,0xAB,0x00,0x03,0x04,0x02,0x02,0x00,0x00,0x0D,0xFF,0x0D,0x0A};		//降低音量 最后两字节是0D 0A !!!!!!
uint8_t 					VolumeInc							[13]							={0x57,0xAB,0x00,0x03,0x04,0x02,0x01,0x00,0x00,0x0C,0xFF,0x0D,0x0A};		//提升音量
uint8_t 					Mute									[13]							={0x57,0xAB,0x00,0x03,0x04,0x02,0x04,0x00,0x00,0x0F,0xFF,0x0D,0x0A};		//静音
uint8_t 					Calculator						[13]							={0x57,0xAB,0x00,0x03,0x04,0x02,0x00,0x00,0x04,0x0F,0xFF,0x0D,0x0A};		//计算器
uint8_t 					EMail									[13]							={0x57,0xAB,0x00,0x03,0x04,0x02,0x00,0x01,0x00,0x0C,0xFF,0x0D,0x0A};		//邮箱
uint8_t 					Search								[13]							={0x57,0xAB,0x00,0x03,0x04,0x02,0x00,0x02,0x00,0x0D,0xFF,0x0D,0x0A};		//搜索
uint8_t 					Explorer							[13]							={0x57,0xAB,0x00,0x03,0x04,0x02,0x00,0x00,0x02,0x0D,0xFF,0x0D,0x0A};		//浏览器
uint8_t 					ScreenSave						[13]							={0x57,0xAB,0x00,0x03,0x04,0x02,0x00,0x00,0x08,0x13,0xFF,0x0D,0x0A};		//浏览器

//按键释放
uint8_t						KeyRelease						[13]							={0x57,0xAB,0x00,0x03,0x04,0x02,0x00,0x00,0x00,0x0B,0xFF,0x0D,0x0A};
/**-------------------------------------------------------------------------------------------------------------*/




/********************************************************ASCLL码*******************************************************/
/**按照ASCLL码表，数组前33位应该被填充
	SendCommand((uint8_t*)ascll[126]);
*/
uint32_t ascll[127]={
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,
	(uint32_t)&Exclamation													 ,				//' ! ' 
	(uint32_t)&DoubleQuotationMarks                  ,        //' " '
	(uint32_t)&Well                                  ,        //' # '
	(uint32_t)&Dollar                                ,        //' $ '
	(uint32_t)&Percent                               ,        //' % '
	(uint32_t)&And                                   ,        //' & '
	(uint32_t)&SingleQuotes					                 ,        //' ' '
	(uint32_t)&LeftParenthesis                       ,        //' ( '
	(uint32_t)&RightParenthesis                      ,        //' ) '
	(uint32_t)&Star                                  ,        //' * '
	(uint32_t)&Plus                                  ,        //' + '
	(uint32_t)&Comma								                 ,        //' , '
	(uint32_t)&Line                                	 ,        //' - '
	(uint32_t)&Point								                 ,        //' . '
	(uint32_t)&ObliqueLine					                 ,        //' / '
	(uint32_t)&Zero                                  ,        //' 0 '
	(uint32_t)&One                                   ,        //' 1 '
	(uint32_t)&Two                                   ,        //' 2 '
	(uint32_t)&Three                                 ,        //' 3 '
	(uint32_t)&Four                                  ,        //' 4 '
	(uint32_t)&Five                                  ,        //' 5 '
	(uint32_t)&Six                                   ,        //' 6 '
	(uint32_t)&Seven                                 ,        //' 7 '
	(uint32_t)&Eight                                 ,        //' 8 '
	(uint32_t)&Nine                                  ,        //' 9 '
	(uint32_t)&Colon                                 ,        //' : '
	(uint32_t)&Semicolon						                 ,        //' ; '
	(uint32_t)&LeftAngleBracket                      ,        //' < '
	(uint32_t)&Equal                                 ,        //' = '
	(uint32_t)&RightAngleBracket                     ,        //' > '
	(uint32_t)&QuestionMark													 ,        //' ? '
	(uint32_t)&At                                    ,        //' @ '
	(uint32_t)&A                                     ,        //' A '
	(uint32_t)&B                                     ,        //' B '
	(uint32_t)&C                                     ,        //' C '
	(uint32_t)&D                                     ,        //' D '
	(uint32_t)&E                                     ,        //' E '
	(uint32_t)&F                                     ,        //' F '
	(uint32_t)&G                                     ,        //' G '
	(uint32_t)&H                                     ,        //' H '
	(uint32_t)&I                                     ,        //' I '
	(uint32_t)&J                                     ,        //' J '
	(uint32_t)&K                                     ,        //' K '
	(uint32_t)&L                                     ,        //' L '
	(uint32_t)&M                                     ,        //' M '
	(uint32_t)&N                                     ,        //' N '
	(uint32_t)&O                                     ,        //' O '
	(uint32_t)&P                                     ,        //' P '
	(uint32_t)&Q                                     ,        //' Q '
	(uint32_t)&R                                     ,        //' R '
	(uint32_t)&S                                     ,        //' S '
	(uint32_t)&T                                     ,        //' T '
	(uint32_t)&U                                     ,        //' U '
	(uint32_t)&V                                     ,        //' V '
	(uint32_t)&W                                     ,        //' W '
	(uint32_t)&X                                     ,        //' X '
	(uint32_t)&Y                                     ,        //' Y '
	(uint32_t)&Z                                     ,        //' Z '
	(uint32_t)&LeftSquareBrackets		                 ,        //' [ '
	(uint32_t)&Backlash															 ,        //' \ '
	(uint32_t)&RightSquareBrackets	                 ,        //' ] '
	(uint32_t)&UpAngleBrackets                       ,        //' ^ '
	(uint32_t)&DownLine                              ,        //' _ '
	(uint32_t)&Pie                                   ,        //' ` '
	(uint32_t)&a										                 ,        //' a '
	(uint32_t)&b										                 ,        //' b '
	(uint32_t)&c										                 ,        //' c '
	(uint32_t)&d										                 ,        //' d '
	(uint32_t)&e										                 ,        //' e '
	(uint32_t)&f										                 ,        //' f '
	(uint32_t)&g										                 ,        //' g '
	(uint32_t)&h										                 ,        //' h '
	(uint32_t)&i										                 ,        //' i '
	(uint32_t)&j										                 ,        //' j '
	(uint32_t)&k										                 ,        //' k '
	(uint32_t)&l										                 ,        //' l '
	(uint32_t)&m										                 ,        //' m '
	(uint32_t)&n										                 ,        //' n '
	(uint32_t)&o										                 ,        //' o '
	(uint32_t)&p										                 ,        //' p '
	(uint32_t)&q                                     ,        //' q '
	(uint32_t)&r										                 ,        //' r '
	(uint32_t)&s										                 ,        //' s '
	(uint32_t)&t										                 ,        //' t '
	(uint32_t)&u										                 ,        //' u '
	(uint32_t)&v										                 ,        //' v '
	(uint32_t)&w										                 ,        //' w '
	(uint32_t)&x										                 ,        //' x '
	(uint32_t)&y										                 ,        //' y '
	(uint32_t)&z										                 ,        //' z '
	(uint32_t)&Leftbrace                             ,        //' { '
	(uint32_t)&PerpendicularLine										 ,        //' | '
	(uint32_t)&Rightbrace                            ,        //' } '
	(uint32_t)&Wave                                  ,        //' ~ '
/*	多余、无用
												(uint32_t)&Keycode14                             ,
												(uint32_t)&BackSpace                             ,
												(uint32_t)&Tab                                   ,																						 
												(uint32_t)&CapsLock							                 ,																		 
												(uint32_t)&Keycode42						                 ,
												(uint32_t)&LeftEnter						                 ,
												(uint32_t)&LeftShift						                 ,
												(uint32_t)&Keycode45						                 ,																		 
												(uint32_t)&Keycode56						                 ,
												(uint32_t)&RightShift						                 ,
												(uint32_t)&LeftCtrl							                 ,
												(uint32_t)&LeftAlt							                 ,
												(uint32_t)&Space						                 	   ,
												(uint32_t)&RightAlt							                 ,
												(uint32_t)&RightCtrl						                 ,
												(uint32_t)&Insert								                 ,
												(uint32_t)&Delete								                 ,
												(uint32_t)&LeftArrow						                 ,
												(uint32_t)&Home									                 ,
												(uint32_t)&End									                 ,
												(uint32_t)&UpArrow							                 ,
												(uint32_t)&DownArrow						                 ,
												(uint32_t)&PgUp									                 ,
												(uint32_t)&PgDn									                 ,
												(uint32_t)&RightArrow						                 ,
												(uint32_t)&NumLock							                 ,
												(uint32_t)&sSeven								                 ,
												(uint32_t)&sFour								                 ,
												(uint32_t)&sOne									                 ,
												(uint32_t)&Divide								                 ,
												(uint32_t)&sEight								                 ,
												(uint32_t)&sFive								                 ,
												(uint32_t)&sTwo									                 ,
												(uint32_t)&sZero								                 ,
												(uint32_t)&sStar								                 ,
												(uint32_t)&sNine								                 ,
												(uint32_t)&sSix									                 ,
												(uint32_t)&sThree								                 ,
												(uint32_t)&sDot									                 ,
												(uint32_t)&sSub									                 ,
												(uint32_t)&sPlus								                 ,
												(uint32_t)&Keycode107						                 ,
												(uint32_t)&RightEnter						                 ,
												(uint32_t)&Esc									                 ,
												(uint32_t)&F1										                 ,
												(uint32_t)&F2										                 ,
												(uint32_t)&F3										                 ,
												(uint32_t)&F4										                 ,
												(uint32_t)&F5										                 ,
												(uint32_t)&F6										                 ,
												(uint32_t)&F7										                 ,
												(uint32_t)&F8										                 ,
												(uint32_t)&F9										                 ,
												(uint32_t)&F10									                 ,
												(uint32_t)&F11									                 ,
												(uint32_t)&F12									                 ,
												(uint32_t)&PrintScreen					                 ,
												(uint32_t)&ScrollLock					                   ,
												(uint32_t)&Pause																 ,
*/
};
/***************************************************************************************************************/
uint8_t CH_CONFIG[50] = {0x00,0x80,0x00,0x00,0x00,0x25,0x80,0x08,0x00,0x00,
												 0x03,0x86,0x1A,0x29,0xE1,0x00,0x00,0x00,0x01,0x00,
												 0x0D,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
												 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
												 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
												 
void CH9329_Init(void)		//CH9329引脚初始化
{
	GPIO_InitTypeDef gpio;
	__HAL_RCC_GPIOA_CLK_ENABLE();
	
	/* 复位引脚默认低电平 */
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_SET);		//SET脚默认高电平
	
	/* 复位引脚配置 */
	gpio.Mode=GPIO_MODE_OUTPUT_PP;
	gpio.Pin=GPIO_PIN_12;
	gpio.Pull=GPIO_PULLDOWN;
	gpio.Speed=GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA,&gpio);
	
	/* SET脚配置 */
	gpio.Mode=GPIO_MODE_OUTPUT_PP;
	gpio.Pin=GPIO_PIN_5;
	gpio.Pull=GPIO_PULLDOWN;
	gpio.Speed=GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOB,&gpio);
}

void CH9329_Reset(void)
{
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12,GPIO_PIN_SET);
	Delay_ms(200);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12,GPIO_PIN_RESET);
}

void CH9329_WorkMode_Config(uint8_t workmode)
{
	CH_CONFIG[0] = workmode;
}

void CH9329_SerialMode_Config(uint8_t serialmode)
{
	CH_CONFIG[1] = serialmode;
}

void CH9329_SerialAddr_Config(uint8_t addr)
{
	CH_CONFIG[2] = addr;
}

void CH9329_SerialBaudRate_Config(uint8_t* baudrate)
{
	CH_CONFIG[3] = baudrate[0];
	CH_CONFIG[4] = baudrate[1];
	CH_CONFIG[5] = baudrate[2];
	CH_CONFIG[6] = baudrate[3];
}

void CH9329_SerialInterval_Config(uint8_t* interval)
{
	CH_CONFIG[9] = interval[0];
	CH_CONFIG[10] = interval[1];
}

void CH9329_Vid_Pid_Config(uint8_t* vid,uint8_t* pid)
{
	CH_CONFIG[11] = vid[1];
	CH_CONFIG[12] = vid[0];
	CH_CONFIG[13] = pid[1];
	CH_CONFIG[14] = pid[0];
}



void CH9329_Config()
{
	Para_Cfg config;
	
}

void Combine( uint8_t *head, uint8_t *body)		//字节拼接
{
	for(int i=0;i<5;i++){
		FIXED[i]=head[i];
	}
	for(int b=5;b<13;b++){
		FIXED[b]=body[b-5];
	}
	for(int s=0;s<13;s++){
		CHECK+=FIXED[s];
	}
	FIXED[13]=CHECK;
	FIXED[14]=0xFF;
	FIXED[15]=0x0D;
	FIXED[16]=0x0A;
	//Usart1_SendString(FIXED);
	HAL_UART_Transmit(&KEYOUT,FIXED,17,1000);
	CHECK=0;			//清除校验和
}

void SendCommand( uint8_t *body)
{
	Combine(FIXED_HEAD,body);
	Delay_ms(1);
	//Usart1_SendString(KeyUP);
	HAL_UART_Transmit(&KEYOUT,KeyUP,20,1000);
	Delay_ms(1);
}


/**配置组合键  控制键+按键*/

uint8_t *Combination( uint8_t *control, uint8_t *key)
{
	for(int i=0;i<8;i++){
		CB[i]=control[i];
	}
	CB[2]=key[2];
	return CB;
}


//uint8_t word[100]={"0"};		//用来接收串口数据
uint8_t result[103];													//用于存储转换结果
uint8_t len;																	//记录数据长度
/**把字符串转换为ASCLL码序号*/
void toASCLL( uint8_t *asc)
{
	len=strlen((char*)asc);
	for(int i=0;i<len;i++){
		result[i]=(char)asc[i];
	}
	result[len+1]=0xFF;
	result[len+2]=0x0D;
	result[len+3]=0x0A;
}

void Get_Cfg(void)
{
	uint8_t cmd[6] = {0x57,0xAB,0x00,0x08,0x00};
	uint8_t checksum = 0;
	for(uint8_t i=0;i<5;i++){
		checksum+=cmd[i];
	}
	cmd[5] = checksum;
	
	HAL_UART_Transmit(&KEYOUT,cmd,6,1000);
}

void Set_Cfg(void)
{
	uint8_t cmd[56] = {0x57,0xAB,0x00,0x09,0x32};
	uint8_t checksum = 0;
	for(uint8_t i=0;i<55;i++){
		cmd[i+5] = CH_CONFIG[i];
		checksum += cmd[i];
	}
	cmd[55] = checksum;
	HAL_UART_Transmit(&KEYOUT,cmd,56,1000);
}

/************************************ 淘汰字符串发送函数  *****************************************************
void SendWords(const uint8_t *w1,const uint8_t *w2,const uint8_t *w3,const uint8_t *w4,const uint8_t *w5,
							const uint8_t *w6,const uint8_t *w7,const uint8_t *w8,const uint8_t *w9,const uint8_t *w10,const uint8_t num)
{
	switch(num){
		case 1:
			SendCommand(w1);
			break;
		case 2:
			SendCommand(w1);
			SendCommand(w2);
			break;
		case 3:
			SendCommand(w1);
			SendCommand(w2);
			SendCommand(w3);
			break;
		case 4:
			SendCommand(w1);
			SendCommand(w2);
			SendCommand(w3);
			SendCommand(w4);
			break;
		case 5:
			SendCommand(w1);
			SendCommand(w2);
			SendCommand(w3);
			SendCommand(w4);
			SendCommand(w5);
			break;
		case 6:
			SendCommand(w1);
			SendCommand(w2);
			SendCommand(w3);
			SendCommand(w4);
			SendCommand(w5);
			SendCommand(w6);
			break;
		case 7:
			SendCommand(w1);
			SendCommand(w2);
			SendCommand(w3);
			SendCommand(w4);
			SendCommand(w5);
			SendCommand(w6);
			SendCommand(w7);
			break;
		case 8:
			SendCommand(w1);
			SendCommand(w2);
			SendCommand(w3);
			SendCommand(w4);
			SendCommand(w5);
			SendCommand(w6);
			SendCommand(w7);
			SendCommand(w8);
			break;
		case 9:
			SendCommand(w1);
			SendCommand(w2);
			SendCommand(w3);
			SendCommand(w4);
			SendCommand(w5);
			SendCommand(w6);
			SendCommand(w7);
			SendCommand(w8);
			SendCommand(w9);
			break;
		case 10:
			SendCommand(w1);
			SendCommand(w2);
			SendCommand(w3);
			SendCommand(w4);
			SendCommand(w5);
			SendCommand(w6);
			SendCommand(w7);
			SendCommand(w8);
			SendCommand(w9);
			SendCommand(w10);
			break;
		default:
			break;
	}
}*/




