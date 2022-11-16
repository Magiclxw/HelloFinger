#include "entrance.h"
#include "ui_entrance.h"
#include "hidapi.h"
#include <QtDebug>
#include "usbthread.h"
#include <QMessageBox>
#include <QElapsedTimer>

/*板子上电默认处于协议传输模式*/


struct hid_device_ *handle;
struct hid_device_ *transhandle = NULL;    //透传句柄

USBTHREAD *usbthread = new USBTHREAD;

/*协议传输ID*/
uint16_t Protocol_VID = 0x1A86;
uint16_t Protocol_PID = 0xE129;
/*透传ID*/
uint16_t Transmission_VID = 0x1A86;
uint16_t Transmission_PID = 0xE429;

uint8_t Msg[6] = {0x00,0x04};   //保存下传数据

Entrance::Entrance(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Entrance)
{
    ui->setupUi(this);

    hid_device_info *hid_info;

    hid_info = hid_enumerate(Protocol_VID,Protocol_PID);


    if(hid_info == NULL){
        QMessageBox::critical(this,"连接失败","尝试重新插拔设备！");
        qDebug() << "连接失败";
        while(1){
            hid_info = hid_enumerate(Protocol_VID,Protocol_PID);
            if(hid_info != NULL) break;
            qDebug() << "重新连接";
        }
    }

    for(;hid_info != nullptr;hid_info = hid_info->next){
           if(hid_info->interface_number == 3)//接口匹配
           {
               qDebug("interface_number:%s",hid_info->path);//打印地址
               break;
           }
    }
        /*释放链表*/
        //hid_free_enumeration(hid_info);

    handle = hid_open_path(hid_info->path);

    hid_free_enumeration(hid_info);

    if(handle == NULL){
        qDebug() << "HID Open Failed";
    }else{
        qDebug() << "HID Open Success";
    }

/*****************************测试功能*************************************/
    connect(ui->pushButton,&QPushButton::clicked,this,[=](){
        //Msg[0] = 0x00;
        //Msg[1] = 0x04;
        Msg[2] = 0xFE;
        Msg[3] = 0x01;
        Msg[4] = 0x01;
        Msg[5] = 0xFF;

        int i=hid_write(handle,Msg,6);
        qDebug() << i;

        if(i>0){
            hid_close(handle);
            usbthread->start();
        }
    });
/*************************************************************************/

}

Entrance::~Entrance()
{
    delete ui;
}

