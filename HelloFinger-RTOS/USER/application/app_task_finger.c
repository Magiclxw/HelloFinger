#include "app_task_finger.h"
#include "usart.h"
#include "sys_config.h"
#include "drv_ch9329.h"
#include "app_task_key.h"

static void vTaskFingerProcessing(void);	//ָ�ƽ������ݴ�������
static void FingerResetData(void);	//��λ���ܽṹ��
static int CMP_Checksum(uint8_t *data,uint8_t len);
int Finger_RecData_Handle(uint8_t data);
static void Finger_Func_Exec(void);

TaskHandle_t Task_Finger_Handle = NULL;
TaskHandle_t Task_Finger_Rec_Handle = NULL;
QueueHandle_t Queue_FingerProcessing_Handle = NULL;
EventGroupHandle_t FingerEvent_Handle	= NULL;		//ָ��ʱ���־�飬����ָ��͡����ռ��ͬ��

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
	FingerResetData();
	Queue_FingerProcessing_Handle = xQueueCreate((UBaseType_t)FINGER_DATA_HANDLE_QUEUE_LEN,(UBaseType_t)FINGER_DATA_HANDLE_QUEUE_SIZE);
	FingerEvent_Handle = xEventGroupCreate();	//��ʼ���¼���־��
	while(1)
	{
		BaseType_t ret = xQueueReceive(Queue_FingerProcessing_Handle,&rec_data,portMAX_DELAY);
		if(ret == pdTRUE)
		{
			Finger_RecData_Handle(rec_data);
		}
		else
		{
			FingerResetData();
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
									int result = CMP_Checksum((uint8_t*)&g_data_format.type,(g_data_format.len[0]<<8|g_data_format.len[1])+1);	//У����ǴӰ���ʶ��У���֮�������ֽ�֮�ͣ���������ʶ������У���
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


static int CMP_Checksum(uint8_t *data,uint8_t len)		//�Ƚ�У���
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
		case ID_CMD:	//�����
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
			switch(g_data_format.data[0])	//�ж�ȷ����
			{
				case CONFIRM_OK:
				{
					event_status = xEventGroupGetBits(FingerEvent_Handle);
					//event_status = xEventGroupWaitBits(FingerEvent_Handle,EVENT_INDEX_LIST,pdTRUE,pdFALSE,100);
					if(event_status & EVENT_INDEX_LIST)	//�ѷ��Ͷ�ȡ������ָ���ǰ���ص�����������Ϣ
					{
						g_usb_response.head = USB_RESPONSE_HEAD;
						g_usb_response.len = 34;
						g_usb_response.type = USB_PROTOCOL_FORMAT_GET_INDEX_LIST;
						g_usb_response.result = CONFIRM_OK;
						memcpy((uint8_t*)&g_usb_response.data,(uint8_t*)&g_data_format.data[1],32);
						g_usb_response.data[32] = CH9329_CAL_SUM((uint8_t*)&g_usb_response,36);
						Send_HID_Data((uint8_t*)&g_usb_response,37);
						xEventGroupClearBits(FingerEvent_Handle,EVENT_INDEX_LIST);
					}
					//event_status = xEventGroupWaitBits(FingerEvent_Handle,EVENT_AUTO_ENROLL,pdFALSE,pdFALSE,100);
					if(event_status & EVENT_AUTO_ENROLL)
					{
						g_usb_response.head = USB_RESPONSE_HEAD;
						g_usb_response.len = 4;
						g_usb_response.type = USB_PROTOCOL_FORMAT_ENROLL_FINGER;
						g_usb_response.result = CONFIRM_OK;
						g_usb_response.data[0] = g_data_format.data[1];	//����1
						g_usb_response.data[1] = g_data_format.data[2];	//����2
						g_usb_response.data[2] = CH9329_CAL_SUM((uint8_t*)&g_usb_response,6);
						if(g_usb_response.data[0] == 0x03 || g_usb_response.data[0] == 0x01)	//���°�����ָ
						{
							Send_HID_Data((uint8_t*)&g_usb_response,7);
						}
						if(g_usb_response.data[0] == 0x06 && g_usb_response.data[1] == 0xF2)	//���̽���,��λ��־
						{
							Send_HID_Data((uint8_t*)&g_usb_response,7);
							xEventGroupClearBits(FingerEvent_Handle,EVENT_AUTO_ENROLL);
						}
					}
					if(event_status & EVENT_DELETE_CHAR)
					{
						g_usb_response.head = USB_RESPONSE_HEAD;
						g_usb_response.len = 2;
						g_usb_response.type = USB_PROTOCOL_FORMAT_DELETE_FINGER;
						g_usb_response.result = CONFIRM_OK;
						g_usb_response.data[0] = CH9329_CAL_SUM((uint8_t*)&g_usb_response,4);
						Send_HID_Data((uint8_t*)&g_usb_response,5);
						xEventGroupClearBits(FingerEvent_Handle,EVENT_DELETE_CHAR);
					}
					if(event_status & EVENT_TOUCH_DETECT)	//ָ����֤���
					{
						if(g_data_format.data[1] == 0x05)
						{
							Generate_Sleep();
							HAL_UART_Transmit(&FINGER_HANDLE,(uint8_t*)&g_sleep,g_sleep.LEN[0]<<8|g_sleep.LEN[1]+FIXED_CMD_LEN,1000);
							xEventGroupClearBits(FingerEvent_Handle,EVENT_TOUCH_DETECT);
							
						}
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
				case CONFIRM_FINGER_SEARCH_FAIL:
				{
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
					break;
				}
				case CONFIRM_ENROLL_TIMES_ERROR:
				{
					break;
				}
				case CONFIRM_TIMEOUT:
				{
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
}





