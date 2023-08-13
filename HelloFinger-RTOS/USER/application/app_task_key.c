#include "app_task_key.h"
#include "drv_fpm383.h"
#include "usart.h"

static void vTaskKeyProcessing(void);
int Key_Protocol_Mode_RecData_Handle(uint8_t data);
int Key_Trans_Mode_RecData_Handle(uint8_t data);
static void KeyResetData(void);
static int Key_CMP_Checksum(uint8_t *data,uint8_t len);
static void Key_Func_Exec(void);

extern CMD_AutoEnroll_t 				g_autoenroll;
extern CMD_AutoIdentify_t 			g_autoidentify;
extern CMD_DeleteChar_t 				g_deletechar;
extern CMD_Cancel_t							g_cancel;
extern CMD_Sleep_t							g_sleep;
extern CMD_ValidTempleteNum_t 	g_valid_num;
extern CMD_ReadIndexTable_t	 		g_read_index_table;
extern CMD_SetPwd_t							g_set_pwd;
extern CMD_VfyPwd_t							g_vfy_pwd;
extern CMD_HandShake_t					g_hand_shake;
extern CMD_CheckSensor_t				g_check_sensor;
extern CMD_SetChipAddr_t				g_set_chip_addr;
extern CMD_WriteNotePad_t				g_write_notepad;
extern CMD_ReadNotepad_t   			g_read_notepad;
extern CMD_GetImage_t						g_get_image;
extern CMD_GenChar_t						g_gen_char;
extern CMD_RegModel_t						g_reg_model;
extern CMD_StoreChar_t					g_store_char;
extern CMD_Match_t							g_match;


TaskHandle_t Task_Key_Handle = NULL;
QueueHandle_t Queue_KeyProcessing_Handle = NULL;

KEY_DATA_CONTROLLR_t g_key_data_ctl = {0};
KEY_DATA_FORMAT_t g_key_data_format = {0};


int Key_GiveNotifyFromISR(uint8_t *recData,uint8_t dataSize)
{
	portBASE_TYPE xHigherPriorityTaskWoken = pdTRUE;
	if(Queue_KeyProcessing_Handle != NULL)
	{
		xQueueSendFromISR(Queue_KeyProcessing_Handle,recData,&xHigherPriorityTaskWoken);
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	}
	return OPERATE_SUCCESS;
}

int Task_Key_DataCTLCreate(void)
{
	xTaskCreate( (TaskFunction_t)vTaskKeyProcessing,
								(const char*  )"KeyDataControl",
								(uint32_t     )TASK_KEY_CONTROL_SIZE,
								(void *				)NULL,
								(UBaseType_t  )TASK_KEY_CONTROL_PRIORITY,
								&Task_Key_Handle);
	return OPERATE_SUCCESS;
}


static void vTaskKeyProcessing(void)
{
	uint8_t rec_data = 0;
	KeyResetData();
	Queue_KeyProcessing_Handle = xQueueCreate((UBaseType_t)KEY_DATA_HANDLE_QUEUE_LEN,(UBaseType_t)KEY_DATA_HANDLE_QUEUE_SIZE);
	while(1)
	{
		BaseType_t ret = xQueueReceive(Queue_KeyProcessing_Handle,&rec_data,portMAX_DELAY);
		if(ret == pdTRUE)
		{
			Key_Protocol_Mode_RecData_Handle(rec_data);
			Key_Trans_Mode_RecData_Handle(rec_data);
		}
		else
		{
			KeyResetData();
		}
	}
}


int Key_Protocol_Mode_RecData_Handle(uint8_t data)	//协议传输数据处理
{
	if(g_key_data_ctl.head_state_H == DATA_RECV_STATE_NO_GET)
	{
		if(data == KEY_CMD_HEAD_H)
		{
			g_key_data_ctl.head_state_H = DATA_RECV_STATE_GET;
			*g_key_data_ctl.pData = data;
			g_key_data_ctl.pData++;
			g_key_data_ctl.rec_data_size++;
		}
		else
		{
			KeyResetData();
		}
	}
	else
	{
		if(g_key_data_ctl.head_state_L == DATA_RECV_STATE_NO_GET)
		{
			if(data == KEY_CMD_HEAD_L)
			{
				g_key_data_ctl.head_state_L = DATA_RECV_STATE_GET;
				*g_key_data_ctl.pData = data;
				g_key_data_ctl.pData++;
				g_key_data_ctl.rec_data_size++;
			}
			else
			{
				KeyResetData();
			}
		}
		else
		{
			if(g_key_data_ctl.addr_state == DATA_RECV_STATE_NO_GET)
			{
				if(data == KEY_CMD_ADDR)
				{
					g_key_data_ctl.addr_state = DATA_RECV_STATE_GET;
					*g_key_data_ctl.pData = data;
					g_key_data_ctl.pData++;
					g_key_data_ctl.rec_data_size++;
				}
				else
				{
					KeyResetData();
				}
			}
			else
			{
				if(g_key_data_ctl.rec_data_size < 5)
				{
					*g_key_data_ctl.pData = data;
					g_key_data_ctl.pData++;
					g_key_data_ctl.rec_data_size++;
				}
				else
				{
					g_key_data_ctl.data_state = DATA_RECV_STATE_GET;
					g_key_data_ctl.data_length = g_key_data_format.len+CH9329_CHECKSUM_LEN;
					g_key_data_ctl.rec_data_size++;
				}
				if(g_key_data_ctl.data_state == DATA_RECV_STATE_GET)
				{
					if(g_key_data_ctl.data_length)
					{
						g_key_data_ctl.data_length--;
						*g_key_data_ctl.pData = data;
						g_key_data_ctl.pData++;
					}
					else
					{
						int result = Key_CMP_Checksum((uint8_t*)g_key_data_format.head,g_key_data_format.len);
						if(result == OPERATE_SUCCESS)
						{
							Key_Func_Exec();
							KeyResetData();
						}
						else
						{
							KeyResetData();
						}
					}
				}
			}
		}
	}
	return OPERATE_SUCCESS;
}

int Key_Trans_Mode_RecData_Handle(uint8_t data)	//透传模式数据处理
{
	
}

static void KeyResetData(void)
{
	memset(&g_key_data_ctl,0,sizeof(KEY_DATA_CONTROLLR_t));
	g_key_data_ctl.pData = (uint8_t*)&g_key_data_format;
}

/* 比较校验位 */
static int Key_CMP_Checksum(uint8_t *data,uint8_t len)
{
	uint8_t checksum = 0;
	for(uint8_t i=0; i<len; i++)
	{
		checksum += data[i];
	}
	if(checksum == data[len])
	{
		return OPERATE_SUCCESS;
	}
	else
	{
		return OPERATE_ERROR_INVALID_PARAMETERS;
	}
}

static void Key_Func_Exec(void)
{
	switch (g_key_data_format.cmd)
	{
		case CMD_GET_INFO:
		{
			
			break;
		}
		case CMD_SEND_KB_GENERAL_DATA:
		{
			
			break;
		}
		case CMD_SEND_KB_MEDIA_DATA:
		{
			
			break;
		}
		case CMD_SEND_MS_ABS_DATA:
		{
			
			break;
		}
		case CMD_SEND_MS_REL_DATA:
		{
			
			break;
		}
		case CMD_SEND_MY_HID_DATA:
		{
			
			break;
		}
		case CMD_READ_MY_HID_DATA:
		{
			HID_Data_Handle();
			break;
		}
		case CMD_GET_PARA_CFG:
		{
			
			break;
		}
		case CMD_SET_PARA_CFG:
		{
			
			break;
		}
		case CMD_GET_USB_STRING:
		{
			
			break;
		}
		default : break;
	}
}

int HID_Data_Handle(void)
{
	 if(g_key_data_format.data[0] == 0xFE && (Key_CMP_Checksum((uint8_t*)&g_key_data_format.data,g_key_data_format.data[1]) == g_key_data_format.data[g_key_data_format.data[1]+2]))	//判断是否为自定义USB通信协议头
	 {
		 
		 switch (g_key_data_format.data[2])		//判断指令类型
		 {
			 case USB_PROTOCOL_FORMAT_MODE_SWITCH:	//协议传输/透传模式切换
			 {
				 break;
			 }
			 case USB_PROTOCOL_FORMAT_GET_INDEX_LIST:	//获取索引表状态
			 {
				 Generate_ReadIndexTable(0);
				 HAL_UART_Transmit(&huart2,(uint8_t*)&g_read_index_table,g_read_index_table.LEN[0]<<8|g_read_index_table.LEN[1],1000);
				 xEventGroupSetBits((EventGroupHandle_t)FingerEvent_Handle,(EventBits_t)EVENT_INDEX_LIST);
				 break;
			 }
			 case USB_PROTOCOL_FORMAT_ENROLL_FINGER:
			 {
				 uint16_t id = g_key_data_format.data[3]<<8|g_key_data_format.data[4];
				 uint8_t enroll_times = g_key_data_format.data[5];
				 uint16_t param = g_key_data_format.data[6]<<8|g_key_data_format.data[7];
				 Generate_AutoEnroll(id,enroll_times,param);
				 HAL_UART_Transmit(&huart2,(uint8_t*)&g_autoenroll,g_autoenroll.LEN[0]<<8|g_autoenroll.LEN[1],1000);
				 xEventGroupSetBits((EventGroupHandle_t)FingerEvent_Handle,(EventBits_t)EVENT_AUTO_ENROLL);
			 }
			 default : break;
		 }
	 }
	 else
	 {
			return OPERATE_ERROR_INVALID_PARAMETERS;
	 }
	 return OPERATE_SUCCESS;
}
