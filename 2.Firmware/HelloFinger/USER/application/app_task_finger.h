#ifndef __APP_TASK_FINGER_H
#define __APP_TASK_FINGER_H
#include "sys_config.h"
#include "drv_fpm383.h"

#define FINGER_CMD_HEAD_H	(0xEF)
#define FINGER_CMD_HEAD_L	(0x01)
#define FINGER_CMD_ADDR_1	(0xFF)
#define FINGER_CMD_ADDR_2	(0xFF)
#define FINGER_CMD_ADDR_3	(0xFF)
#define FINGER_CMD_ADDR_4	(0xFF)

#define TASK_FINGER_CONTROL_SIZE	(200)
#define TASK_FINGER_CONTROL_PRIORITY	(13)
#define REC_MAX_DATA_LEN	(100)	//接收数据部分最大字节数
#define FINGER_DATA_HANDLE_QUEUE_LEN	(10)
#define FINGER_DATA_HANDLE_QUEUE_SIZE	(1)


typedef struct FINGER_DATA_CONTROLLER
{
	volatile uint8_t *pData;
	volatile uint8_t rec_data_size;
	volatile DATA_RECV_STATE_e head_state_H;
	volatile DATA_RECV_STATE_e head_state_L;
	volatile DATA_RECV_STATE_e addr_state_1;
	volatile DATA_RECV_STATE_e addr_state_2;
	volatile DATA_RECV_STATE_e addr_state_3;
	volatile DATA_RECV_STATE_e addr_state_4;
	volatile DATA_RECV_STATE_e data_state;	//开始接收数据标志
	volatile uint16_t data_length;
}FINGER_DATA_CONTROLLR_t;

typedef struct FINGER_DATA_FORMAT
{
	volatile uint8_t head[2];
	volatile uint8_t addr[4];
	volatile uint8_t type;
	volatile uint8_t len[2];
	volatile uint8_t data[REC_MAX_DATA_LEN];
}FINGER_DATA_FORMAT_t;

#define USB_RESPONSE_HEAD	0xFE


typedef struct USB_RESPONSE
{
	volatile uint8_t head;
	volatile uint8_t len;
	volatile uint8_t type;
	volatile uint8_t result;
	volatile uint8_t data[61];
}USB_RESPONSE_t;

extern USB_RESPONSE_t g_usb_response;

int Task_Finger_DataCTLCreate(void);
int Finger_GiveNotifyFromISR(uint8_t *recData,uint8_t dataSize);
int Finger_TouchNotifyFromISR(void);
static void Finger_Function(uint16_t id,uint16_t score);
#endif

