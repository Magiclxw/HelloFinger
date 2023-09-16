#ifndef _CRC_H_
#define _CRC_H_

#include "stm32f1xx.h"

void CRC_Init(void);
uint32_t Calc_CRC(uint8_t *data,uint8_t len);
#endif
