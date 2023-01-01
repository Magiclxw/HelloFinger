#ifndef __MSGHANDLER_H
#define __MSGHANDLER_H

#include "stm32f1xx.h"

#define RECEIVE 0xFE	//��λ���·�����
#define USB_TRANSMIT 0x01		//͸��ģʽ
#define USB_COMMAND	 0x02		//Э�鴫��ģʽ
#define USB_TABLESTATE 0x10	//��ȡ������״̬
#define USB_ENROLL		0x11	//ע��ָ��
#define USB_IDENTIFY	0x12

uint8_t Calc_Checksum(uint8_t *data);
void Handler(uint8_t *data);
#endif
