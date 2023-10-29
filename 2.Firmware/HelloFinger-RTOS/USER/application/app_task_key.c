#include "app_task_key.h"
#include "drv_fpm383.h"
#include "usart.h"
#include "string.h"
#include "..\USER\driver\W25Q128\drv_w25q128.h"
#include "app_task_finger.h"
#include "app_task_rgb.h"


static void vTaskSidebarProcessing(void);
static void vTaskActionKeyProcessing(void);
static void vTaskNormalKeyProcessing(void);
static void vTaskJoyconKeyProcessing(void);
static void Action_Func_Exec(uint8_t func,uint8_t action);


TaskHandle_t Task_Sidebar_Handle = NULL;	//侧边栏控制任务句柄
TaskHandle_t Task_Action_Key_Handle = NULL;	//Action按键功能句柄
TaskHandle_t Task_Normal_Key_Handle = NULL;	//普通按键句柄
TaskHandle_t Task_Joycon_Key_Handle = NULL;	//Joycon按键句柄


int ENCODER_KeyNotifyFromISR(void)	//编码器按键任务通知
{
	portBASE_TYPE xHigherPriorityTaskWoken = pdTRUE;
	if(Task_Sidebar_Handle != NULL)
	{
		vTaskNotifyGiveFromISR((TaskHandle_t)Task_Sidebar_Handle,&xHigherPriorityTaskWoken);
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	}
	return OPERATE_SUCCESS;
}

int Action_KeyNotifyFromISR(void)	//Action按键任务通知
{
	portBASE_TYPE xHigherPriorityTaskWoken = pdTRUE;
	if(Task_Action_Key_Handle != NULL)
	{
		vTaskNotifyGiveFromISR((TaskHandle_t)Task_Action_Key_Handle,&xHigherPriorityTaskWoken);
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	}
	return OPERATE_SUCCESS;
}

int Normal_KeyNotifyFromISR(void)	//普通按键任务通知
{
	portBASE_TYPE xHigherPriorityTaskWoken = pdTRUE;
	if(Task_Normal_Key_Handle != NULL)
	{
		vTaskNotifyGiveFromISR((TaskHandle_t)Task_Normal_Key_Handle,&xHigherPriorityTaskWoken);
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	}
	return OPERATE_SUCCESS;
}

int Joycon_KeyNotifyFromISR(void)	//Joycon按键任务通知
{
	portBASE_TYPE xHigherPriorityTaskWoken = pdTRUE;
	if(Task_Joycon_Key_Handle != NULL)
	{
		vTaskNotifyGiveFromISR((TaskHandle_t)Task_Joycon_Key_Handle,&xHigherPriorityTaskWoken);
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	}
	return OPERATE_SUCCESS;
}

int Task_Sidebar_CTLCreate(void)	//侧边栏控制按键任务创建
{
	xTaskCreate( (TaskFunction_t)vTaskSidebarProcessing,
								(const char*  )"SidebarDataControl",
								(uint32_t     )TASK_SIDEBAR_CONTROL_SIZE,
								(void *				)NULL,
								(UBaseType_t  )TASK_SIDEBAR_CONTROL_PRIORITY,
								&Task_Sidebar_Handle);
	return OPERATE_SUCCESS;
}

int Task_Action_KEY_CTLCreate(void)	//Action功能控制按键任务创建
{
	xTaskCreate( (TaskFunction_t)vTaskActionKeyProcessing,
								(const char*  )"ActionKeyControl",
								(uint32_t     )TASK_ACTION_KEY_SIZE,
								(void *				)NULL,
								(UBaseType_t  )TASK_ACTION_KEY_PRIORITY,
								&Task_Action_Key_Handle);
	return OPERATE_SUCCESS;
}

int Task_Normal_KEY_CTLCreate(void)	//普通按键任务创建
{
	xTaskCreate( (TaskFunction_t)vTaskNormalKeyProcessing,
								(const char*  )"NormalKeyControl",
								(uint32_t     )TASK_NORMAL_KEY_SIZE,
								(void *				)NULL,
								(UBaseType_t  )TASK_NORMAL_KEY_PRIORITY,
								&Task_Normal_Key_Handle);
	return OPERATE_SUCCESS;
}

int Task_Joycon_KEY_CTLCreate(void)	//普通按键任务创建
{
	xTaskCreate( (TaskFunction_t)vTaskJoyconKeyProcessing,
								(const char*  )"JoyconKeyControl",
								(uint32_t     )TASK_JOYCON_KEY_SIZE,
								(void *				)NULL,
								(UBaseType_t  )TASK_JOYCON_KEY_PRIORITY,
								&Task_Joycon_Key_Handle);
	return OPERATE_SUCCESS;
}


static void vTaskSidebarProcessing(void)	//编码器按键任务
{
	char            *task_info_buf  = NULL;
	while(1)
	{
		BaseType_t ret = ulTaskNotifyTake((BaseType_t)pdTRUE,(TickType_t)portMAX_DELAY);
		if(ret != 0)
		{
			vTaskDelay(20);
			if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1))	//消抖
			{
				CH9329_Input_Fuc_Key(R_ALT|R_SHIFT|R_CTRL,KEY_F1);	//输入快捷键，上位机解析为侧边栏控制功能
//				task_info_buf = pvPortMalloc(500);
//				vTaskList(task_info_buf); /* 获取所有任务的信息 */
//				printf("任务名\t\t 状态\t 优先级\t 剩余栈\t 任务序号\r\n");
//				printf("%s\r\n", task_info_buf);
//				vPortFree(task_info_buf);
			}
			vTaskDelay(50);
		}
	}
}

static void vTaskActionKeyProcessing(void)	//Action按键任务
{
	uint8_t func = 0;
	uint8_t action = 0;
	uint32_t crc_value = 0;
	while(1)
	{
		BaseType_t ret = ulTaskNotifyTake((BaseType_t)pdTRUE,(TickType_t)portMAX_DELAY);	
		if(ret != 0)
		{
			vTaskDelay(50);
			if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_14) == 0)	//消抖
			{
				Flash_read(&func,ACTION_FUNC_BASE_ADDR,1);
				Flash_read(&action,ACTION_FUNC_BASE_ADDR+1,1);
				Action_Func_Exec(func,action);
			}
		}
	}
}

static void vTaskJoyconKeyProcessing(void)
{
	while(1)
	{
		BaseType_t ret = ulTaskNotifyTake((BaseType_t)pdTRUE,(TickType_t)portMAX_DELAY);	
		if(ret != 0)
		{
			vTaskDelay(100);
			if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0) == 0)	//消抖
			{
				printf("key 0\r\n");
			}
		}
	}
}

static void vTaskNormalKeyProcessing(void)
{
	uint8_t key1_press_flag = 0;
	uint8_t key2_press_flag = 0;
	
	while(1)
	{
		BaseType_t ret = ulTaskNotifyTake((BaseType_t)pdTRUE,(TickType_t)portMAX_DELAY);
		if(ret != 0)
		{
			vTaskDelay(20);
			if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_8) == GPIO_PIN_RESET)
			{
				CH9329_REL_Mouse_Ctrl(0,0,0,button_LEFT);
				key1_press_flag = 1;
			}
			if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_8) == GPIO_PIN_SET)
			{
				if(key1_press_flag == 1)
				{
					CH9329_REL_Mouse_Ctrl(0,0,0,button_NULL);
					key1_press_flag = 0;
				}
			}
			if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_11) == GPIO_PIN_RESET)
			{
				CH9329_REL_Mouse_Ctrl(0,0,0,button_RIGHT);
				key2_press_flag = 1;
			}
			if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_11) == GPIO_PIN_SET)
			{
				if(key2_press_flag == 1)
				{
					CH9329_REL_Mouse_Ctrl(0,0,0,button_NULL);
					key2_press_flag = 0;
				}
			}
		}
	}
}



static void Action_Func_Exec(uint8_t func,uint8_t action)
{
	switch (func)
	{
		case ACTION_KEY_FUNC_POWER:
		{
			CH9329_Input_Power_Key(action);
			break;
		}
		case ACTION_KEY_FUNC_MEDIA:
		{
			CH9329_Input_Media_Key(action);
			break;
		}
		case ACTION_KEY_FUNC_CHAT:
		{
			CH9329_Input_Fuc_Key(R_ALT|R_SHIFT|R_CTRL,KEY_F2);
		}
	}
}

