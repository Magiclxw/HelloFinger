#ifndef __FUNC_H
#define __FUNC_H
#include "stm32f1xx.h"

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;

#define KEYOUT	huart1
#define FINGER	huart2

void GetTableState(void);
uint8_t Con_Sleep(void);
void Con_AutoEnroll(uint8_t *ID,uint8_t NUM,uint8_t *PARAM);
uint8_t Con_AutoIdentify(uint8_t *ID,uint8_t *PARAM);
uint16_t Con_GetDummyTempleteNo(void);
uint8_t Con_ControlBLN(uint8_t FUNC,uint8_t startcolor,uint8_t endcolor,uint8_t circle);

uint8_t Con_GetChipSN(void);
uint8_t Con_HandShake(void);
uint8_t Con_CheckSensor(void);
uint8_t Con_SetPwd(uint8_t *PassWord);
uint8_t Con_VfyPwd(uint8_t *PassWord);
uint8_t Con_SetChipAddr(uint8_t *Addr);
uint8_t Con_WriteNotepad(uint8_t Page,uint8_t *Content);
uint8_t Con_ReadNotepad(uint8_t Page);

#endif
