#include "app_task_rgb.h"
#include "task.h"

static void vTaskRGBProcessing(void);

TaskHandle_t Task_RGB_Handle = NULL;


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
	static uint8_t gs_temp[1024];
	__IO uint32_t rgb;
	__IO uint8_t r,g,b;
	r = 0x00;                               /* set red */
	g = 0x00;                                /* set green */
	b = 0xFF;                                /* set blue */
	__IO uint8_t dir = 0;
	while(1)
	{
		rgb = ((uint32_t)(r) << 16) | ((uint32_t)(g) << 8) | b;

		for (uint8_t i = 0; i < 6; i++)
		{
			gs_rgb[i] = rgb;//0xE0;
		}
		/* write data */
		WS25812B_write(gs_rgb, 6, gs_temp);
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

		memset(gs_temp,0,(sizeof(uint8_t)*1024));
		vTaskDelay(100);
	}
}