#include "app_task_rgb.h"
#include "task.h"

static void vTaskRGBProcessing(void);

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




static void vTaskRGBProcessing(void)
{
	static uint32_t gs_rgb[6]; 
	//static uint8_t gs_temp[1024];
	uint32_t rgb = 0;
	__IO uint8_t r,g,b;
	__IO uint8_t r_tmp,g_tmp,b_tmp;
	__IO uint8_t dir = 0;
	uint32_t rec_rgbi = 0;;
	r = 0x00;                               /* set red */
	g = 0x00;                                /* set green */
	b = 0xFF; 
	r_tmp = r;
	g_tmp = g;
	b_tmp = b;	/* set blue */
	uint8_t R_decrease = 0;
	uint8_t G_decrease = 0;
	uint8_t B_decrease = 5;
	uint8_t interval = 0;
	
	RGB_Queue_Handle = xQueueCreate((UBaseType_t)QUEUE_RGB_PROCESS_LEN,(UBaseType_t)QUEUE_RGB_PROCESS_SIZE);
	vTaskDelay(500);
	WS25812B_write(gs_rgb, 6, gs_temp);
	
	while(1)
	{
		BaseType_t ret = xQueueReceive(RGB_Queue_Handle,&rec_rgbi,30);
		if(ret == pdTRUE)
		{
			r = rec_rgbi>>24;
			g = rec_rgbi>>16;
			b = rec_rgbi>>8;
			r_tmp = r;
			g_tmp = g;
			b_tmp = b;
			interval = (uint8_t)rec_rgbi;
			R_decrease = r_tmp/interval;
			G_decrease = g_tmp/interval;
			B_decrease = b_tmp/interval;
		}

		rgb = ((uint32_t)(r) << 16) | ((uint32_t)(g) << 8) | b;
			
			for (uint8_t i = 0; i < 6; i++)
			{
				gs_rgb[i] = rgb;//0xE0;
			}
			/* write data */
			
			if(dir == 0)
			{
				r -= R_decrease;
				g -= G_decrease;
				b -= B_decrease;
				if(r < R_decrease || g < G_decrease || b < B_decrease)
				{
					dir = 1;
				}
			}
			if(dir == 1)
			{
				r += R_decrease;
				g += G_decrease;
				b += B_decrease;
				if(r > r_tmp-R_decrease || g > g_tmp-G_decrease || b > b_tmp-B_decrease)
				{
					dir = 0;
				}
			}
			
			
			
			WS25812B_write(gs_rgb, 6, gs_temp);
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
