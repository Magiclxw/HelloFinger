#ifndef __DELAY_H
#define __DELAY_H

#include "sys.h"


void delay_init(uint16_t sysclk);
void delay_ms(uint16_t nms);
void delay_us(uint32_t nus);

#if (!SYS_SUPPORT_OS)
    void HAL_Delay(uint32_t Delay);
#endif

#endif





























