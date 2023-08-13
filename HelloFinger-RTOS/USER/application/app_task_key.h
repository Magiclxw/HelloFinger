#ifndef __APP_TASK_KEY_H
#define __APP_TASK_KEY_H

#include "sys_config.h"
#include "drv_ch9329.h"

#define KEY_CMD_HEAD_H	0x57
#define KEY_CMD_HEAD_L	0xAB
#define KEY_CMD_ADDR		0x00

#define TASK_KEY_CONTROL_SIZE	(200)
#define TASK_KEY_CONTROL_PRIORITY	(5)
#define KEY_DATA_HANDLE_QUEUE_LEN	(10)
#define KEY_DATA_HANDLE_QUEUE_SIZE	(1)

typedef enum USB_PROTOCOL_FORMAT
{
	USB_PROTOCOL_FORMAT_NOUSE0,								//0x00
	USB_PROTOCOL_FORMAT_MODE_SWITCH = 0x01,		//0x01
	USB_PROTOCOL_FORMAT_NOUSE1,               //0x02
	USB_PROTOCOL_FORMAT_NOUSE2,               //0x03
	USB_PROTOCOL_FORMAT_NOUSE3,               //0x04
	USB_PROTOCOL_FORMAT_NOUSE4,               //0x05
	USB_PROTOCOL_FORMAT_NOUSE5,               //0x06
	USB_PROTOCOL_FORMAT_NOUSE6,               //0x07
	USB_PROTOCOL_FORMAT_NOUSE7,               //0x08
	USB_PROTOCOL_FORMAT_NOUSE8,               //0x09
	USB_PROTOCOL_FORMAT_GET_INDEX_LIST,       //0x0A
	USB_PROTOCOL_FORMAT_ENROLL_FINGER,        //0x0B
	USB_PROTOCOL_FORMAT_NOUSE11,              //0x0C
	       //0x0D
	
}USB_PROTOCOL_FORMAT_e;

typedef struct KEY_DATA_CONTROLLER
{
	volatile uint8_t *pData;
	volatile uint8_t rec_data_size;
	volatile DATA_RECV_STATE_e head_state_H;
	volatile DATA_RECV_STATE_e head_state_L;
	volatile DATA_RECV_STATE_e addr_state;
	volatile DATA_RECV_STATE_e data_state;	//��ʼ�������ݱ�־
	volatile uint16_t data_length;
}KEY_DATA_CONTROLLR_t;

typedef struct KEY_DATA_FORMAT
{
	volatile uint8_t head[2];
	volatile uint8_t addr;
	volatile uint8_t cmd;
	volatile uint8_t len;
	volatile uint8_t data[CH9329_TRANS_MAX_DATA_LEN];
	volatile uint8_t sum;	//sum = head[0] + head[1] + addr + cmd + len + data[...]
}KEY_DATA_FORMAT_t;


int Key_GiveNotifyFromISR(uint8_t *recData,uint8_t dataSize);
int Task_Key_DataCTLCreate(void);
int HID_Data_Handle(void);
#endif
