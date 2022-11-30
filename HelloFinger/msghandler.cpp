#include "msghandler.h"
#include <QDebug>
#include <QWidget>
#include "entrance.h"

/* 处理USB接收数据 */

uint8_t length; //数据长度
uint8_t head;   //指令码
uint8_t checksum = 0;   //校验和
uint8_t TableState[8];  //数据：索引表存储状态

MsgHandler::MsgHandler()
{
}

uint8_t CalcCheckSum(uint8_t *msg)
{
    uint8_t length = msg[0];    //获取接收长度
    for(int i = 1;i < length;i++){
        checksum += msg[i];
    }
    if(checksum == msg[length]){
        qDebug() << "验证成功" ;
        checksum = 0;
        return 1;
    }else{
        qDebug() << "验证失败" ;
        checksum = 0;
        return 0;
    }
}

uint8_t Handler(uint8_t *msg)
{
    qDebug() << "handler" ;
    length = msg[0];
    head = msg[1];
    qDebug() << "length= " << length;
    qDebug() << "head= " << head;
    switch (head) {
    case TABLESTATE:
        for(int i=0;i<8;i++){
            TableState [i] = msg[i+3];  //+3：byte 0 是接收长度，byte 1 是指令码，byte 2是数据长度，byte 3 开始是数据
        }
        qDebug() << "tablestate" ;
        return TABLESTATE;
        break;
    default:
        break;
    }
    return 0;
}
void TableStateUpdate();
