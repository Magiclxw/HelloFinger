#ifndef __ZW800_H
#define __ZW800_H
#include "stm32f1xx.h"

#define 					AutoEnrollSize								17
#define 					AutoIdentifySize							17
#define 					DeletCharSize									16
#define 					CancelSize										12
#define						SleepSize											12
#define 					ValidTempleteNumSize					12
#define 					ReadIndexTableSize						13
#define 					SetPwdSize										16
#define 					VfyPwdSize										16
#define 					GetChipEchoSize								12
#define 					AutoCaiSensorSize							12
#define 					ControlBLNSize								16
#define 					GetDummyTempleteNoSize				12

#define 					GetChipSNSize									13
#define 					HandShakeSize									12
#define 					CheckSensorSize								12
#define 					SetChipAddrSize								16
#define 					WriteNotepadSize							45
#define 					ReadNotepadSize								13


uint8_t *CmdConnect(void);
void Check_Sum_Div(uint16_t sum);
uint8_t * CMD_AutoEnroll(uint8_t *ID,uint8_t NUM,uint8_t *PARAM);
uint8_t *CMD_AutoIdentify(uint8_t secureleval,uint8_t *ID,uint8_t *PARAM);
uint8_t *CMD_DeletChar(uint8_t *PageID,uint8_t *N);
uint8_t *CMD_Cancel(void);
uint8_t *CMD_Sleep(void);
uint8_t *CMD_ValidTempleteNum(void);
uint8_t *CMD_ReadIndexTable(uint8_t page);
uint8_t *CMD_SetPwd(uint8_t *PassWord);
uint8_t *CMD_VfyPwd(uint8_t *PassWord);
uint8_t *CMD_GetChipEcho(void);
uint8_t *CMD_AutoCaiSensor(void);
uint8_t *CMD_ControlBLN(uint8_t FUNC,uint8_t startcolor,uint8_t endcolor,uint8_t circle);
void CMD_GetDummyTempleteNo(void);

void CMD_GetChipSN(void);
void CMD_HandShake(void);
void CMD_CheckSensor(void);
void CMD_SetChipAddr(uint8_t *Addr);
void CMD_WriteNotePad(uint8_t Page,uint8_t *Content);
void CMD_ReadNotepad(uint8_t Page);

#endif
