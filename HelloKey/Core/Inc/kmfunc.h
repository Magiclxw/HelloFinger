#ifndef __KMFUNC_H
#define __KMFUNC_H
#include "stm32f1xx.h"

extern uint8_t Response[100];
extern uint8_t nums;




void UnLock(uint16_t X,uint16_t Y);
void Sendtest( uint8_t *asc);
void CMD_GET_INFO(void);
void CMD_GET_PARA_CFG(void);
void DATA_Judge(uint8_t *Data , uint8_t Length);

#endif
