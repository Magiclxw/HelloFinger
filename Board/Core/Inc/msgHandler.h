#ifndef __MSGHANDLER_H
#define __MSGHANDLER_H

#include "stm32f1xx.h"
/*****************************************************************************/
/*                                USB通信相关宏                              */

#define RECEIVE 0xFE	//上位机下发数据
#define PROTOCOL 0x57	//协议传输指令头
#define USB_TRANSMIT 0x01		//透传模式
#define USB_COMMAND	 0x02		//协议传输模式
#define USB_TABLESTATE 0x10	//获取索引表状态
#define USB_ENROLL		0x11	//注册指纹
#define USB_IDENTIFY	0x12
#define USB_DELETE		0x14

/* 协议传输接收命令码 */
#define PRO_GET_INFO	0x81
#define PRO_READ_PARA	0x88
#define PRO_SET_PARA	0x89
#define PRO_HID_DATA	0x87	//HID通信命令码
#define PRO_GET_TABLESTATE	0x10	//获取索引表状态
#define PRO_ENROLL	0x11	//注册指纹
#define PRO_DELETE	0x14
#define PRO_STORE_FUNC	0x15	//存储账号/密码/快捷键

/****************************************************************************/
/*                               指纹模块通信相关宏                         */





/****************************************************************************/



uint8_t GenerateProtocolCMD(uint8_t *data,uint8_t cmdLen);
void USB_Handler(uint8_t *data);
void FPM383_Handler(uint8_t *data);
#endif
