#ifndef __SYS_H
#define __SYS_H

#include "stm32f1xx.h"

/**
 * SYS_SUPPORT_OS���ڶ���ϵͳ�ļ����Ƿ�֧��OS
 * 0,��֧��OS
 * 1,֧��OS
 */
#define SYS_SUPPORT_OS          1

typedef struct _SYSTEM_INFO_
{
	char *compile_date;
	char *compile_time;
	char firmware_version[10];
}_SYSTEM_INFO_t;

typedef struct JOYSTICK_INIT_PARAM_
{
	uint8_t JOYSTICK_INIT_PARAM_MIN_OFFSET;
	uint8_t JOYSTICK_INIT_PARAM_MAX_OFFSET;
	uint16_t JOYSTICK_INIT_PARAM_DEFAULT_LOW_THRESHOLD;
	uint16_t JOYSTICK_INIT_PARAM_DEFAULT_HIGH_THRESHOLD;
}JOYSTICK_INIT_PARAM_t;

typedef struct CH9329_INIT_PARAM_
{
	uint8_t CH9329_WORKMODE;
	uint8_t CH9329_SERIALMODE;
	uint8_t CH9329_ADDR;
	uint8_t CH9329_BAUD[4];
	uint8_t CH9329_PACK_INTERVAL[2];
	uint8_t CH9329_VID[2];
	uint8_t CH9329_PID[2];
	uint8_t CH9329_UPLOAD_INTERVAL[2];
	uint8_t CH9329_KEY_RELASE_DELAY[2];
	uint8_t CH9329_AUTOENTER;
	uint8_t CH9329_ENTER_SYMBOL1[4];
	uint8_t CH9329_ENTER_SYMBOL2[4];
	uint8_t CH9329_FILITER_START[4];
	uint8_t CH9329_FILTER_STOP[4];
	uint8_t CH9329_EN_FLAG;
	uint8_t CH9329_KEY_FAST_UPLOAD_FLAG;
}CH9329_INIT_PARAM_t;

typedef struct FPM383_INIT_PARAM_
{
	uint8_t FPM383_INIT_PARAM_ADDR[4];
	uint8_t FPM383_Password[4];
	
}FPM383_INIT_PARAM_t;

typedef struct SYSTEM_INIT_PARAM_
{
	JOYSTICK_INIT_PARAM_t joystick_param;
	CH9329_INIT_PARAM_t ch9329_param;
	FPM383_INIT_PARAM_t fp383_param;
}SYSTEM_INIT_PARAM_t;

void sys_nvic_set_vector_table(uint32_t baseaddr, uint32_t offset);             /* �����ж�ƫ���� */
void sys_standby(void);                                                         /* �������ģʽ */
void sys_soft_reset(void);                                                      /* ϵͳ��λ */
uint8_t sys_clock_set(uint32_t plln);                                           /* ʱ�����ú��� */
void Task_Create(void);

/* ����Ϊ��ຯ�� */
void sys_wfi_set(void);                                                         /* ִ��WFIָ�� */
void sys_intx_disable(void);                                                    /* �ر������ж� */
void sys_intx_enable(void);                                                     /* ���������ж� */
void sys_msr_msp(uint32_t addr);                                                /* ����ջ����ַ */

#endif











