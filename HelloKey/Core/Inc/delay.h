#ifndef __DELAY_H
#define __DELAY_H
#include "stm32f1xx.h"



void Delay_Init(void);
void Delay_us(uint32_t us);
void Delay_ms(uint16_t ms);
#endif
