#include "usbthread.h"
#include "entrance.h"
#include "hidapi.h"
#include <QDebug>
#include "msghandler.h"

extern struct hid_device_ *handle;
extern struct hid_device_ *transhandle;

extern uint16_t Transmission_VID;
extern uint16_t Transmission_PID;

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

    /* 开启透传 */
    if(transhandle == NULL){
        while(1){
            transhandle = hid_open(Transmission_VID,Transmission_PID,NULL);
            qDebug("thread NULL");
            if(transhandle != NULL) break;
            msleep(1000);
        }
    }

    while(!stopped){
        if(transhandle == NULL){
            while(1){
                transhandle = hid_open(Transmission_VID,Transmission_PID,NULL);
                qDebug("thread NULL");
                if(transhandle != NULL) break;
                msleep(1000);
            }
        }
        rec = hid_read_timeout(transhandle,rec_buffer,20,1000);     //接收第一字节为后续数据长度
        rec_buffer_arry = QByteArray((char*)rec_buffer,20);
        qDebug() << "Receive num:" << rec;
        qDebug() << "rec_buffer:" << rec_buffer[0];
        qDebug() << "Receive data" << rec_buffer_arry;

        if(!CalcCheckSum(rec_buffer)){
            continue;
        }

        returnFlag = Handler(rec_buffer);
        switch (returnFlag){
        case TABLESTATE:
            emit SI_TableStateUpdate();
            break;

        default:
            break;
        }

        memset(rec_buffer,0,20);
    }
}

void USBTHREAD::stop()
{
    stopped = true;
}
