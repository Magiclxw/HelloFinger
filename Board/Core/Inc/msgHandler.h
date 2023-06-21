#ifndef __MSGHANDLER_H
#define __MSGHANDLER_H

#include "stm32f1xx.h"
/*****************************************************************************/
/*                                USBͨ����غ�                              */

#define RECEIVE 0xFE	//��λ���·�����
#define PROTOCOL 0x57	//Э�鴫��ָ��ͷ
#define USB_TRANSMIT 0x01		//͸��ģʽ
#define USB_COMMAND	 0x02		//Э�鴫��ģʽ
#define USB_TABLESTATE 0x10	//��ȡ������״̬
#define USB_ENROLL		0x11	//ע��ָ��
#define USB_IDENTIFY	0x12
#define USB_DELETE		0x14

/* Э�鴫����������� */
#define PRO_GET_INFO	0x81
#define PRO_READ_PARA	0x88
#define PRO_SET_PARA	0x89
#define PRO_HID_DATA	0x87	//HIDͨ��������
#define PRO_GET_TABLESTATE	0x10	//��ȡ������״̬
#define PRO_ENROLL	0x11	//ע��ָ��
#define PRO_DELETE	0x14
#define PRO_STORE_FUNC	0x15	//�洢�˺�/����/��ݼ�

/****************************************************************************/
/*                               ָ��ģ��ͨ����غ�                         */





/****************************************************************************/



uint8_t GenerateProtocolCMD(uint8_t *data,uint8_t cmdLen);
void USB_Handler(uint8_t *data);
void FPM383_Handler(uint8_t *data);
#endif
