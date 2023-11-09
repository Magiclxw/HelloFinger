#include "msg_handler.h"
#include "interface.h"
#include "config/sys_config.h"
#include <QDebug>

REC_DATA_FORMAT_t g_rec_data_format;
uint8_t TableState[8] = {0};

Msg_Handler::Msg_Handler(QObject *parent) : QObject(parent)
{

}

/**
*@brief	比较校验和
*@param	-msg：待校验数据
*@return 执行状态
*/
int Msg_Handler::Comp_CheckSum(uint8_t *msg)
{
    uint8_t length = msg[0];    //获取接收长度
    uint8_t checkSum = 0;
    for(int i = 1;i < length;i++){
        checkSum += msg[i];
    }
    if(checkSum == msg[length]){
        qDebug() << "compare ok"  << "calc checksum = " << checkSum << "rec checksum = " << msg[length];;
        return OPERATE_SUCCESS;
    }else{
        qDebug() << "compare error" << "calc checksum = " << checkSum << "rec checksum = " << msg[length];
        return OPERATE_ERROR_INVALID_PARAMETERS;
    }

}


/**
*@brief	HID数据处理
*@param	-data:接收数据指针
*@return 执行状态
*/
int Msg_Handler::Data_Resolve(uint8_t *data)
{
    uint8_t datalength = 0; //hid数据长度
    datalength = data[0];   //hid数据中第一个字节代表后续数据长度
    g_rec_data_format.cmd = data[1];
    g_rec_data_format.data_len = data[2];
    g_rec_data_format.type = data[3];
    g_rec_data_format.result = data[4];

    memcpy((uint8_t*)&g_rec_data_format.data, (uint8_t*)&data[5],g_rec_data_format.data_len);
    g_rec_data_format.checksum = data[g_rec_data_format.data_len];
    switch (g_rec_data_format.type)
    {
    case USB_PROTOCOL_FORMAT_GET_INDEX_LIST:    //数据为索引表信息
    {
        //uint8_t *TableState = new uint8_t[8];
        for(int i=0;i<8;i++){
            TableState [i] = g_rec_data_format.data[i];  //FPM383C索引表仅前8byte有效
        }
        qDebug() << "tablestate" ;
        emit Signal_Update_TableState();
        break;
    }
    case USB_PROTOCOL_FORMAT_ENROLL_FINGER:    //数据为指纹注册状态信息
    {
        if(g_rec_data_format.result == CONFIRM_OK)  //执行结果正确
        {
            uint8_t enrollState[2] = {0};
            memcpy(enrollState,(uint8_t*)&g_rec_data_format.data,2);
            qDebug()<<"enroll_state:"<<enrollState;
            emit Signal_Update_EnrollState(enrollState[0],enrollState[1]);
        }
        else    //执行结果错误
        {

        }
        break;
    }
    case USB_PROTOCOL_FORMAT_DELETE_FINGER:
    {
        qDebug() << "finger delete ok";
        //emit mainwindow->Signal_RefreshFinger();
        break;
    }
    case USB_PROTOCOL_FORMAT_GET_FW_HW:
    {
        if(g_rec_data_format.result == CONFIRM_OK)  //执行结果正确
        {
            char compile_date[21] = {0};
            char version[16] = {0};
            memcpy(compile_date,(uint8_t*)&g_rec_data_format.data[0],19);
            memcpy(version,(uint8_t*)&g_rec_data_format.data[19],15);
            compile_date[20] = 0;
            version[15] = 0;
            qDebug()<<"date:"<<compile_date;
            qDebug()<<"version:"<<version;
            emit Signal_Update_Firmware_Msg(compile_date,version);
        }
        else    //执行结果错误
        {

        }
        break;
    }
    default:
        return OPERATE_ERROR_INVALID_PARAMETERS;
    }
    memset(rec_buffer,0,REC_LEN);
    return OPERATE_SUCCESS;
}



