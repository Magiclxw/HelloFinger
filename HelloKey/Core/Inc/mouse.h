#ifndef __MOUSE_H
#define	__MOUSE_H
#include "stm32f1xx.h"

/**œ‡∂‘ Û±Í*/
extern 			 uint8_t					Move2Center						[16]						;
extern uint8_t 					PressLeft							[17]            ;
extern uint8_t 					PressRight						[17]            ;
extern uint8_t 					PressMiddle						[17]            ;
extern uint8_t 					PressRelease					[17]            ;
extern uint8_t 					MiddleUp							[17]						;
extern uint8_t 					MiddleDw							[17]						;
extern uint8_t result[103];
extern uint8_t word[100];
extern uint8_t len;

void Cal(uint16_t X,uint16_t Y);

#endif
