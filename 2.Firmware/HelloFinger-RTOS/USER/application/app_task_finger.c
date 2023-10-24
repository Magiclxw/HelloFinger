#include "app_task_finger.h"
#include "usart.h"
#include "sys_config.h"
#include "drv_ch9329.h"
#include "app_task_key.h"
#include "..\USER\driver\W25Q128\drv_w25q128.h"
#include "app_task_rgb.h"

static void vTaskFingerProcessing(void);	//指纹接收数据处理任务
static void FingerResetData(void);	//复位接受结构体
static int CMP_Checksum(uint8_t *data,uint8_t len);
static int Finger_Func_Quick_Start(char key);
int Finger_RecData_Handle(uint8_t data);
static void Finger_Func_Exec(void);
static void Finger_Key_Function(uint16_t id,uint16_t score);

TaskHandle_t Task_Finger_Handle = NULL;
TaskHandle_t Task_Finger_Rec_Handle = NULL;
QueueHandle_t Queue_FingerProcessing_Handle = NULL;
EventGroupHandle_t FingerEvent_Handle	= NULL;		//指纹时间标志组，用于指令发送、接收间的同步

FINGER_DATA_CONTROLLR_t g_finger_data_ctl = {0};
FINGER_DATA_FORMAT_t g_data_format = {0};

USB_RESPONSE_t g_usb_response = {0};

int Finger_GiveNotifyFromISR(uint8_t *recData,uint8_t dataSize)
{
	portBASE_TYPE xHigherPriorityTaskWoken = pdTRUE;
	if(Queue_FingerProcessing_Handle != NULL)
	{
		xQueueSendFromISR(Queue_FingerProcessing_Handle,recData,&xHigherPriorityTaskWoken);
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	}
	return OPERATE_SUCCESS;
}

int Finger_TouchNotifyFromISR(void)
{
	CMD_AutoIdentify_t 			g_autoidentify 			= {0};	//自动验证指纹结构体
	Generate_AutoIdentify(&g_autoidentify,0x03,0xFFFF,0x0007);
	HAL_UART_Transmit(&FINGER_HANDLE,(uint8_t*)&g_autoidentify,g_autoidentify.LEN[0]<<8|g_autoidentify.LEN[1]+9,1000);
	portBASE_TYPE xHigherPriorityTaskWoken = pdTRUE;
	if(FingerEvent_Handle != NULL)
	{
		xEventGroupSetBitsFromISR((EventGroupHandle_t)FingerEvent_Handle,(EventBits_t)EVENT_TOUCH_DETECT,&xHigherPriorityTaskWoken);
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	}
	return OPERATE_SUCCESS;
}

int Task_Finger_DataCTLCreate(void)
{
	xTaskCreate( (TaskFunction_t)vTaskFingerProcessing,
								(const char*  )"FingerDataControl",
								(uint32_t     )TASK_FINGER_CONTROL_SIZE,
								(void *				)NULL,
								(UBaseType_t  )TASK_FINGER_CONTROL_PRIORITY,
								&Task_Finger_Handle);
	return OPERATE_SUCCESS;
}

static void vTaskFingerProcessing(void)
{
	uint8_t rec_data = 0 ;
	CMD_Sleep_t							g_sleep							= {0};	//休眠指令结构体
	
	FingerResetData();
	Queue_FingerProcessing_Handle = xQueueCreate((UBaseType_t)FINGER_DATA_HANDLE_QUEUE_LEN,(UBaseType_t)FINGER_DATA_HANDLE_QUEUE_SIZE);
	FingerEvent_Handle = xEventGroupCreate();	//初始化事件标志组
	while(1)
	{
		BaseType_t ret = xQueueReceive(Queue_FingerProcessing_Handle,&rec_data,2000);
		if(ret == pdTRUE)
		{
			Finger_RecData_Handle(rec_data);
		}
		else
		{
			FingerResetData();
			if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4) == GPIO_PIN_SET)
			{
				Generate_Sleep(&g_sleep);
				HAL_UART_Transmit(&FINGER_HANDLE,(uint8_t*)&g_sleep,g_sleep.LEN[0]<<8|g_sleep.LEN[1]+FIXED_CMD_LEN,1000);
			}
		}
		
					
	}
}

static void FingerResetData(void)
{
	memset(&g_finger_data_ctl,0,sizeof(FINGER_DATA_CONTROLLR_t));
	g_finger_data_ctl.pData = (uint8_t *)&g_data_format;
}

int Finger_RecData_Handle(uint8_t data)
{
	if(g_finger_data_ctl.head_state_H == DATA_RECV_STATE_NO_GET)
	{
		if(data == FINGER_CMD_HEAD_H)
		{
			g_finger_data_ctl.head_state_H = DATA_RECV_STATE_GET;
			*g_finger_data_ctl.pData = data;
			g_finger_data_ctl.pData++;
			g_finger_data_ctl.rec_data_size++;
		}
		else
		{
			FingerResetData();
		}
	}
	else
	{
		if(g_finger_data_ctl.head_state_L == DATA_RECV_STATE_NO_GET)
		{
			if(data == FINGER_CMD_HEAD_L)
			{
				g_finger_data_ctl.head_state_L = DATA_RECV_STATE_GET;
				*g_finger_data_ctl.pData = data;
				g_finger_data_ctl.pData++;
				g_finger_data_ctl.rec_data_size++;
			}
			else
			{
				FingerResetData();
			}
		}
		else
		{
			if(g_finger_data_ctl.addr_state_1 == DATA_RECV_STATE_NO_GET)
			{
				if(data == FINGER_CMD_ADDR_1)
				{
					g_finger_data_ctl.addr_state_1 = DATA_RECV_STATE_GET;
					*g_finger_data_ctl.pData = data;
					g_finger_data_ctl.pData++;
					g_finger_data_ctl.rec_data_size++;
				}
				else
				{
					FingerResetData();
				}
			}
			else
			{
				if(g_finger_data_ctl.addr_state_2 == DATA_RECV_STATE_NO_GET)
				{
					if(data == FINGER_CMD_ADDR_2)
					{
						g_finger_data_ctl.addr_state_2 = DATA_RECV_STATE_GET;
						*g_finger_data_ctl.pData = data;
						g_finger_data_ctl.pData++;
						g_finger_data_ctl.rec_data_size++;
					}
					else
					{
						FingerResetData();
					}
				}
				else
				{
					if(g_finger_data_ctl.addr_state_3 == DATA_RECV_STATE_NO_GET)
					{
						if(data == FINGER_CMD_ADDR_3)
						{
							g_finger_data_ctl.addr_state_3 = DATA_RECV_STATE_GET;
							*g_finger_data_ctl.pData = data;
							g_finger_data_ctl.pData++;
							g_finger_data_ctl.rec_data_size++;
						}
						else
						{
							FingerResetData();
						}
					}
					else
					{
						if(g_finger_data_ctl.addr_state_4 == DATA_RECV_STATE_NO_GET)
						{
							if(data == FINGER_CMD_ADDR_4)
							{
								g_finger_data_ctl.addr_state_4 = DATA_RECV_STATE_GET;
								*g_finger_data_ctl.pData = data;
								g_finger_data_ctl.pData++;
								g_finger_data_ctl.rec_data_size++;
							}
							else
							{
								FingerResetData();
							}
						}
						else
						{
							if(g_finger_data_ctl.rec_data_size < 9)
							{
								*g_finger_data_ctl.pData = data;
								g_finger_data_ctl.pData++;
								g_finger_data_ctl.rec_data_size++;
							}
							else if(g_finger_data_ctl.rec_data_size == 9)
							{
								g_finger_data_ctl.data_state = DATA_RECV_STATE_GET;
								g_finger_data_ctl.data_length = g_data_format.len[0]<<8|g_data_format.len[1];
								g_finger_data_ctl.rec_data_size++;
							}
							if(g_finger_data_ctl.data_state == DATA_RECV_STATE_GET)
							{
								if(g_finger_data_ctl.data_length-1)
								{
									g_finger_data_ctl.data_length--;
									*g_finger_data_ctl.pData = data;
									g_finger_data_ctl.pData++;
								}
								else
								{
									*g_finger_data_ctl.pData = data;
									int result = CMP_Checksum((uint8_t*)&g_data_format.type,(g_data_format.len[0]<<8|g_data_format.len[1])+1);	//校验和是从包标识至校验和之间所有字节之和，包含包标识不包含校验和
									if(result == OPERATE_SUCCESS)
									{
										Finger_Func_Exec();
										FingerResetData();
									}
									else
									{
										FingerResetData();
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return OPERATE_SUCCESS;
}


static int CMP_Checksum(uint8_t *data,uint8_t len)		//比较校验和
{
	uint16_t checksum = 0;
	
	for(uint8_t i=0; i<len; i++){
		checksum += data[i];
	}
	if(checksum == (data[len]<<8|data[len+1]))
	{
		return OPERATE_SUCCESS;
	}
	else
	{
		return OPERATE_ERROR_INVALID_PARAMETERS;
	}
}

static void Finger_Func_Exec(void)
{
	static EventBits_t event_status = 0;
	switch (g_data_format.type)
	{
		case ID_CMD:	//命令包
		{
			break;
		}
		case ID_DATA1:
		{
			break;
		}
		case ID_DATA2:
		{
			break;
		}
		case ID_RESP:
		{
			switch(g_data_format.data[0])	//判断确认码
			{
				
				case CONFIRM_OK:
				{
					event_status = xEventGroupGetBits(FingerEvent_Handle);
					//event_status = xEventGroupWaitBits(FingerEvent_Handle,EVENT_INDEX_LIST,pdTRUE,pdFALSE,100);
					if(event_status & EVENT_INDEX_LIST)	//已发送读取索引表指令，当前返回的是索引表信息
					{
						g_usb_response.head = USB_RESPONSE_HEAD;
						g_usb_response.len = 34;
						g_usb_response.type = USB_PROTOCOL_FORMAT_GET_INDEX_LIST;
						g_usb_response.result = CONFIRM_OK;
						memcpy((uint8_t*)&g_usb_response.data,(uint8_t*)&g_data_format.data[1],32);
						g_usb_response.data[32] = CH9329_CAL_SUM((uint8_t*)&g_usb_response,36);
						CH9329_Send_HID_Data((uint8_t*)&g_usb_response,37);
						xEventGroupClearBits(FingerEvent_Handle,EVENT_INDEX_LIST);
					}
					//event_status = xEventGroupWaitBits(FingerEvent_Handle,EVENT_AUTO_ENROLL,pdFALSE,pdFALSE,100);
					if(event_status & EVENT_AUTO_ENROLL)
					{
						g_usb_response.head = USB_RESPONSE_HEAD;
						g_usb_response.len = 4;
						g_usb_response.type = USB_PROTOCOL_FORMAT_ENROLL_FINGER;
						g_usb_response.result = CONFIRM_OK;
						g_usb_response.data[0] = g_data_format.data[1];	//参数1
						g_usb_response.data[1] = g_data_format.data[2];	//参数2
						g_usb_response.data[2] = CH9329_CAL_SUM((uint8_t*)&g_usb_response,6);

						if(g_usb_response.data[0] == 0x01 || g_usb_response.data[0] == 0x02 ||g_usb_response.data[0] == 0x03)	//重新按下手指
						{
							CH9329_Send_HID_Data((uint8_t*)&g_usb_response,7);
						}
						if(g_usb_response.data[0] == 0x06 && g_usb_response.data[1] == 0xF2)	//流程结束,置位标志
						{
							CH9329_Send_HID_Data((uint8_t*)&g_usb_response,7);
							xEventGroupClearBits(FingerEvent_Handle,EVENT_AUTO_ENROLL);
							/* 指纹注册成功后重新获取索引表信息发送给上位机 */
							xEventGroupSetBits(FingerEvent_Handle,EVENT_INDEX_LIST);
							CMD_ReadIndexTable_t	 	g_read_index_table 	= {0};	//读索引表结构体
							Generate_ReadIndexTable(&g_read_index_table,0);
							HAL_UART_Transmit(&FINGER_HANDLE,(uint8_t*)&g_read_index_table,g_read_index_table.LEN[0]<<8|g_read_index_table.LEN[1]+FIXED_CMD_LEN,1000);
						}
					}
					if(event_status & EVENT_DELETE_CHAR)
					{
						g_usb_response.head = USB_RESPONSE_HEAD;
						g_usb_response.len = 2;
						g_usb_response.type = USB_PROTOCOL_FORMAT_DELETE_FINGER;
						g_usb_response.result = CONFIRM_OK;
						g_usb_response.data[0] = CH9329_CAL_SUM((uint8_t*)&g_usb_response,4);
						CH9329_Send_HID_Data((uint8_t*)&g_usb_response,5);           
						xEventGroupClearBits(FingerEvent_Handle,EVENT_DELETE_CHAR);
						/* 删除指纹完成后重新获取索引表信息发送给上位机 */
						xEventGroupSetBits(FingerEvent_Handle,EVENT_INDEX_LIST);
						CMD_ReadIndexTable_t	 	g_read_index_table 	= {0};	//读索引表结构体
						Generate_ReadIndexTable(&g_read_index_table,0);
						HAL_UART_Transmit(&FINGER_HANDLE,(uint8_t*)&g_read_index_table,g_read_index_table.LEN[0]<<8|g_read_index_table.LEN[1]+FIXED_CMD_LEN,1000);
					}
					if(event_status & EVENT_TOUCH_DETECT)	//指纹验证结果
					{
						if(g_data_format.data[1] == 0x05)
						{
							uint16_t id = g_data_format.data[2]<<8|g_data_format.data[3];
							uint16_t score = g_data_format.data[4]<<8|g_data_format.data[5];
							if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_13) == GPIO_PIN_SET)
							{
								Finger_Function(id,score);	//指纹匹配
							}
							else
							{
								Finger_Key_Function(id,score);	//指纹匹配且按键按下
							}
							
						}
						CMD_Sleep_t							g_sleep							= {0};	//休眠指令结构体
						Generate_Sleep(&g_sleep);
						HAL_UART_Transmit(&FINGER_HANDLE,(uint8_t*)&g_sleep,g_sleep.LEN[0]<<8|g_sleep.LEN[1]+FIXED_CMD_LEN,1000);
						
						xEventGroupClearBits(FingerEvent_Handle,EVENT_TOUCH_DETECT);
					}
					break;
				}
				case CONFIRM_REC_ERROR:
				{
					
					break;
				}
				case CONFIRM_NO_FINGER:
				{
					break;
				}
				case CONFIRM_RECORD_FAIL:
				{
					break;
				}
				case CONFIRM_IMAGE_DRY_LIGHT:
				{
					break;
				}
				case CONFIRM_IMAGE_WET_BREEZING:
				{
					break;
				}
				case CONFIRM_IMAGE_MESS:
				{
					break;
				}
				case CONFIRM_IMAGE_LACK:
				{
					break;
				}
				case CONFIRM_FINGER_MISS_MATCH:
				{
					break;
				}
				case CONFIRM_FINGER_SEARCH_FAIL:	//没有搜索到指纹	
				{
					CMD_Sleep_t							g_sleep							= {0};	//休眠指令结构体
					//if(event_status & EVENT_TOUCH_DETECT)	//指纹验证结果
					//{
						Generate_Sleep(&g_sleep);
						
						HAL_UART_Transmit(&FINGER_HANDLE,(uint8_t*)&g_sleep,g_sleep.LEN[0]<<8|g_sleep.LEN[1]+FIXED_CMD_LEN,1000);
						
						xEventGroupClearBits(FingerEvent_Handle,EVENT_TOUCH_DETECT);
					//}
					break;
				}
				case CONFIRM_FEATURE_MATCH_FAIL:
				{
					break;
				}
				case CONFIRM_ADDRESS_ERROR:
				{
					break;
				}
				case CONFIRM_LIBRARY_READ_ERROR:
				{
					break;
				}
				case CONFIRM_FEATURE_UPLOAD_ERROR:
				{
					break;
				}
				case CONFIRM_REFUSE_FOLLOW_DATA:
				{
					break;
				}
				case CONFIRM_IMAGE_UPLOAD_FAIL:
				{
					break;
				}
				case CONFIRM_TEMPLATE_DELETE_FAIL:
				{
					break;
				}
				case CONFIRM_CLEAR_LIBRARY_FAIL:
				{
					break;
				}
				case CONFIRM_ENTER_LOW_POWER_MODE_FAIL:
				{
					break;
				}
				case CONFIRM_CMD_ERROR:
				{
					break;
				}
				case CONFIRM_RESET_ERROR:
				{
					break;
				}
				case CONFIRM_GENERATE_IMAGE_ERROR:
				{
					break;
				}
				case CONFIRM_UPDATE_ERROR:
				{
					break;
				}
				case CONFIRM_FINGER_NO_REPLACE:
				{
					break;
				}
				case CONFIRM_FLASH_ERROR:
				{
					break;
				}
				case CONFIRM_RANDOM_NUMBER_GENERATE_FAIL:
				{
					break;
				}
				case CONFIRM_INVALID_REG_NUMBER:
				{
					break;
				}
				case CONFIRM_REG_CONTENT_ERROR:
				{
					break;
				}
				case CONFIRM_NOTEBOOK_PAGE_ERROR:
				{
					break;
				}
				case CONFIRM_PORT_ERROR:
				{
					break;
				}
				case CONFIRM_AUTO_ENROLL_FAIL:
				{
					break;
				}
				case CONFIRM_LIBRARY_FULL:
				{
					break;
				}
				case CONFIRM_ADDR_ERROR:
				{
					break;
				}
				case CONFIRM_PASSWORD_ERROR:
				{
					break;
				}
				case CONFIRM_TEMPLATE_NOT_EMPTY:
				{
					break;
				}
				case CONFIRM_TEMPLATE_EMPTY:
				{
					break;
				}
				case CONFIRM_LIBRARY_EMPTY:
				{
					//Generate_Sleep();
					//HAL_UART_Transmit(&FINGER_HANDLE,(uint8_t*)&g_sleep,g_sleep.LEN[0]<<8|g_sleep.LEN[1]+FIXED_CMD_LEN,1000);
					break;
				}
				case CONFIRM_ENROLL_TIMES_ERROR:
				{
					break;
				}
				case CONFIRM_TIMEOUT:
				{
					//Generate_Cancel();
					//HAL_UART_Transmit(&FINGER_HANDLE,(uint8_t*)&g_cancel,g_cancel.LEN[0]<<8|g_cancel.LEN[1]+FIXED_CMD_LEN,1000);
					break;
				}
				case CONFIRM_FINGER_EXIST:
				{
					break;
				}
				case CONFIRM_FINGER_FERTURE_RELATED:
				{
					break;
				}
				case CONFIRM_SENSOR_INIT_FAIL:
				{
					break;
				}
				case CONFIRM_DEV_INFO_NOT_EMPTY:
				{
					break;
				}
				case CONFIRM_DEV_INFO_EMPTY:
				{
					break;
				}
				case CONFIRM_OPT_FAIL:
				{
					break;
				}
				case CONFIRM_PRIV_KEY_GENERATE_FAIL:
				{
					break;
				}
				case CONFIRM_PRIV_KEY_NOT_EXIST:
				{
					break;
				}
				case CONFIRM_SAFE_ALG_EXE_FAIL:
				{
					break;
				}
				case CONFIRM_SAFE_ALG_RESULT_ERROR:
				{
					break;
				}
				case CONFIRM_FUNC_SECURE_NOT_MATCH:
				{
					break;
				}
				case CONFIRM_PRIV_KEY_LOCK:
				{
					break;
				}
				case CONFIRM_IMAGE_SMALL:
				{
					break;
				}
				default : break;
			}
			break;
		}
		default : break;
	}
	//Generate_Sleep();
	//HAL_UART_Transmit(&FINGER_HANDLE,(uint8_t*)&g_sleep,g_sleep.LEN[0]<<8|g_sleep.LEN[1]+FIXED_CMD_LEN,1000);
}
/**
* @brief		指纹验证通过后执行对应的操作
* @param		- id 验证成功的指纹序号
* @param		- score 验证成功的指纹得分
* @date			2023-10-16 22:22:26
* @return 	NULL
* @note
*/
static void Finger_Function(uint16_t id,uint16_t score)
{
	uint8_t func_type = 0;
	Flash_read(&func_type,FINGER_FUNC_BASE_ADDR+id*FINGER_FUNC_BASE_SIZE,1);	//读取功能类型
	switch (func_type)
	{
		case TYPE_Windows_Password:	//解锁
		{
			uint8_t len = 0;
			uint32_t crc_value = 0;
			uint32_t rec_crc = 0;
			Flash_read(&len,FINGER_FUNC_BASE_ADDR+id*FINGER_FUNC_BASE_SIZE+FINGER_FUNC_LEN1_OFFSET,1);
			if(len == 0) break;
			uint8_t *password = (uint8_t*)pvPortMalloc(len+3);
			Flash_read(password,FINGER_FUNC_BASE_ADDR+id*FINGER_FUNC_BASE_SIZE,len+3);
			crc_value = Calc_CRC(password,len+3);
			printf("crc_value = %d\r\n",crc_value);
			vTaskDelay(10);
			Flash_read((uint8_t *)&rec_crc,FINGER_FUNC_BASE_ADDR+id*FINGER_FUNC_BASE_SIZE+len+3,4);
			printf("rec_crc = %d",rec_crc);
			if(rec_crc == crc_value)		//crc校验通过
			{
				
				uint8_t led_status = 0;
				CH9329_Get_Info();
				xQueueReceive(Queue_Computer_Info_Handle,&led_status,200);
				if(led_status & LED_STATE_CAPS_LOCK)	//当前是大写状态
				{
					CH9329_Input_Fuc_Key(NO_CTRL,KEY_CapsLock);
				}
				CH9329_Input_Fuc_Key(NO_CTRL,KEY_LeftCtrl);
				vTaskDelay(400);
				CH9329_Keyboard_Switch();	//系统键盘切换
				CH9329_Input_Ascii((char*)&password[3],len);
				CH9329_Input_Fuc_Key(NO_CTRL,KEY_LeftEnter);
				CH9329_Keyboard_Switch();
				if(led_status & LED_STATE_CAPS_LOCK)
				{
					CH9329_Input_Fuc_Key(NO_CTRL,KEY_CapsLock);
				}
			}
			vPortFree(password);
			break;
		}
		case TYPE_Password:			//密码
		{
			uint8_t len = 0;
			uint32_t crc_value = 0;
			uint32_t rec_crc = 0;
			Flash_read(&len,FINGER_FUNC_BASE_ADDR+id*FINGER_FUNC_BASE_SIZE+FINGER_FUNC_LEN1_OFFSET,1);
			if(len == 0) break;
			uint8_t *password = (uint8_t*)pvPortMalloc(len+3);
			Flash_read(password,FINGER_FUNC_BASE_ADDR+id*FINGER_FUNC_BASE_SIZE,len+3);
			crc_value = Calc_CRC(password,len+3);
			printf("crc_value = %d\r\n",crc_value);
			vTaskDelay(10);
			Flash_read((uint8_t *)&rec_crc,FINGER_FUNC_BASE_ADDR+id*FINGER_FUNC_BASE_SIZE+len+3,4);
			printf("rec_crc = %d",rec_crc);
			if(rec_crc == crc_value)		//crc校验通过
			{
				uint8_t led_status = 0;
				CH9329_Get_Info();
				xQueueReceive(Queue_Computer_Info_Handle,&led_status,200);
				if(led_status & LED_STATE_CAPS_LOCK)
				{
					CH9329_Input_Fuc_Key(NO_CTRL,KEY_CapsLock);
				}
				CH9329_Keyboard_Switch();	//系统键盘切换
				CH9329_Input_Ascii((char*)&password[3],len);
				CH9329_Input_Fuc_Key(NO_CTRL,KEY_LeftEnter);
				CH9329_Keyboard_Switch();	//系统键盘切换
				if(led_status & LED_STATE_CAPS_LOCK)
				{
					CH9329_Input_Fuc_Key(NO_CTRL,KEY_CapsLock);
				}
			}
			vPortFree(password);
			break;
			
		}
		case TYPE_Account_Password:		//账号+密码
		{
			uint8_t account_len = 0;
			uint8_t password_len = 0;
			uint32_t crc_value = 0;
			uint32_t rec_crc = 0;
			Flash_read(&account_len,FINGER_FUNC_BASE_ADDR+id*FINGER_FUNC_BASE_SIZE+FINGER_FUNC_LEN1_OFFSET,1);
			if(account_len == 0) break;
			printf("account len = %d\r\n",account_len);
			Flash_read(&password_len,FINGER_FUNC_BASE_ADDR+id*FINGER_FUNC_BASE_SIZE+FINGER_FUNC_LEN1_OFFSET+2+account_len,1);
			if(password_len == 0) break;
			printf("password len = %d\r\n",password_len);
			uint8_t *account_password = (uint8_t *)pvPortMalloc(account_len+password_len+3+1+1);
			Flash_read(account_password,FINGER_FUNC_BASE_ADDR+id*FINGER_FUNC_BASE_SIZE,account_len+password_len+3+1+1);
			crc_value = Calc_CRC(account_password,account_len+password_len+3+1+1);
			printf("crc_value = %x\r\n",crc_value);
			vTaskDelay(10);
			Flash_read((uint8_t *)&rec_crc,FINGER_FUNC_BASE_ADDR+id*FINGER_FUNC_BASE_SIZE+account_len+password_len+3+1+1,4);
			printf("rec_crc = %x",rec_crc);
			if(rec_crc == crc_value)		//crc校验通过
			{
				uint8_t led_status = 0;
				CH9329_Get_Info();
				xQueueReceive(Queue_Computer_Info_Handle,&led_status,200);
				if(led_status & LED_STATE_CAPS_LOCK)
				{
					CH9329_Input_Fuc_Key(NO_CTRL,KEY_CapsLock);
				}
				CH9329_Keyboard_Switch();	//系统键盘切换
				uint8_t *account = (uint8_t *)pvPortMalloc(account_len);
				uint8_t *password = (uint8_t *)pvPortMalloc(password_len);
				memcpy(account,(uint8_t*)&account_password[3],account_len);
				memcpy(password,(uint8_t*)&account_password[2+account_len+2],password_len);
				CH9329_Input_Ascii((char*)account,account_len);
				vTaskDelay(10);
				CH9329_Input_Fuc_Key(NO_CTRL,KEY_Tab);
				vTaskDelay(10);
				CH9329_Input_Ascii((char*)password,password_len);
				vTaskDelay(50);
				CH9329_Input_Fuc_Key(NO_CTRL,KEY_LeftEnter);
				vTaskDelay(10);
				CH9329_Keyboard_Switch();	//系统键盘切换
				if(led_status & LED_STATE_CAPS_LOCK)
				{
					CH9329_Input_Fuc_Key(NO_CTRL,KEY_CapsLock);
				}
				vPortFree(account);
				vPortFree(password);
				
			}
			vPortFree(account_password);
			break;
		}
		case TYPE_Shortcut:		//快捷键
		{
			uint8_t func_key = 0;
			char key[6] = {0};
			uint8_t key_len = 0;	//功能键+按键总长度
			Flash_read(&key_len,FINGER_FUNC_BASE_ADDR+id*FINGER_FUNC_BASE_SIZE+FINGER_FUNC_LEN1_OFFSET,1);
			if(key_len == 0) break;
			Flash_read(&func_key,FINGER_FUNC_BASE_ADDR+id*FINGER_FUNC_BASE_SIZE+FINGER_FUNC_LEN1_OFFSET+2,1);
			Flash_read((uint8_t*)key,FINGER_FUNC_BASE_ADDR+id*FINGER_FUNC_BASE_SIZE+FINGER_FUNC_LEN1_OFFSET+3,key_len-1);
			CH9329_Input_Shortcut(func_key,key,key_len-1);
			break;
		}
		case TYPE_QuickStart:	//快捷启动应用
		{
			uint8_t quick_start = 0;
			Flash_read(&quick_start,FINGER_FUNC_BASE_ADDR+id*FINGER_FUNC_BASE_SIZE+FINGER_FUNC_LEN1_OFFSET,1);
			switch(quick_start)
			{
				case QUICK_START_1:
				{
					Finger_Func_Quick_Start('0');
					break;
				}
				case QUICK_START_2:
				{
					Finger_Func_Quick_Start('1');
					break;
				}
				case QUICK_START_3:
				{
					Finger_Func_Quick_Start('2');
					break;
				}
				case QUICK_START_4:
				{
					Finger_Func_Quick_Start('3');
					break;
				}
				case QUICK_START_5:
				{
					Finger_Func_Quick_Start('4');
					break;
				}
				case QUICK_START_6:
				{
					Finger_Func_Quick_Start('5');
					break;
				}
				default : break;
			}
		}
	}
}

/**
* @brief		指纹验证通过且按键按下后执行对应的操作
* @param		- id 验证成功的指纹序号
* @param		- score 验证成功的指纹得分
* @date			2023-10-16 22:22:14
* @return 	NULL
* @note
*/
static void Finger_Key_Function(uint16_t id,uint16_t score)
{
	uint8_t func_type = 0;
	Flash_read(&func_type,FINGER_KEY_FUNC_BASE_ADDR+id*FINGER_FUNC_BASE_SIZE,1);
	switch (func_type)
	{
		case TYPE_KEY_Windows_Password:
		{
			uint8_t len = 0;
			uint32_t crc_value = 0;
			uint32_t rec_crc = 0;
			Flash_read(&len,FINGER_KEY_FUNC_BASE_ADDR+id*FINGER_FUNC_BASE_SIZE+FINGER_FUNC_LEN1_OFFSET,1);
			if(len == 0) break;
			uint8_t *password = (uint8_t*)pvPortMalloc(len+3);
			Flash_read(password,FINGER_KEY_FUNC_BASE_ADDR+id*FINGER_FUNC_BASE_SIZE,len+3);
			crc_value = Calc_CRC(password,len+3);
			printf("crc_value = %d\r\n",crc_value);
			vTaskDelay(10);
			Flash_read((uint8_t *)&rec_crc,FINGER_KEY_FUNC_BASE_ADDR+id*FINGER_FUNC_BASE_SIZE+len+3,4);
			printf("rec_crc = %d",rec_crc);
			if(rec_crc == crc_value)		//crc校验通过
			{
				uint8_t led_status = 0;
				CH9329_Get_Info();
				xQueueReceive(Queue_Computer_Info_Handle,&led_status,200);
				if(led_status & LED_STATE_CAPS_LOCK)
				{
					CH9329_Input_Fuc_Key(NO_CTRL,KEY_CapsLock);
				}
				CH9329_Input_Fuc_Key(NO_CTRL,KEY_LeftCtrl);
				vTaskDelay(400);
				CH9329_Keyboard_Switch();	//系统键盘切换
				CH9329_Input_Ascii((char*)&password[3],len);
				CH9329_Input_Fuc_Key(NO_CTRL,KEY_LeftEnter);
				CH9329_Keyboard_Switch();	//系统键盘切换
				if(led_status & LED_STATE_CAPS_LOCK)
				{
					CH9329_Input_Fuc_Key(NO_CTRL,KEY_CapsLock);
				}
			}
			vPortFree(password);
			break;
		}
		case TYPE_KEY_Password:			//密码
		{
			uint8_t len = 0;
			uint32_t crc_value = 0;
			uint32_t rec_crc = 0;
			Flash_read(&len,FINGER_KEY_FUNC_BASE_ADDR+id*FINGER_FUNC_BASE_SIZE+FINGER_FUNC_LEN1_OFFSET,1);
			if(len == 0) break;
			uint8_t *password = (uint8_t*)pvPortMalloc(len+3);
			Flash_read(password,FINGER_KEY_FUNC_BASE_ADDR+id*FINGER_FUNC_BASE_SIZE,len+3);
			crc_value = Calc_CRC(password,len+3);
			printf("crc_value = %d\r\n",crc_value);
			vTaskDelay(10);
			Flash_read((uint8_t *)&rec_crc,FINGER_KEY_FUNC_BASE_ADDR+id*FINGER_FUNC_BASE_SIZE+len+3,4);
			printf("rec_crc = %d",rec_crc);
			if(rec_crc == crc_value)		//crc校验通过
			{
				uint8_t led_status = 0;
				CH9329_Get_Info();
				xQueueReceive(Queue_Computer_Info_Handle,&led_status,200);
				if(led_status & LED_STATE_CAPS_LOCK)
				{
					CH9329_Input_Fuc_Key(NO_CTRL,KEY_CapsLock);
				}
				CH9329_Keyboard_Switch();	//系统键盘切换
				CH9329_Input_Ascii((char*)&password[3],len);
				CH9329_Input_Fuc_Key(NO_CTRL,KEY_LeftEnter);
				CH9329_Keyboard_Switch();	//系统键盘切换
				if(led_status & LED_STATE_CAPS_LOCK)
				{
					CH9329_Input_Fuc_Key(NO_CTRL,KEY_CapsLock);
				}
			}
			vPortFree(password);
			break;
			
		}
		case TYPE_KEY_Account_Password:		//账号+密码
		{
			uint8_t account_len = 0;
			uint8_t password_len = 0;
			uint32_t crc_value = 0;
			uint32_t rec_crc = 0;
			Flash_read(&account_len,FINGER_KEY_FUNC_BASE_ADDR+id*FINGER_FUNC_BASE_SIZE+FINGER_FUNC_LEN1_OFFSET,1);
			if(account_len == 0) break;
			printf("account len = %d\r\n",account_len);
			Flash_read(&password_len,FINGER_KEY_FUNC_BASE_ADDR+id*FINGER_FUNC_BASE_SIZE+FINGER_FUNC_LEN1_OFFSET+2+account_len,1);
			if(password_len == 0) break;
			printf("password len = %d\r\n",password_len);
			uint8_t *account_password = (uint8_t *)pvPortMalloc(account_len+password_len+3+1+1);
			Flash_read(account_password,FINGER_KEY_FUNC_BASE_ADDR+id*FINGER_FUNC_BASE_SIZE,account_len+password_len+3+1+1);
			crc_value = Calc_CRC(account_password,account_len+password_len+3+1+1);
			printf("crc_value = %x\r\n",crc_value);
			vTaskDelay(10);
			Flash_read((uint8_t *)&rec_crc,FINGER_KEY_FUNC_BASE_ADDR+id*FINGER_FUNC_BASE_SIZE+account_len+password_len+3+1+1,4);
			printf("rec_crc = %x",rec_crc);
			if(rec_crc == crc_value)		//crc校验通过
			{
				uint8_t led_status = 0;
				CH9329_Get_Info();
				xQueueReceive(Queue_Computer_Info_Handle,&led_status,200);
				if(led_status & LED_STATE_CAPS_LOCK)
				{
					CH9329_Input_Fuc_Key(NO_CTRL,KEY_CapsLock);
				}
				CH9329_Keyboard_Switch();	//系统键盘切换
				uint8_t *account = (uint8_t *)pvPortMalloc(account_len);
				uint8_t *password = (uint8_t *)pvPortMalloc(password_len);
				memcpy(account,(uint8_t*)&account_password[3],account_len);
				memcpy(password,(uint8_t*)&account_password[2+account_len+2],password_len);
				CH9329_Input_Ascii((char*)account,account_len);
				vTaskDelay(10);
				CH9329_Input_Fuc_Key(NO_CTRL,KEY_Tab);
				vTaskDelay(10);
				CH9329_Input_Ascii((char*)password,password_len);
				vTaskDelay(50);
				CH9329_Input_Fuc_Key(NO_CTRL,KEY_LeftEnter);
				vTaskDelay(10);
				CH9329_Keyboard_Switch();	//系统键盘切换
				if(led_status & LED_STATE_CAPS_LOCK)
				{
					CH9329_Input_Fuc_Key(NO_CTRL,KEY_CapsLock);
				}
				vPortFree(account);
				vPortFree(password);
				
			}
			vPortFree(account_password);
			break;
		}
		case TYPE_KEY_Shortcut:		//快捷键
		{
			uint8_t func_key = 0;
			char key[6] = {0};
			uint8_t key_len = 0;	//功能键+按键总长度
			Flash_read(&key_len,FINGER_KEY_FUNC_BASE_ADDR+id*FINGER_FUNC_BASE_SIZE+FINGER_FUNC_LEN1_OFFSET,1);
			if(key_len == 0) break;
			Flash_read(&func_key,FINGER_KEY_FUNC_BASE_ADDR+id*FINGER_FUNC_BASE_SIZE+FINGER_FUNC_LEN1_OFFSET+2,1);
			Flash_read((uint8_t*)key,FINGER_KEY_FUNC_BASE_ADDR+id*FINGER_FUNC_BASE_SIZE+FINGER_FUNC_LEN1_OFFSET+3,key_len-1);
			
			CH9329_Input_Shortcut(func_key,key,key_len-1);
			break;
		}
		case TYPE_KEY_QuickStart:	//快捷启动应用
		{
			uint8_t quick_start = 0;
			Flash_read(&quick_start,FINGER_KEY_FUNC_BASE_ADDR+id*FINGER_FUNC_BASE_SIZE+FINGER_FUNC_LEN1_OFFSET,1);
			switch(quick_start)
			{
				case QUICK_START_1:
				{
					Finger_Func_Quick_Start('0');
					break;
				}
				case QUICK_START_2:
				{
					Finger_Func_Quick_Start('1');
					break;
				}
				case QUICK_START_3:
				{
					Finger_Func_Quick_Start('2');
					break;
				}
				case QUICK_START_4:
				{
					Finger_Func_Quick_Start('3');
					break;
				}
				case QUICK_START_5:
				{
					Finger_Func_Quick_Start('4');
					break;
				}
				case QUICK_START_6:
				{
					Finger_Func_Quick_Start('5');
					break;
				}
				default : break;
			}
		}
	}
}

/**
* @brief	执行快捷启动功能
* @date	2023-10-24 19:08:29
* @return 
*/
static int Finger_Func_Quick_Start(char key)
{
	if(key < '0' || key > '5')
	{
		return OPERATE_ERROR_INVALID_PARAMETERS;
	}
	CH9329_Input_Shortcut(R_WINDOWS|R_CTRL,&key,1);
	
	return OPERATE_SUCCESS;
}

