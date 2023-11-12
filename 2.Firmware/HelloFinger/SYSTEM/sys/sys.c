#include "sys.h"
#include "gpio.h"
#include "dma.h"
#include "drv_w25q128.h"
#include "drv_ch9329.h"
#include "drv_fpm383.h"
#include "drv_joystick.h"
#include "drv_encoder.h"
#include "drv_at24c64.h"
#include "app_task_key.h"
#include "app_task_finger.h"
#include "app_task_rgb.h"
#include "app_task_joystick.h"
#include "app_task_hid_transfer.h"
#include "app_task_encoder.h"


SYSTEM_INIT_PARAM_t g_sys_init_param;
SYSTEM_HARDWARE_INFO_t g_sys_hardware_info;

int System_PARAM_Init(void)
{
	/* 默认系统配置 */
	g_sys_init_param.ch9329_param.CH9329_ADDR = CFG_ADDR;
	g_sys_init_param.ch9329_param.CH9329_BAUD[0] = CFG_BAUD1;
	g_sys_init_param.ch9329_param.CH9329_BAUD[1] = CFG_BAUD2;
	g_sys_init_param.ch9329_param.CH9329_BAUD[2] = CFG_BAUD3;
	g_sys_init_param.ch9329_param.CH9329_BAUD[3] = CFG_BAUD4;

	g_sys_init_param.fp383_param.FPM383_INIT_PARAM_ADDR[0] = (uint32_t)FPM383C_DEFAULT_ADDR>>24;
	g_sys_init_param.fp383_param.FPM383_INIT_PARAM_ADDR[1] = (uint8_t)((uint32_t)FPM383C_DEFAULT_ADDR>>16);
	g_sys_init_param.fp383_param.FPM383_INIT_PARAM_ADDR[2] = (uint8_t)((uint32_t)FPM383C_DEFAULT_ADDR>>8);
	g_sys_init_param.fp383_param.FPM383_INIT_PARAM_ADDR[3] = (uint8_t)FPM383C_DEFAULT_ADDR;
	g_sys_init_param.fp383_param.FPM383_Password[0] = FPM383C_DEFAULT_PASSWORD>>24;
	g_sys_init_param.fp383_param.FPM383_Password[1] = FPM383C_DEFAULT_PASSWORD>>16;
	g_sys_init_param.fp383_param.FPM383_Password[2] = FPM383C_DEFAULT_PASSWORD>>8;
	g_sys_init_param.fp383_param.FPM383_Password[3] = FPM383C_DEFAULT_PASSWORD;
	g_sys_init_param.fp383_param.FPM383_RGB_func = LED_FUNC_BREATHE;
	g_sys_init_param.fp383_param.FPM383_RGB_startColor = LED_COLOR_BLUE;
	g_sys_init_param.fp383_param.FPM383_RGB_stopColor = LED_COLOR_BLUE;
	g_sys_init_param.fp383_param.FPM383_RGB_cycle = 0;
	
	g_sys_init_param.joystick_param.JOYSTICK_INIT_PARAM_DEFAULT_HIGH_THRESHOLD = DEFAULT_HIGH_THRESHOLD;
	g_sys_init_param.joystick_param.JOYSTICK_INIT_PARAM_DEFAULT_LOW_THRESHOLD = DEFAULT_LOW_THRESHOLD;
	g_sys_init_param.joystick_param.JOYSTICK_INIT_PARAM_MAX_OFFSET = MAX_OFFSET;
	g_sys_init_param.joystick_param.JOYSTICK_INIT_PARAM_MIN_OFFSET = MIN_OFFSET;
	
	g_sys_init_param.rgb_param.RGB_INIT_PARAM_R = 0x00;
	g_sys_init_param.rgb_param.RGB_INIT_PARAM_G = 0xFF;
	g_sys_init_param.rgb_param.RGB_INIT_PARAM_B = 0x00;
	g_sys_init_param.rgb_param.RGB_R_decrease = 0;
	g_sys_init_param.rgb_param.RGB_G_decrease = 5;
	g_sys_init_param.rgb_param.RGB_B_decrease = 0;
	g_sys_init_param.rgb_param.RGB_interval = 30;

}

void SYSTEM_Init(void)
{
	MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
	MX_USART3_UART_Init();
	AT24C64_Init();
	MX_DMA_Init();	//dma初始化要在其他使用dma外设之前
	MX_ADC1_Init();
	Flash_Init();
	MX_SPI2_Init();
	delay_init(72);
	FPM383C_Init();
	CH9329_Init();
	//delay_ms(1000);
	ENCODER_Init();
	CRC_Init();
}

void Task_Create(void)
{
	taskENTER_CRITICAL();
	
	Task_Finger_DataCTLCreate();
	Task_Key_DataCTLCreate();
	Task_RGB_ProcessCreate();
	Task_JoyStick_DataCTLCreate();
	Task_Sidebar_CTLCreate();
	Task_Action_KEY_CTLCreate();
	Task_Normal_KEY_CTLCreate();
	Task_Joycon_KEY_CTLCreate();
	Task_Encoder_CTLCreate();
	
	taskEXIT_CRITICAL();
}



















