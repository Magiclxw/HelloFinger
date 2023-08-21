#include "app_task_joystick.h"
#include "drv_ch9329.h"

static void vTaskJoyStickProcessing(void);	//指纹接收数据处理任务

TaskHandle_t Task_JOYSTICK_Handle = NULL;
QueueHandle_t Queue_JOYSTICKProcessing_Handle = NULL;

int JoyStick_GiveNotifyFromISR(uint8_t *recData,uint8_t dataSize)
{
	portBASE_TYPE xHigherPriorityTaskWoken = pdTRUE;
	if(Queue_JOYSTICKProcessing_Handle != NULL)
	{
		xQueueSendFromISR(Queue_JOYSTICKProcessing_Handle,recData,&xHigherPriorityTaskWoken);
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	}
	return OPERATE_SUCCESS;
}

int Task_JoyStick_DataCTLCreate(void)
{
	xTaskCreate((TaskFunction_t) vTaskJoyStickProcessing,
							(const char *	)	 "JoyStickTask",
							(uint32_t)TASK_JOYSTICK_CONTROL_SIZE,
							(void*) NULL,
							(UBaseType_t)TASK_JOYSTICK_CONTROL_PRIORITY,
							&Task_JOYSTICK_Handle);
	return OPERATE_SUCCESS;
}

void vTaskJoyStickProcessing(void)
{
	uint8_t offset_XY[2] = {0};
	uint8_t move_dist_x_y[2] = {0};
	Queue_JOYSTICKProcessing_Handle = xQueueCreate((UBaseType_t)QUEUE_JOYSTICK_LEN,(UBaseType_t)QUEUE_JOYSTICK_SIZE);
	//BaseType_t xHigherPriorityTaskWoken = pdTRUE;
	HAL_ADC_Start_DMA(&hadc1,(uint32_t*)&value_X_Y,(uint32_t)2);
	while(1)
	{
		//BaseType_t rec = xQueueReceiveFromISR(Queue_JOYSTICKProcessing_Handle,&move_dist_x_y,&xHigherPriorityTaskWoken);
		//portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
		BaseType_t ret = xQueueReceive(Queue_JOYSTICKProcessing_Handle,&offset_XY,portMAX_DELAY);
		//printf("x=%d,y=%d\r\n",offset_XY[0],offset_XY[1]);
		//REL_Mouse_Ctrl(0,move_dist_x_y[0],move_dist_x_y[1],button_NULL);
		taskENTER_CRITICAL();
		if(offset_XY[1] < MIN_OFFSET){
			move_dist_x_y[1] = (MIN_OFFSET - offset_XY[1])*1;
		}
		if(offset_XY[1] > MAX_OFFSET){
			move_dist_x_y[1] = 0xFF - ((offset_XY[1] - MAX_OFFSET)*1);
		}
		if(offset_XY[0] < MIN_OFFSET){
			move_dist_x_y[0] = (MIN_OFFSET - offset_XY[0])*1;
		}
		if(offset_XY[0] > MAX_OFFSET){
			move_dist_x_y[0] = 0xFF - ((offset_XY[0] - MAX_OFFSET)*1);
		}
		if(move_dist_x_y[0] != 0 | move_dist_x_y[1] != 0){
			printf("x=%d,y=%d\r\n",offset_XY[0],offset_XY[1]);
			REL_Mouse_Ctrl(0,move_dist_x_y[0],move_dist_x_y[1],button_NULL);
			memset(move_dist_x_y,0,2);
			memset(offset_XY,0,2);
		}
		taskEXIT_CRITICAL();
		vTaskDelay(30);
		HAL_ADC_Start_DMA(&hadc1,(uint32_t*)&value_X_Y,(uint32_t)2);
	}
}

