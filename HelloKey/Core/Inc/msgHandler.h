#ifndef __MSGHANDLER_H
#define __MSGHANDLER_H

#include "stm32f1xx.h"

#define RECEIVE 0xFE	//上位机下发数据
#define USB_TRANSMIT 0x01		//透传模式
#define USB_COMMAND	 0x02		//协议传输模式
#define USB_TABLESTATE 0x10	//获取索引表状态

void Handler(uint8_t *data);
#endif
