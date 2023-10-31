#include "app_task_encoder.h"
#include "drv_ch9329.h"

static void vTaskEncoderProcessing(void);

TaskHandle_t Task_Encoder_Handle = NULL;

int ENCODER_NotifyFromISR(uint32_t dir)	//编码器任务通知
{
	portBASE_TYPE xHigherPriorityTaskWoken = pdTRUE;
	if(Task_Encoder_Handle != NULL)
	{
		xTaskNotifyFromISR((TaskHandle_t)Task_Encoder_Handle,dir,eSetValueWithOverwrite,&xHigherPriorityTaskWoken);
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	}
	return OPERATE_SUCCESS;
}

int Task_Encoder_CTLCreate(void)	//编码器任务创建
{
	xTaskCreate( (TaskFunction_t)vTaskEncoderProcessing,
								(const char*  )"Encoder",
								(uint32_t     )TASK_ENCODER_CONTROL_SIZE,
								(void *				)NULL,
								(UBaseType_t  )TASK_ENCODER_CONTROL_PRIORITY,
								&Task_Encoder_Handle);
	return OPERATE_SUCCESS;
}

static void vTaskEncoderProcessing(void)
{
	uint32_t encoderState = 0;
	while(1)
	{
		encoderState = ulTaskNotifyTake((BaseType_t)pdTRUE,(TickType_t)portMAX_DELAY);
		if(encoderState == 0)
		{
			CH9329_REL_Mouse_Ctrl(0x01,0,0,button_NULL);
		}
		else
		{
			CH9329_REL_Mouse_Ctrl(0xFF,0,0,button_NULL);
		}
	}
}
