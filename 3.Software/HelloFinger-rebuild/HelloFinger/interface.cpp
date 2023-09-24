#include "interface.h"
#include <QtDebug>
#include "msg_handler.h"
#include "form_mainwindow.h"
#include "hid_function.h"

hid_device *usb_handle = NULL;
hid_device_info *usb_info = NULL;

int rec_num = 0;    //接收数据长度
uint8_t rec_buffer[REC_LEN] = {0};
uint8_t hid_command[SEND_LEN] = {0};


Msg_Handler *msgHandler = new Msg_Handler;

Interface::Interface(QObject *parent) : QThread(parent)
{
    stopped = false;
    Form_MainWindow *mainwindow = new Form_MainWindow;
    mainwindow->show();
    connect(msgHandler,&Msg_Handler::Signal_Update_TableState,mainwindow,&Form_MainWindow::Slot_Updata_TableState);
}

void Interface::run()
{

    while(1)
    {
        if(usb_handle == NULL)  //未连接
        {
            usb_info = hid_enumerate(PROTOCOL_VID,PROTOCOL_PID);
            if(usb_info == NULL)
            {
                qDebug() << "info get failed";
            }
            else
            {
                qDebug() << "info get success";
                for(;usb_info != nullptr;usb_info = usb_info->next)
                {
                       if(usb_info->interface_number == 3)//接口匹配
                       {
                           qDebug("interface_number:%s",usb_info->path);//打印地址
                           usb_handle = hid_open_path(usb_info->path);
                           HID_Send_Breath_RGB(usb_handle,0xFF,0xFF,0xFF,30);
                           break;
                       }
                }
                    /*释放链表*/
                hid_free_enumeration(usb_info);
            }
            msleep(1000);
        }
        else    //已连接
        {
            qDebug() << "connect ok";
            rec_num = hid_read_timeout(usb_handle,rec_buffer,REC_LEN,200);
            if(rec_num != -1)
            {
                msgHandler->Data_Resolve(rec_buffer);
            }
        }
        msleep(1000);
    }
}
