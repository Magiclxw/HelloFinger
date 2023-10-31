#include "app_task_rgb.h"
#include "task.h"
#include "sys.h"

extern SYSTEM_INIT_PARAM_t g_sys_init_param;

static void vTaskRGBProcessing(void);
TIM_HandleTypeDef rgb_timer_handler;

TaskHandle_t Task_RGB_Handle = NULL;
QueueHandle_t RGB_Queue_Handle = NULL;
uint8_t gs_temp[288];

int Task_RGB_ProcessCreate(void)
{
	xTaskCreate( (TaskFunction_t)vTaskRGBProcessing,
								(const char*  )"RGBProcess",
								(uint32_t     )TASK_RGB_PROCESS_SIZE,
								(void *				)NULL,
								(UBaseType_t  )TASK_RGB_PROCESS_PRIORITY,
								&Task_RGB_Handle);
	return OPERATE_SUCCESS;
}


static uint32_t gs_rgb[6]; 
	
__IO uint32_t rgb = 0;
__IO float r,g,b;
__IO float r_tmp,g_tmp,b_tmp;
__IO uint8_t dir = 0;
uint32_t rec_rgbi = 0;;

__IO float R_decrease = 0;
__IO float G_decrease = 0;
__IO float B_decrease = 0;
__IO uint8_t interval = 30;

static void vTaskRGBProcessing(void)
{
	R_decrease = g_sys_init_param.rgb_param.RGB_R_decrease;
	G_decrease = g_sys_init_param.rgb_param.RGB_G_decrease;
	B_decrease = g_sys_init_param.rgb_param.RGB_B_decrease;
	
	interval = g_sys_init_param.rgb_param.RGB_interval;
	
	r = g_sys_init_param.rgb_param.RGB_INIT_PARAM_R;                               /* set red */
	g = g_sys_init_param.rgb_param.RGB_INIT_PARAM_G;                                /* set green */
	b = g_sys_init_param.rgb_param.RGB_INIT_PARAM_B; 
	r_tmp = r;
	g_tmp = g;
	b_tmp = b;	/* set blue */
	
	RGB_Queue_Handle = xQueueCreate((UBaseType_t)QUEUE_RGB_PROCESS_LEN,(UBaseType_t)QUEUE_RGB_PROCESS_SIZE);
	//vTaskDelay(500);
	//WS25812B_write(gs_rgb, 6, gs_temp);
	rgb_timer_handler.Instance = TIM2;
	rgb_timer_handler.Init.Prescaler = 719999;
	rgb_timer_handler.Init.Period = interval;
	rgb_timer_handler.Init.CounterMode = TIM_COUNTERMODE_UP;
	HAL_TIM_Base_Init(&rgb_timer_handler);
	HAL_TIM_Base_Start_IT(&rgb_timer_handler);
	while(1)
	{
		BaseType_t ret = xQueueReceive(RGB_Queue_Handle,&rec_rgbi,portMAX_DELAY);
		if(ret == pdTRUE)
		{
			HAL_TIM_Base_Stop_IT(&rgb_timer_handler);
			r = rec_rgbi>>24;
			g = (rec_rgbi>>16)&0xFF;
			b = (rec_rgbi>>8)&0xFF;
			//if((r == 0) && (g == 0) && (b == 0))	//关闭rgb
			//{
			//	dir = 0;
			//	//WS2812B_Write_Only_Reset(gs_temp,0);
			//	continue;
			//}
			r_tmp = r;
			g_tmp = g;
			b_tmp = b;
			interval = (uint8_t)rec_rgbi;
			if(interval < 10) interval = 30;
			R_decrease = r_tmp/40;
			G_decrease = g_tmp/40;
			B_decrease = b_tmp/40;
			//TIM2->ARR = interval;
			rgb_timer_handler.Init.Period = interval;
			HAL_TIM_Base_Init(&rgb_timer_handler);
			HAL_TIM_Base_Start_IT(&rgb_timer_handler);
			//printf("R_decrease = %f,G_decrease = %f,B_decrease = %f\r\n",R_decrease,G_decrease,B_decrease);
		}
	}
}

portBASE_TYPE xHigherPriorityTaskWoken = pdTRUE;

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
	if(hspi->Instance == SPI2)
	{
		if(FingerEvent_Handle != NULL)
		{
			
		}
	}
}

void RGB_Effect(uint8_t r,uint8_t g,uint8_t b,uint16_t delay,uint8_t times)	//RGB灯效，用于表示操作执行结果
{
	uint32_t rgb = 0;
	
	HAL_TIM_Base_Stop_IT(&rgb_timer_handler);
	
	for(uint8_t i=0;i<times;i++)
	{
		rgb = ((uint32_t)(r) << 16) | ((uint32_t)(g) << 8) | (uint8_t)b;
		for (uint8_t i = 0; i < 6; i++)
		{
			gs_rgb[i] = rgb;
		}
		
		WS25812B_write(gs_rgb, 6, gs_temp);
		
		vTaskDelay(delay);
		rgb = 0;
		for (uint8_t i = 0; i < 6; i++)
		{
			gs_rgb[i] = rgb;
		}
		WS25812B_write(gs_rgb, 6, gs_temp);
		vTaskDelay(delay);
	}
	HAL_TIM_Base_Start_IT(&rgb_timer_handler);
}

void Display_Result(uint8_t result)
{
	switch (result)
	{
		case RESULT_SUCCESS:
		{
			RGB_Effect(0,255,0,200,2);
			break;
		}
		case RESULT_FAILED:
		{
			RGB_Effect(255,0,0,200,2);
		}
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(dir == 0)
			{
				r -= R_decrease;
				g -= G_decrease;
				b -= B_decrease;
				if(r < R_decrease || g < G_decrease || b < B_decrease)
				{
					dir = 1;
					r = 0;
					g = 0;
					b = 0;
				}
				//printf("0:r = %f,g = %f,b = %f\r\n",r,g,b);

			}
			else if(dir == 1)
			{
				r += R_decrease;
				g += G_decrease;
				b += B_decrease;
				if(r > r_tmp-R_decrease || g > g_tmp-G_decrease || b > b_tmp-B_decrease)
				{
					dir = 0;
					r = r_tmp;
					g = g_tmp;
					b = b_tmp;
				}
				//printf("1:r = %f,g = %f,b = %f\r\n",r,g,b);
			}

			rgb = ((uint32_t)(r) << 16) | ((uint32_t)(g) << 8) | (uint8_t)b;
			
			for (uint8_t i = 0; i < 6; i++)
			{
				gs_rgb[i] = rgb;//0xE0;
			}
			
			WS25812B_write(gs_rgb, 6, gs_temp);
}
