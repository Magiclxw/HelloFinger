#include "app_task_encoder.h"
#include "drv_ch9329.h"

TaskHandle_t Task_Encoder_Handle = NULL;
TimerHandle_t Sidebar_Timer_Handler;

static void vTaskEncoderProcessing(void);
void Sidebar_TimerCallback(TimerHandle_t xTimer);

int ENCODER_NotifyFromISR(uint32_t dir)	//����������֪ͨ
{
	portBASE_TYPE xHigherPriorityTaskWoken = pdTRUE;
	if(Task_Encoder_Handle != NULL)
	{
		xTaskNotifyFromISR((TaskHandle_t)Task_Encoder_Handle,dir,eSetValueWithOverwrite,&xHigherPriorityTaskWoken);
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	}
	return OPERATE_SUCCESS;
}

int Task_Encoder_CTLCreate(void)	//���������񴴽�
{
	xTaskCreate( (TaskFunction_t)vTaskEncoderProcessing,
								(const char*  )"Encoder",
								(uint32_t     )TASK_ENCODER_CONTROL_SIZE,
								(void *				)NULL,
								(UBaseType_t  )TASK_ENCODER_CONTROL_PRIORITY,
								&Task_Encoder_Handle);
	return OPERATE_SUCCESS;
}

__IO uint8_t timerFlag = 0;

static void vTaskEncoderProcessing(void)
{
	Sidebar_Timer_Handler = xTimerCreate((const char*  )"SidebarTimer",                 /* ��ʱ���� */
                                 (TickType_t    )5000,                      /* ��ʱ����ʱʱ�� */
                                 (UBaseType_t   )pdFALSE,                   /* ���ζ�ʱ�� */
                                 (void*         )1,                         /* ��ʱ��ID */
                                 (TimerCallbackFunction_t)Sidebar_TimerCallback);  /* ��ʱ���ص����� */
	uint32_t encoderState = 0;
	while(1)
	{
		encoderState = ulTaskNotifyTake((BaseType_t)pdTRUE,(TickType_t)portMAX_DELAY);
		if(timerFlag == 0)
		{
			if(encoderState == 0)
			{
				CH9329_REL_Mouse_Ctrl(0x01,0,0,button_NULL);
			}
			else
			{
				CH9329_REL_Mouse_Ctrl(0xFF,0,0,button_NULL);
			}
		}
		else if(timerFlag == 1)	//���������
		{
			if(encoderState == 0)
			{
				CH9329_Input_Fuc_Key(R_ALT|R_SHIFT|R_CTRL,KEY_LeftArrow);
				xTimerReset(Sidebar_Timer_Handler,(TickType_t)portMAX_DELAY);
				xTimerStart((TimerHandle_t  )Sidebar_Timer_Handler,(TickType_t)portMAX_DELAY);
			}
			else
			{
				CH9329_Input_Fuc_Key(R_ALT|R_SHIFT|R_CTRL,KEY_RightArrow);
				xTimerReset(Sidebar_Timer_Handler,(TickType_t)portMAX_DELAY);
				xTimerStart((TimerHandle_t  )Sidebar_Timer_Handler,(TickType_t)portMAX_DELAY);
			}
		}
			
	}
}

void Sidebar_TimerCallback(TimerHandle_t xTimer)
{
	timerFlag = 0;
}
