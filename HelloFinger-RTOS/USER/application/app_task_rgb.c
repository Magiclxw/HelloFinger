#include "app_task_rgb.h"
#include "task.h"

static void vTaskRGBProcessing(void);

TaskHandle_t Task_RGB_Handle = NULL;
EventGroupHandle_t RGB_Event_Handle	= NULL;

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
	__IO uint32_t rgb;
	__IO uint8_t r,g,b;
	__IO uint8_t dir = 0;
	r = 0x00;                               /* set red */
	g = 0x00;                                /* set green */
	b = 0xFF;                                /* set blue */
	__IO uint32_t event_status = 0;
	RGB_Event_Handle = xEventGroupCreate();
	vTaskDelay(500);
	WS25812B_write(gs_rgb, 6, gs_temp);
	
	while(1)
	{
		event_status = xEventGroupGetBits(RGB_Event_Handle);
		//if(event_status & EVENT_RGB_TRANS_OVER)
		{
			//taskENTER_CRITICAL();
			rgb = ((uint32_t)(r) << 16) | ((uint32_t)(g) << 8) | b;
			
			for (uint8_t i = 0; i < 6; i++)
			{
				gs_rgb[i] = rgb;//0xE0;
			}
			/* write data */
			
			if(dir == 0)
			{
				//r-=5;
				b-=5;
				//g-=5;
			}
			if(dir == 1)
			{
				//r+=5;
				b+=5;
				//g+=5;
			}
			
			if(b == 0)
			{
				dir = 1;
			}
			if(b == 255)
			{
				dir = 0;
			}
			WS25812B_write(gs_rgb, 6, gs_temp);
			//memset(gs_temp,0,288);
			xEventGroupClearBits(RGB_Event_Handle,(EventBits_t)EVENT_RGB_TRANS_OVER);
			//taskEXIT_CRITICAL();
		}
		
		vTaskDelay(30);
	}
}

portBASE_TYPE xHigherPriorityTaskWoken = pdTRUE;

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
	if(hspi->Instance == SPI2)
	{
		if(FingerEvent_Handle != NULL)
		{
			xEventGroupSetBitsFromISR((EventGroupHandle_t)RGB_Event_Handle,(EventBits_t)EVENT_RGB_TRANS_OVER,&xHigherPriorityTaskWoken);
			portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
		}
	}
}
