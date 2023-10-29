#ifndef __SYS_H
#define __SYS_H

#include "stm32f1xx.h"

/**
 * SYS_SUPPORT_OS用于定义系统文件夹是否支持OS
 * 0,不支持OS
 * 1,支持OS
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

void sys_nvic_set_vector_table(uint32_t baseaddr, uint32_t offset);             /* 设置中断偏移量 */
void sys_standby(void);                                                         /* 进入待机模式 */
void sys_soft_reset(void);                                                      /* 系统软复位 */
uint8_t sys_clock_set(uint32_t plln);                                           /* 时钟设置函数 */
void Task_Create(void);

/* 以下为汇编函数 */
void sys_wfi_set(void);                                                         /* 执行WFI指令 */
void sys_intx_disable(void);                                                    /* 关闭所有中断 */
void sys_intx_enable(void);                                                     /* 开启所有中断 */
void sys_msr_msp(uint32_t addr);                                                /* 设置栈顶地址 */

#endif











