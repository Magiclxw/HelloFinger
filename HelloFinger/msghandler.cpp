#include "msghandler.h"
#include <QDebug>
#include <QWidget>
#include "entrance.h"
#include "mainwindow.h"
#include "hidapi.h"
#include "usbthread.h"
#include "string.h"
/* 处理USB接收数据 */

REC_DATA_FORMAT_t g_rec_data_format = {0};

extern uint8_t g_enroll_state;  //注册状态
extern struct hid_device_ *transhandle;
uint8_t Command[20];

uint8_t datalength; //hid数据长度
uint8_t checksum = 0;   //校验和
uint8_t TableState[8];  //数据：索引表存储状态

MsgHandler::MsgHandler()
{
}

/**
* @brief	验证校验和
* @param	接收数据
* @date		2023-5-1 19:48:17
* @return 	执行状态
*			- 0 验证失败
*			- 1	验证成功
*/
uint8_t CalcCheckSum(uint8_t *msg)
{
    uint8_t length = msg[0];    //获取接收长度
    for(int i = 1;i < length;i++){
        checksum += msg[i];
    }
    if(checksum == msg[length]){
        qDebug() << "compare ok" ;
        checksum = 0;
        return 1;
    }else{
        qDebug() << "compare error" ;
        checksum = 0;
        return 0;
    }
}

/**
* @brief	根据指令类型执行对应操作
* @param	接收数据
* @date		2023-5-1 19:50:01
* @return 	执行状态
*			- 0 指令识别失败
*			- others 验证成功
* @note
*/
uint8_t Handler(uint8_t *msg)
{
    qDebug() << "handler" ;
    datalength = msg[0];
    g_rec_data_format.cmd = msg[1];
    g_rec_data_format.data_len = msg[2];
    g_rec_data_format.type = msg[3];
    g_rec_data_format.result = msg[4];
    //g_rec_data_format.data = &msg[4];
    memcpy((uint8_t*)&g_rec_data_format.data, (uint8_t*)&msg[5],g_rec_data_format.data_len);
    g_rec_data_format.checksum = msg[g_rec_data_format.data_len];
    qDebug() << "length= " << datalength;
    qDebug() << "cmd= " << g_rec_data_format.cmd;

    switch (g_rec_data_format.type) {
    case TABLESTATE:    //数据为索引表信息
        for(int i=0;i<8;i++){
            TableState [i] = g_rec_data_format.data[i];  //+3：byte 0 是接收长度，byte 1 是指令码，byte 2是数据长度，byte 3 开始是数据
        }
        qDebug() << "tablestate" ;
        return TABLESTATE;
    case ENROLL:    //数据为指纹注册状态信息
    {
        g_enroll_state = msg[3];
        qDebug()<<"enroll_state:"<<g_enroll_state;
        return ENROLL;
    }
    case HEARTBEAT:
    {
        uint8_t cmd = USB_HEARTBEAT;
        GenerateCmd(&cmd,1);
        hid_write(transhandle,Command,CMDLEN);

    }
    default:
        return 0;
    }

}
void TableStateUpdate();


/* 生成HID通信指令 */
void GenerateCmd(uint8_t *data,uint8_t dataLen)
{
    uint8_t checksum = 0;
    uint8_t len = 0;
    Command[0] = 0x00;  //HID通信固定起始字节
    Command[1] = dataLen + 3;   //HID通信固定字节，通信数据长度
    Command[2] = RECEIVE;   //协议指令头
    Command[3] = dataLen;
    for(uint8_t i=4;i<dataLen+4;i++){
        Command[i] = data[i-4];
    }
    checksum = GenerateChecksum(Command,dataLen+3);     //获取校验位
    Command[dataLen+4] = checksum;

}

/* 生成校验位 */
uint8_t GenerateChecksum(uint8_t *cmd,uint8_t cmdLen) //cmdLen:指令长度，不包括固定头和固定长度（cmd[0]、cmd[1]）
{
    uint8_t checksum = 0;
    for(int i=2;i<cmdLen+2;i++){
        checksum += cmd[i];
    }
    return checksum;
}
