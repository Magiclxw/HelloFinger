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
#include "usbdevice.h"
#include "hidewindow.h"
#include "enrollstate.h"

/*板子上电默认处于协议传输模式*/

extern uint8_t Command[20];

struct hid_device_ *handle = NULL;
struct hid_device_ *transhandle = NULL;    //透传句柄
hid_device_info *hid_info = NULL;
USBTHREAD *usbthread = new USBTHREAD;
uint8_t runningstate = PROTOCOLSTATE;   //当前状态，默认处于协议传输状态
uint8_t table_state_flag = 0;       //索引表获取（更新）标志，0：索引表未获取  1：索引表已获取

/*协议传输ID*/
uint16_t Protocol_VID = 0x1A86;
uint16_t Protocol_PID = 0xE129;
/*透传ID*/
uint16_t Transmission_VID = 0x1A86;
uint16_t Transmission_PID = 0xE429;

uint8_t infoFlag = 0;   //获取信息成功标志
uint8_t interfaceFlag = 0;  //获取指定接口信息成功标志
uint8_t openFlag = 0;   //打开接口成功标志
uint8_t waitingSwitchFlag = 0;      //等待转换传输模式标志    0：未等待模式转换   1：等待模式转换
uint8_t timerCount = 0;
uint8_t Msg[6] = {0x00,0x04};   //保存下传数据
MainWindow *m;
HideWindow *hidewindow;

QTimer *progress_timer = new QTimer;

Entrance::Entrance(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Entrance)
{
    ui->setupUi(this);
    this->setFixedSize(300,100);
    this->setWindowTitle("HelloFinger");
    m = new MainWindow;             //创建主窗口
    hidewindow = new HideWindow;    //创建自动隐藏窗口
    hidewindow->show();

    USBDEVICE *usbdevice = new USBDEVICE(this);
    usbdevice->registerDevice(this->winId());
    qApp->installNativeEventFilter(usbdevice);

    connect(usbdevice,SIGNAL(deviceIn(QString,QString)),this,SLOT(onDeviceIn(QString,QString)));
    connect(usbdevice,SIGNAL(deviceOut(QString,QString)),this,SLOT(onDeviceOut(QString,QString)));

/* 若进度条满，则隐藏进度条窗口 */
    connect(ui->progressBar,&QProgressBar::valueChanged,this,&Entrance::SL_HideWindow);

/* 进度条定时器 */
    progress_timer->start(10);
    connect(progress_timer,&QTimer::timeout,this,&Entrance::ProgressCtrl);

/* 定时发送获取索引表状态指令 */
    connect(cmdtimer,&QTimer::timeout,this,&Entrance::SL_GetTableState);

/******************************************** 建立连接过程 *************************************************/
/*  1、获取设备信息 */
    hid_info = hid_enumerate(Protocol_VID,Protocol_PID);

    if(hid_info == NULL){
        infoFlag = 0;
        qDebug() << "获取信息失败";
    }else{
        infoFlag = 1;
        ui->progressBar->setStyleSheet("QProgressBar{background:write;} QProgressBar::chunk{background:green}");
        qDebug() << "获取信息成功";
    }

/* 2、获取指定接口 */
    for(;hid_info != nullptr;hid_info = hid_info->next){
           if(hid_info->interface_number == 3)//接口匹配
           {
               qDebug("interface_number:%s",hid_info->path);//打印地址
               interfaceFlag = 1;
               ui->progressBar->setStyleSheet("QProgressBar{background:write;} QProgressBar::chunk{background:green}");
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
        ui->progressBar->setStyleSheet("QProgressBar{background:write;} QProgressBar::chunk{background:green}");
        hid_free_enumeration(hid_info);
        qDebug() << "HID Open Success";
    }
    if(handle != NULL){
//        uint8_t cmd[1] = {TRANSMISSIONSTATE};
//        GenerateCmd(cmd,1);
//        hid_write(handle,Command,CMDLEN);   //发送切换为透传状态指令
//        waitingSwitchFlag = 1;
//        memset(Command,0,20);
        usbthread->start();
        cmdtimer->start(1000);
    }
/********************************************************************************************************/


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
    connect(usbthread,&USBTHREAD::SI_EnrollStateUpdate,m,&MainWindow::SL_EnrollStateUpdate);
    connect(m,&MainWindow::SI_AddFinger,this,[=](uint8_t id,uint8_t times,uint8_t *param){
        uint8_t cmd[6] = {USB_ENROLL,0x00,id,times,param[0],param[1]};
        GenerateCmd(cmd,6);
        hid_write(handle,Command,11);  //cmd:6 + head:4 + tail:1
        memset(Command,0,20);
        //table_state_flag = 0;
        //cmdtimer->start(1000);

    });

    connect(m,&MainWindow::SI_FingerDelete,this,[=](uint8_t ID){
        uint8_t cmd[5] = {USB_DELETE,0x00,ID,0x00,0x01};
        GenerateCmd(cmd,5);
        hid_write(handle,Command,10);
        memset(Command,0,20);
        table_state_flag = 0;
        cmdtimer->start(1000);

    });

    connect(m,&MainWindow::SI_FingerRefresh,this,[=](){
        table_state_flag = 0;
        cmdtimer->start(1000);
    });

    connect(m,&MainWindow::SI_USB_SEND_WindowsPassword,this,[=](QString password){
        /* 转换为字符数组 */
        QByteArray ba_password = password.toLatin1();
        char *c_password = ba_password.data();

        uint8_t flag = USB_FUNC_STORE;
        uint8_t type = TYPE_Windows_Password;
        uint8_t len = password.length();    //获取密码长度
        uint8_t cmdLen = len+3+1;
        uint8_t *cmd = new uint8_t[cmdLen];
        cmd[0] = flag;
        cmd[1] = type;
        cmd[2] = len;

        for (uint8_t i=3;i < len+3 ; i++) {
            cmd[i] = c_password[i-3];
        }

        GenerateCmd(cmd,cmdLen);

        //hid_write(handle,Command,cmdLen+5);

        QByteArray tmp = QByteArray((char*)Command,cmdLen+5);
        qDebug() << "command = " << tmp.toHex();
        //qDebug()<<"len" << len;
        //hid_write(handle,,)
    });

}

void Entrance::ProgressCtrl()
{
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
        progress_timer->stop();
    }
    ui->progressBar->setValue(timerCount);
    timerCount++;

}

void Entrance::SL_HideWindow()
{
    if(ui->progressBar->value() == 100){
        m->show();
        this->hide();
    }
}

void Entrance::SL_GetTableState()
{
    if(handle != NULL){
        qDebug() << "cmdtimer";
        uint8_t cmd[1] = {USB_TABLESTATE};
        GenerateCmd(cmd,1);
        if(table_state_flag == 1){
            cmdtimer->stop();
            return;
        }
        hid_write(handle,Command,6);   //发送获取索引表状态指令
        memset(Command,0,20);
    }
}


//void Entrance::GenerateCmd(int cmd)
//{
//    uint8_t checksum = 0;
//    Command[0] = 0x00;
//    Command[1] = 4;
//    Command[2] = RECEIVE;
//    Command[3] = DATALEN;
//    Command[4] = cmd;
//    checksum = GenerateChecksum(Command);
//    Command[5] = checksum;
//}

void Entrance::onDeviceIn(QString VID, QString PID)
{
    QString vid;
    QString pid;
    qDebug()<<"设备已插入"<<"VID:"<<VID<<"PID:"<<PID;
    vid=VID.right(4);
    pid=PID.right(4);
    qDebug()<<vid;
    qDebug()<<pid;
    bool ok;
    if(vid.toInt(&ok,16)==Protocol_VID && pid.toInt(&ok,16)==Protocol_PID && waitingSwitchFlag == 0)
    {
        qDebug() << "In ";
        while(hid_info == NULL){
            hid_info = hid_enumerate(Protocol_VID,Protocol_PID);

            if(hid_info == NULL){
                infoFlag = 0;
                qDebug() << "获取信息失败";
            }else{
                infoFlag = 1;
                ui->progressBar->setStyleSheet("QProgressBar{background:write;} QProgressBar::chunk{background:green}");
                qDebug() << "获取信息成功";
                //break;
            }
            if(infoFlag == 1){
                for(;hid_info != nullptr;hid_info = hid_info->next){
                    if(hid_info->interface_number == 3)//接口匹配
                    {
                        qDebug("interface_number:%s",hid_info->path);//打印地址
                        interfaceFlag = 1;
                        ui->progressBar->setStyleSheet("QProgressBar{background:write;} QProgressBar::chunk{background:green}");
                        break;
                    }else{
                        interfaceFlag = 0;
                    }
                }
            }
        }


        if(infoFlag == 1 && interfaceFlag == 1){
            handle = hid_open_path(hid_info->path);
        }

        if(handle == NULL){
            qDebug() << "HID Open Failed";
        }else{
            openFlag = 1;
            ui->progressBar->setStyleSheet("QProgressBar{background:write;} QProgressBar::chunk{background:green}");
            hid_free_enumeration(hid_info);
            //hid_close(handle);
            //usbthread->start();
            runningstate = PROTOCOLSTATE;
            qDebug() << "HID Open Success";
            waitingSwitchFlag = 1;
        }

    }else if(vid.toInt(&ok,16)==Transmission_VID && pid.toInt(&ok,16)==Transmission_PID){
        if(waitingSwitchFlag == 1){
            qDebug() << "enter transmission";
            hid_close(handle);
            qDebug() << "enter transmission";
            usbthread->start();
            cmdtimer->start(1000);
            waitingSwitchFlag = 0;

        }else{
            qDebug() << "尚未完成握手";
        }

    }

}


void Entrance::onDeviceOut(QString VID, QString PID)
{
    QString vid;
    QString pid;
    qDebug()<<"设备已拔出"<<"VID:"<<VID<<"PID:"<<PID;
    vid=VID.right(4);
    pid=PID.right(4);
    qDebug()<<vid;
    qDebug()<<pid;
    bool ok;
    if( vid.toInt(&ok,16)==Protocol_VID && pid.toInt(&ok,16)==Protocol_PID )
    {
//        usbthread->stop();
//        transhandle = NULL;
        hid_info = NULL;
        handle = NULL;
        //waitingSwitchFlag = 0;
        qDebug()<<"thread stop";
    }else if(vid.toInt(&ok,16)==Transmission_VID && pid.toInt(&ok,16)==Transmission_PID){
        cmdtimer->stop();
        usbthread->stop();
        transhandle = NULL;
        waitingSwitchFlag = 0;
    }
}


Entrance::~Entrance()
{
    delete ui;
}

