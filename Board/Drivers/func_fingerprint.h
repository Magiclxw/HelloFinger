#ifndef __FINGERPRINT_H
#define __FINGERPRINT_H

#include "stm32f1xx.h"
#include "usart.h"

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;

#define KEYOUT	huart1
#define FINGER	huart2

#define ENROLL_TIMEOUT					10000
#define ENROLL_STATE_LEAVE			0x01
#define ENROLL_STATE_PUT				0x02
#define ENROLL_STATE_SUCCESS		0x03
#define ENROLL_STATE_REPEAT			0x04
#define ENROLL_STATE_TIMEOUT		0x05

extern uint8_t RX_TableData[44];			//�洢���յ�������
extern uint8_t RX_TableState[8];			//�洢������״̬��Ϣ
extern uint8_t RX_SleepData[12];
extern uint8_t RX_AutoEnrollData[14];
extern uint8_t RX_AutoIdentifyData[17];
extern uint8_t RX_GetDummyTempleteNoData[14];
extern uint8_t RX_ControlBLN[12];
extern uint8_t USB_CMD[100];

uint8_t Calc_Checksum(uint8_t *data);
uint8_t Cmp_Checksum(uint8_t *data);
uint8_t GetTableState(void);
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
uint8_t Con_Register(uint8_t BufferID,uint16_t PageID);
uint8_t GenerateHeadLenCheck(uint8_t *data,uint8_t head);
uint8_t Con_DeleteChar(uint8_t *PageID,uint8_t *N);

#endif