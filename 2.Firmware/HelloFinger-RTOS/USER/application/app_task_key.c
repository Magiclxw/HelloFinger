#include "app_task_key.h"
#include "drv_fpm383.h"
#include "usart.h"
#include "string.h"
#include "..\USER\driver\W25Q128\drv_w25q128.h"
#include "app_task_finger.h"
#include "app_task_rgb.h"

static void vTaskKeyProcessing(void);
int Key_Protocol_Mode_RecData_Handle(uint8_t data);
int Key_Trans_Mode_RecData_Handle(uint8_t data);
static void KeyResetData(void);
static int Key_CMP_Checksum(uint8_t *data,uint8_t len);
static void Key_Func_Exec(void);



TaskHandle_t Task_Key_Handle = NULL;
QueueHandle_t Queue_KeyProcessing_Handle = NULL;
QueueHandle_t Queue_Computer_Info_Handle = NULL;

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

static uint8_t store_msg[100] = {0};

static void vTaskKeyProcessing(void)
{
	uint8_t rec_data = 0;
	KeyResetData();
	Queue_KeyProcessing_Handle = xQueueCreate((UBaseType_t)KEY_DATA_HANDLE_QUEUE_LEN,(UBaseType_t)KEY_DATA_HANDLE_QUEUE_SIZE);
	Queue_Computer_Info_Handle = xQueueCreate((UBaseType_t)COMPUTER_INFO_QUEUE_LEN,(UBaseType_t)COMPUTER_INFO_QUEUE_SIZE);
	//uint16_t id = 0x00;
	//uint8_t enroll_times = 0x02;
	//uint16_t param = 0x0F;
	//Generate_AutoEnroll(id,enroll_times,param);
	//HAL_UART_Transmit(&FINGER_HANDLE,(uint8_t*)&g_autoenroll,g_autoenroll.LEN[0]<<8|g_autoenroll.LEN[1]+FIXED_CMD_LEN,1000);
	//taskENTER_CRITICAL();
	//Generate_ReadIndexTable(0);
	//HAL_UART_Transmit(&huart2,(uint8_t*)&g_read_index_table,g_read_index_table.LEN[0]<<8|g_read_index_table.LEN[1]+FIXED_CMD_LEN,1000);
	//taskEXIT_CRITICAL();
	_LED_Function_t func = LED_FUNC_BREATHE;
	uint8_t start_color = LED_COLOR_RED|LED_COLOR_GREEN;
	uint8_t end_color = LED_COLOR_RED|LED_COLOR_GREEN;
	uint8_t cycle_time = 0;
	Generate_ControlBLN(func,start_color,end_color,cycle_time);
	HAL_UART_Transmit(&FINGER_HANDLE,(uint8_t*)&g_control_bln,g_control_bln.LEN[0]<<8|g_control_bln.LEN[1]+FIXED_CMD_LEN,1000);
	CH9329_Get_Info();
	RGB_Effect(255,0,0,500,2);
	//uint8_t time = 36;
	//uint8_t color1 = 0x99;
	//uint8_t color2 = 0x00;
	//uint8_t color3 = 0x00;
	//uint8_t color4 = 0x00;
	//uint8_t color5 = 0x00;
	//uint8_t cycle = 0;
	//Generate_ControlBLN_Program(time,color1,color2,color3,color4,color5,cycle);
	//HAL_UART_Transmit(&FINGER_HANDLE,(uint8_t*)&g_control_bln_pro,g_control_bln_pro.LEN[0]<<8|g_control_bln_pro.LEN[1]+FIXED_CMD_LEN,1000);
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
					else if(g_key_data_ctl.rec_data_size == 5)
					{
						g_key_data_ctl.data_state = DATA_RECV_STATE_GET;
						g_key_data_ctl.data_length = g_key_data_format.len;
						g_key_data_ctl.rec_data_size++;
						if(g_key_data_ctl.data_length > 64) KeyResetData();
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
							*g_key_data_ctl.pData = data;
							int result = Key_CMP_Checksum((uint8_t*)g_key_data_format.head,g_key_data_format.len+5);
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
	switch ((g_key_data_format.cmd) & 0x0F)	//响应码会在原命令码基础上|0x80，为了匹配去除高位
	{
		case CMD_GET_INFO:
		{
			uint8_t version = 0;
			uint8_t connection = 0;
			uint8_t led_state = 0;
			version = g_key_data_format.data[0];
			connection = g_key_data_format.data[1];
			led_state = g_key_data_format.data[2];
			printf("version = %x,connection = %x,led_state = %x\r\n",version,connection,led_state);
			xQueueSend(Queue_Computer_Info_Handle,&led_state,0);
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
		case CMD_READ_MY_HID_DATA & 0x0F:
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
	uint8_t result = Key_CMP_Checksum((uint8_t*)&g_key_data_format.data,g_key_data_format.data[1]+2);
	 if((g_key_data_format.data[0] == 0xFE) && (result == (uint8_t)OPERATE_SUCCESS))	//判断是否为自定义USB通信协议头
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
				 HAL_UART_Transmit(&FINGER_HANDLE,(uint8_t*)&g_read_index_table,g_read_index_table.LEN[0]<<8|g_read_index_table.LEN[1]+FIXED_CMD_LEN,1000);
				 xEventGroupSetBits((EventGroupHandle_t)FingerEvent_Handle,(EventBits_t)EVENT_INDEX_LIST);
				 break;
			 }
			 case USB_PROTOCOL_FORMAT_ENROLL_FINGER:	//注册指纹
			 {
				 uint16_t id = g_key_data_format.data[5]<<8|g_key_data_format.data[6];
				 uint8_t enroll_times = g_key_data_format.data[7];
				 uint16_t param = g_key_data_format.data[8]<<8|g_key_data_format.data[9];
				 Generate_AutoEnroll(id,enroll_times,param);
				 HAL_UART_Transmit(&FINGER_HANDLE,(uint8_t*)&g_autoenroll,g_autoenroll.LEN[0]<<8|g_autoenroll.LEN[1]+FIXED_CMD_LEN,1000);
				 xEventGroupSetBits((EventGroupHandle_t)FingerEvent_Handle,(EventBits_t)EVENT_AUTO_ENROLL);
				 break;
			 }
			 case USB_PROTOCOL_FORMAT_DELETE_FINGER:	//删除指纹
			 {
				 uint16_t id = g_key_data_format.data[5]<<8|g_key_data_format.data[6];
				 uint16_t num = g_key_data_format.data[7]<<8|g_key_data_format.data[8];
				 Generate_DeletChar(id,num);
				 HAL_UART_Transmit(&FINGER_HANDLE,(uint8_t*)&g_deletechar,g_deletechar.LEN[0]<<8|g_deletechar.LEN[1]+FIXED_CMD_LEN,1000);
				 xEventGroupSetBits((EventGroupHandle_t)FingerEvent_Handle,(EventBits_t)EVENT_DELETE_CHAR);
				 break;
			 }
			 case USB_PROTOCOL_FORMAT_SET_FINGER_COLOR:	//设置指纹模块颜色
			 {
				 uint8_t func = g_key_data_format.data[5];
				 uint8_t start_color = g_key_data_format.data[6];
				 uint8_t end_color = g_key_data_format.data[7];
				 uint8_t cycle_time = g_key_data_format.data[8];
				 Generate_ControlBLN((_LED_Function_t)func,start_color,end_color,cycle_time);
				 HAL_UART_Transmit(&FINGER_HANDLE,(uint8_t*)&g_control_bln,g_control_bln.LEN[0]<<8|g_control_bln.LEN[1]+FIXED_CMD_LEN,1000);
				 break;
			 }
			 case USB_PROTOCOL_FORMAT_SET_FINGER_COLOR_PRO:
			 {
				 uint8_t time = g_key_data_format.data[5];
				 uint8_t color1 = g_key_data_format.data[6];
				 uint8_t color2 = g_key_data_format.data[7];
				 uint8_t color3 = g_key_data_format.data[8];
				 uint8_t color4 = g_key_data_format.data[9];
				 uint8_t color5 = g_key_data_format.data[10];
				 uint8_t cycle = g_key_data_format.data[11];
				 Generate_ControlBLN_Program(time,color1,color2,color3,color4,color5,cycle);
				 HAL_UART_Transmit(&FINGER_HANDLE,(uint8_t*)&g_control_bln_pro,g_control_bln_pro.LEN[0]<<8|g_control_bln_pro.LEN[1]+FIXED_CMD_LEN,1000);
				 break;
			 }
			 case USB_PROTOCOL_FORMAT_FUNC_STORE:	//存储指纹验证成功执行功能
			 {
				 static uint16_t packNum = 0;	//后续包个数
				 static uint8_t seqLen1 = 0;	//第一包数据长度(开机密码、密码、快捷键)
				 static uint8_t seqLen2 = 0;	//第二包数据长度(账号+密码)
				 static uint8_t index = 0;
				 packNum = g_key_data_format.data[3]<<8|g_key_data_format.data[4];
				 if(g_key_data_format.data[5] == TYPE_Windows_Password)	//开机密码
				 {
					 if(packNum == 1)
					 {
						 index = g_key_data_format.data[6];
						 seqLen1 = g_key_data_format.data[7];
					 }
					 if(packNum == 0 && index == g_key_data_format.data[6])
					 {
						 uint32_t crc_value = 0;
						 //uint8_t *store_msg = (uint8_t *)pvPortMalloc(seqLen1+3);
						 //memset((uint8_t*)store_msg,0,seqLen1+3);	//初始化申请空间，防止未知数据影响crc结果
						 store_msg[0] = TYPE_Windows_Password;
						 store_msg[1] = seqLen1;
						 store_msg[2] = (uint8_t)FINGER_FUNC_RESERVED_DATA;
						 for(uint8_t i=0; i<seqLen1; i++)
						 {
							 store_msg[3+i] = g_key_data_format.data[7+i];
						 }
						 crc_value = Calc_CRC(store_msg,seqLen1+3);
						 printf("crc_value = %d\r\n",crc_value);
						 Flash_write(store_msg,FINGER_FUNC_BASE_ADDR+index*FINGER_FUNC_BASE_SIZE,seqLen1+3);
						 vTaskDelay(10);	//延时，防止前一次dma传输未完成
						 Flash_write((uint8_t*)&crc_value,FINGER_FUNC_BASE_ADDR+index*FINGER_FUNC_BASE_SIZE+seqLen1+3,4);
						 index = 0;
						 seqLen1 = 0;
						 seqLen2 = 0;
						 packNum = 0;
						 Display_Result(RESULT_SUCCESS);
						 //vPortFree((uint8_t*)store_msg);
						 memset((uint8_t*)store_msg,0,100);
					 }
				 }
				 if(g_key_data_format.data[5] == TYPE_Password)	//密码
				 {
					 if(packNum == 1)
					 {
						 index = g_key_data_format.data[6];
						 seqLen1 = g_key_data_format.data[7];
					 }
					 if(packNum == 0 && index == g_key_data_format.data[6])
					 {
						 uint32_t crc_value = 0;
						 //uint8_t *store_msg = (uint8_t *)pvPortMalloc(seqLen1+3);
						 //memset((uint8_t*)store_msg,0,seqLen1+3);	//初始化申请空间，防止未知数据影响crc结果
						 store_msg[0] = TYPE_Password;
						 store_msg[1] = seqLen1;
						 store_msg[2] = (uint8_t)FINGER_FUNC_RESERVED_DATA;
						 for(uint8_t i=0; i<seqLen1; i++)
						 {
							 store_msg[3+i] = g_key_data_format.data[7+i];
						 }
						 crc_value = Calc_CRC(store_msg,seqLen1+3);
						 Flash_write(store_msg,FINGER_FUNC_BASE_ADDR+index*FINGER_FUNC_BASE_SIZE,seqLen1+3);
						 vTaskDelay(10);
						 Flash_write((uint8_t*)&crc_value,FINGER_FUNC_BASE_ADDR+index*FINGER_FUNC_BASE_SIZE+seqLen1+3,4);
						 index = 0;
						 seqLen1 = 0;
						 seqLen2 = 0;
						 packNum = 0;
						 Display_Result(RESULT_SUCCESS);
						 //vPortFree((uint8_t*)store_msg);
						 memset((uint8_t*)store_msg,0,100);
					 }
				 }
				 if(g_key_data_format.data[5] == TYPE_Account_Password)	//账号+密码
				 {
					 if(packNum == 2)	//第一包数据
					 {
						 index = g_key_data_format.data[6];
						 seqLen1 = g_key_data_format.data[7];	//账号长度
						 seqLen2 = g_key_data_format.data[8];	//密码长度
					 }
					 if(packNum == 1 && index == g_key_data_format.data[6])	//第二包数据
					 {
						 //uint32_t crc_value = 0;
						 //uint8_t *store_msg = (uint8_t *)pvPortMalloc(seqLen1+3);
						 //memset((uint8_t*)store_msg,0,seqLen1+3);	//初始化申请空间，防止未知数据影响crc结果
						 store_msg[0] = TYPE_Account_Password;
						 store_msg[1] = seqLen1;
						 store_msg[2] = (uint8_t)FINGER_FUNC_RESERVED_DATA;
						 for(uint8_t i=0; i<seqLen1; i++)
						 {
							 store_msg[3+i] = g_key_data_format.data[7+i];
						 }
						 //crc_value = Calc_CRC(store_msg,seqLen1+3);
						 //Flash_write(store_msg,FINGER_FUNC_BASE_ADDR+index*FINGER_FUNC_BASE_SIZE,seqLen1+3);
						 //vTaskDelay(10);
						 //Flash_write((uint8_t*)&crc_value,FINGER_FUNC_BASE_ADDR+index*FINGER_FUNC_BASE_SIZE+seqLen1+3,4);
					 }
					 if(packNum == 0 && index == g_key_data_format.data[6])
					 {
						 uint8_t len = 0;
						 uint32_t crc_value = 0;
						 store_msg[seqLen1+3] = seqLen2;	//存储密码长度
						 store_msg[seqLen1+3+1] = (uint8_t)FINGER_FUNC_RESERVED_DATA;//存储无效字节
						 for(uint8_t i =0; i<seqLen2; i++)
						 {
							 store_msg[seqLen1+3+1+i] = g_key_data_format.data[7+i];
						 }
						 
						 crc_value = Calc_CRC(store_msg,seqLen1+seqLen2+3+1);
						 printf("store crc = %x\r\n",crc_value);
						 Flash_write(store_msg,FINGER_FUNC_BASE_ADDR+index*FINGER_FUNC_BASE_SIZE,seqLen1+seqLen2+3+2);
						 
						 vTaskDelay(10);
						 
						 Flash_write((uint8_t*)&crc_value,FINGER_FUNC_BASE_ADDR+index*FINGER_FUNC_BASE_SIZE+seqLen1+seqLen2+3+2,4);
						
						 Display_Result(RESULT_SUCCESS);
					 }
				 }
					if(g_key_data_format.data[5] == TYPE_Shortcut)	//快捷键
					{
						if(packNum == 1)
						{
							index = g_key_data_format.data[6];	//指纹号
							seqLen1 = g_key_data_format.data[7];	//快捷键长度
						}
						if(packNum == 0 && index == g_key_data_format.data[6])
						{
							uint32_t crc_value = 0;
							store_msg[0] = TYPE_Shortcut;
							store_msg[1] = seqLen1;
							store_msg[2] = (uint8_t)FINGER_FUNC_RESERVED_DATA;;
							memcpy((uint8_t*)&store_msg[3],(uint8_t*)&g_key_data_format.data[7],seqLen1);
							crc_value = Calc_CRC(store_msg,seqLen1+3);
							Flash_write(store_msg,FINGER_FUNC_BASE_ADDR+index*FINGER_FUNC_BASE_SIZE,seqLen1+3);
							vTaskDelay(10);
							Flash_write((uint8_t*)&crc_value,FINGER_FUNC_BASE_ADDR+index*FINGER_FUNC_BASE_SIZE+seqLen1+3,4);
							Display_Result(RESULT_SUCCESS);
						}
					}
					break;
			 }
			 case USB_PROTOCOL_FORMAT_SET_RGB:
			 {
				 uint8_t color_R = g_key_data_format.data[5];
				 uint8_t color_G = g_key_data_format.data[6];
				 uint8_t color_B = g_key_data_format.data[7];
				 uint8_t interval = g_key_data_format.data[8];
				 uint32_t rgbi = color_R<<24|color_G<<16|color_B<<8|interval;
				 xQueueSend(RGB_Queue_Handle,&rgbi,0);
				 
				 break;
			 }
			 case USB_PROTOCOL_FORMAT_GET_FW_HW:
			 {
				 char compile_date[11] = {0};
				 char compile_time[8] = {0};
				 char firmware_version[15] = {0};
				 strcpy(compile_time,__TIME__);
				 printf("%s\r\n",compile_time);
				 strcpy(compile_date,__DATE__);
				 printf("%s\r\n",compile_date);
				 
				 g_usb_response.head = USB_RESPONSE_HEAD;
				 g_usb_response.len = 21;
				 g_usb_response.type = USB_PROTOCOL_FORMAT_GET_FW_HW;
				 g_usb_response.result = CONFIRM_OK;
				 
				 memcpy((uint8_t*)&g_usb_response.data[0],(uint8_t*)compile_date,11);
				 memcpy((uint8_t*)&g_usb_response.data[11],(uint8_t*)compile_time,8);
				 
				 g_usb_response.data[19] = CH9329_CAL_SUM((uint8_t*)&g_usb_response,23);
				 Send_HID_Data((uint8_t*)&g_usb_response,24);
				 break;
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
