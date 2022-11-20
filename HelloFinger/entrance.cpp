#include "entrance.h"
#include "ui_entrance.h"
#include "hidapi.h"
#include <QtDebug>
#include "usbthread.h"
#include <QMessageBox>
#include <QElapsedTimer>
#include <QTimer>
#include "mainwindow.h"
#include "msghandler.h"

/*板子上电默认处于协议传输模式*/


struct hid_device_ *handle = NULL;
struct hid_device_ *transhandle = NULL;    //透传句柄
USBTHREAD *usbthread = new USBTHREAD;

/*协议传输ID*/
uint16_t Protocol_VID = 0x1A86;
uint16_t Protocol_PID = 0xE129;
/*透传ID*/
uint16_t Transmission_VID = 0x1A86;
uint16_t Transmission_PID = 0xE429;
uint8_t infoFlag = 0;   //获取信息成功标志
uint8_t interfaceFlag = 0;  //获取指定接口信息成功标志
uint8_t openFlag = 0;   //打开接口成功标志
uint8_t timerCount = 0;
uint8_t Msg[6] = {0x00,0x04};   //保存下传数据

Entrance::Entrance(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Entrance)
{
    ui->setupUi(this);
    this->setFixedSize(300,100);
    this->setWindowTitle("HelloFinger");
    MainWindow *m = new MainWindow;

/* 等待进度条满 */
    connect(ui->progressBar,&QProgressBar::valueChanged,[=](){
        if(ui->progressBar->value() == 100){
            m->show();
            //this->hide();
        }
    });

    QTimer *timer = new QTimer;
    timer->start(10);
    connect(timer,&QTimer::timeout,[=](){
        if(timerCount == 30 && infoFlag == 0){
            timerCount = 29;
            ui->progressBar->setStyleSheet("QProgressBar{background:write;} QProgressBar::chunk{background:red}");
        }
        if(timerCount == 60 && interfaceFlag == 0){
            timerCount = 59;
            ui->progressBar->setStyleSheet("QProgressBar{background:write;} QProgressBar::chunk{background:red}");
        }
        if(timerCount == 90 && openFlag == 0){
            timerCount = 89;
            ui->progressBar->setStyleSheet("QProgressBar{background:write;} QProgressBar::chunk{background:red}");
        }
        if(timerCount == 100){
            timer->stop();
        }
        ui->progressBar->setValue(timerCount);
        timerCount++;

    });
    hid_device_info *hid_info;
/*  1、获取设备信息 */
    hid_info = hid_enumerate(Protocol_VID,Protocol_PID);

    if(hid_info == NULL){
        qDebug() << "获取信息失败";
    }else{
        infoFlag = 1;
        qDebug() << "获取信息成功";
    }

/* 2、获取指定接口 */
    for(;hid_info != nullptr;hid_info = hid_info->next){
           if(hid_info->interface_number == 3)//接口匹配
           {
               qDebug("interface_number:%s",hid_info->path);//打印地址
               interfaceFlag = 1;
               break;
           }
    }
        /*释放链表*/
        //hid_free_enumeration(hid_info);

/* 3、打开设备接口 */
    if(infoFlag == 1 && interfaceFlag == 1){
        handle = hid_open_path(hid_info->path);
    }

    if(handle == NULL){
        qDebug() << "HID Open Failed";
    }else{
        openFlag = 1;
        hid_free_enumeration(hid_info);
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

    connect(usbthread,&USBTHREAD::SI_TableStateUpdate,m,&MainWindow::SL_TableStateUpdate);
}

Entrance::~Entrance()
{
    delete ui;
}

