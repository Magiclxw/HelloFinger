#include "usbthread.h"
#include "entrance.h"
#include "hidapi.h"
#include <QDebug>
#include "msghandler.h"

extern struct hid_device_ *handle;
extern struct hid_device_ *transhandle;

extern uint16_t Transmission_VID;
extern uint16_t Transmission_PID;

extern uint8_t table_state_flag;


uint8_t rec;
uint8_t rec_buffer[20]; //接收缓冲区
uint8_t returnFlag=0;
QByteArray rec_buffer_arry;

USBTHREAD::USBTHREAD(QObject *parent) : QThread(parent)
{
    stopped = false;
}

void USBTHREAD::run()
{
    qDebug() << "IN Thread";
    stopped = false;
    /* 开启透传 */
    if(transhandle == NULL){
        while(1){
            transhandle = hid_open(Transmission_VID,Transmission_PID,NULL);
            qDebug("thread1 NULL");
            if(transhandle != NULL) break;
            msleep(1000);
        }
        qDebug() << "leave thread1";
        qDebug() << "stopped=" << stopped;
    }

    while(!stopped){
        if(transhandle == NULL){
            while(1){
                transhandle = hid_open(Transmission_VID,Transmission_PID,NULL);
                qDebug("thread2 NULL");
                if(transhandle != NULL) break;
                msleep(5000);
            }
        }
        rec = hid_read_timeout(transhandle,rec_buffer,20,1000);     //接收第一字节为后续数据长度
        rec_buffer_arry = QByteArray((char*)rec_buffer,20);

        if(!CalcCheckSum(rec_buffer)){  //判断校验位
            continue;
        }

        if(rec != 0){       //接受数据非空
            qDebug() << "Receive num:" << rec;
            qDebug() << "rec_buffer:" << rec_buffer[0];
            qDebug() << "Receive data" << rec_buffer_arry.toHex();

            returnFlag = Handler(rec_buffer);   //判断指令类型
            switch (returnFlag){
            case TABLESTATE:
                emit SI_TableStateUpdate();
                table_state_flag = 1;
                break;
            case ENROLL:
                emit SI_EnrollStateUpdate();
            default:
                break;
            }

            memset(rec_buffer,0,20);
        }



    }
}

void USBTHREAD::stop()
{
    stopped = true;
}

//void USBTHREAD::start()
//{
//    stopped = false;
//}
