#ifndef __MSGHANDLER_H
#define __MSGHANDLER_H

#include "stm32f1xx.h"

#define RECEIVE 0xFE	//��λ���·�����
#define USB_TRANSMIT 0x01		//͸��ģʽ
#define USB_COMMAND	 0x02		//Э�鴫��ģʽ
#define USB_TABLESTATE 0x10	//��ȡ������״̬

void Handler(uint8_t *data);
#endif
