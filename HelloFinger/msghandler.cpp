#include "msghandler.h"
#include <QDebug>
#include <QWidget>
#include "entrance.h"
#include "mainwindow.h"
#include "hidapi.h"
#include "usbthread.h"
#include "string.h"
/* 处理USB接收数据 */

REC_DATA_CTL_t g_rec_data_ctl = {0};
REC_DATA_FORMAT_t g_rec_data_format = {0};


extern uint8_t g_enroll_param[2];
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

        qDebug() << "compare ok"  << "calc checksum = " << checksum << "rec checksum = " << msg[length];;
        checksum = 0;
        return 1;
    }else{
        qDebug() << "compare error" << "calc checksum = " << checksum << "rec checksum = " << msg[length];
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
    case USB_PROTOCOL_FORMAT_GET_INDEX_LIST:    //数据为索引表信息
        for(int i=0;i<8;i++){
            TableState [i] = g_rec_data_format.data[i];  //FPM383C索引表仅前8byte有效
        }
        qDebug() << "tablestate" ;
        return USB_PROTOCOL_FORMAT_GET_INDEX_LIST;
    case USB_PROTOCOL_FORMAT_ENROLL_FINGER:    //数据为指纹注册状态信息
    {
        if(g_rec_data_format.result == CONFIRM_OK)  //执行结果正确
        {
            memcpy(g_enroll_param,(uint8_t*)&g_rec_data_format.data,2);

        }
        else    //执行结果错误
        {

        }
        qDebug()<<"enroll_state:"<<g_enroll_param;
        return USB_PROTOCOL_FORMAT_ENROLL_FINGER;
    }
    case USB_PROTOCOL_FORMAT_DELETE_FINGER:
    {
        qDebug() << "finger delete ok";
        return USB_PROTOCOL_FORMAT_DELETE_FINGER;
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

    Command[0] = 0x00;  //HID通信固定起始字节
    Command[1] = dataLen + 3;   //HID通信固定字节，通信数据长度
    Command[2] = HID_CMD_HEAD;   //协议指令头
    Command[3] = dataLen;

    memcpy(&Command[4],data,dataLen);

    checksum = GenerateChecksum(&Command[2],dataLen+2);     //获取校验位
    Command[dataLen+4] = checksum;

}

/* 生成校验位 */
uint8_t GenerateChecksum(uint8_t *cmd,uint8_t cmdLen) //cmdLen:指令长度，不包括固定头和固定长度（cmd[0]、cmd[1]）
{
    uint8_t checksum = 0;
    for(int i=0;i<cmdLen;i++){
        checksum += cmd[i];
    }
    return checksum;
}

void Reset_Rec_Data(void)
{
    memset(&g_rec_data_ctl,0,sizeof(REC_DATA_CTL_t));
    g_rec_data_ctl.pData = (uint8_t*)&g_rec_data_format;
}

int Rec_Data_Handle(uint8_t * msg)
{
    uint8_t data = msg[1];  //msg[0]为数据长度，msg[1]为数据
    if(g_rec_data_ctl.cmd_state == DATA_RECV_STATE_NO_GET)
    {
        if(data == HID_CMD_HEAD)
        {
            g_rec_data_ctl.cmd_state = DATA_RECV_STATE_GET;
            *g_rec_data_ctl.pData = data;
            g_rec_data_ctl.pData ++;
            g_rec_data_ctl.rec_data_size++;
        }
        else
        {
            Reset_Rec_Data();
        }
    }
    else
    {
        if(g_rec_data_ctl.rec_data_size < 4)
        {
            *g_rec_data_ctl.pData = data;
            g_rec_data_ctl.pData ++;
            g_rec_data_ctl.rec_data_size++;
        }
        else if(g_rec_data_ctl.rec_data_size == 4)
        {
            g_rec_data_ctl.data_state = DATA_RECV_STATE_GET;
            g_rec_data_ctl.data_length = g_rec_data_format.data_len;
            g_rec_data_ctl.rec_data_size++;
        }
        if( g_rec_data_ctl.data_state == DATA_RECV_STATE_GET)
        {
            if(g_rec_data_ctl.data_length)
            {
                g_rec_data_ctl.data_length--;
                *g_rec_data_ctl.pData = data;
                g_rec_data_ctl.pData++;
            }
            else
            {
                *g_rec_data_ctl.pData = data;

            }
        }
    }
}
