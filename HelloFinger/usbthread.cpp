#include "usbthread.h"
#include "entrance.h"
#include "hidapi.h"
#include <QDebug>

extern struct hid_device_ *handle;
extern struct hid_device_ *transhandle;

extern uint16_t Transmission_VID;
extern uint16_t Transmission_PID;

uint8_t rec;
uint8_t rec_buffer[20];

USBTHREAD::USBTHREAD(QObject *parent) : QThread(parent)
{
    stopped = false;
}

void USBTHREAD::run()
{
    qDebug() << "IN Thread";
    if(transhandle == NULL){
        while(1){
            transhandle = hid_open(Transmission_VID,Transmission_PID,NULL);
            qDebug("thread NULL");
            if(transhandle != NULL) break;
            msleep(1000);
        }
    }

    while(!stopped){
        rec = hid_read_timeout(transhandle,rec_buffer,20,1000);

        qDebug() << "Receive num:" << rec;
        qDebug() << "Receive data" << rec_buffer;
    }


}
