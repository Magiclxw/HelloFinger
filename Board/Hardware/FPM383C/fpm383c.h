#ifndef __FPM383C_H
#define __FPM383C_H
#include "stm32f1xx.h"

/*														÷∏¡Ó≥§∂»																			*/
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
#define 					GetImageSize									12
#define 					GenCharSize										13
#define 					RegModelSize									12
#define 					StoreCharSize									15
#define 					MatchSize											12
/****************************************************************************/

#define 					LED_FUNC_BREATHE						1
#define 					LED_FUNC_BLINK							2
#define 					LED_FUNC_OPEN								3
#define 					LED_FUNC_CLOSE							4
#define 					LED_FUNC_OPEN_SLOW					5
#define 					LED_FUNC_CLOSE_SLOW					6
#define 					LED_COLOR_BLUE							0x01
#define 					LED_COLOR_GREEN							0x02
#define 					LED_COLOR_RED								0x04


extern uint8_t PS_AutoEnroll[AutoEnrollSize];
extern uint8_t PS_AutoIdentify[AutoIdentifySize];
extern uint8_t PS_DeletChar[DeletCharSize];
extern uint8_t PS_Cancel[CancelSize];
extern uint8_t PS_Sleep[SleepSize];
extern uint8_t PS_ValidTempleteNum[ValidTempleteNumSize];
extern uint8_t PS_ReadIndexTable[ReadIndexTableSize];
extern uint8_t PS_SetPwd[SetPwdSize];
extern uint8_t PS_VfyPwd[VfyPwdSize];
extern uint8_t PS_GetChipEcho[GetChipEchoSize];
extern uint8_t PS_AutoCaiSensor[AutoCaiSensorSize];
extern uint8_t PS_ControlBLN[ControlBLNSize];
extern uint8_t PS_GetDummyTempleteNo[GetDummyTempleteNoSize];

extern uint8_t PS_GetChipSN[GetChipSNSize];
extern uint8_t PS_HandShake[HandShakeSize];
extern uint8_t PS_CheckSensor[CheckSensorSize];
extern uint8_t PS_SetChipAddr[SetChipAddrSize];
extern uint8_t PS_WriteNotepad[WriteNotepadSize];
extern uint8_t PS_ReadNotepad[ReadNotepadSize];
extern uint8_t	PS_GetImage[GetImageSize];
extern uint8_t PS_GenChar[GenCharSize];
extern uint8_t PS_RegModel[RegModelSize];
extern uint8_t PS_StoreChar[StoreCharSize];
extern uint8_t PS_Match[MatchSize];

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
uint8_t *CMD_ControlBLN(uint8_t FUNC,uint8_t startcolor,uint8_t endcolor,uint8_t cycle);
void CMD_GetDummyTempleteNo(void);

void CMD_GetChipSN(void);
void CMD_HandShake(void);
void CMD_CheckSensor(void);
void CMD_SetChipAddr(uint8_t *Addr);
void CMD_WriteNotePad(uint8_t Page,uint8_t *Content);
void CMD_ReadNotepad(uint8_t Page);
void CMD_GetImage(void);
void CMD_GenChar(uint8_t BufferID);
void CMD_RegModel(void);
void CMD_StoreChar(uint8_t BufferID,uint16_t PageID);
void CMD_Match(void);



#endif
