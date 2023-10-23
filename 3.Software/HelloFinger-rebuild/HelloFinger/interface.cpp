#include "interface.h"

hid_device *usb_handle = NULL;
hid_device_info *usb_info = NULL;

int rec_num = 0;    //接收数据长度
uint8_t rec_buffer[REC_LEN] = {0};
uint8_t hid_command[SEND_LEN] = {0};


Msg_Handler *msgHandler = NULL;
Form_MainWindow *mainwindow = NULL;

Interface::Interface(QObject *parent) : QThread(parent)
{
    qRegisterMetaType<uint8_t>("uint8_t");

    stopped = false;
    mainwindow = new Form_MainWindow;
    mainwindow->show();
    msgHandler = new Msg_Handler;



    /* 更新索引表 */
    connect(msgHandler,&Msg_Handler::Signal_Update_TableState,mainwindow,&Form_MainWindow::Slot_UpdateIndexTable);
    /* 添加指纹 */
    connect(mainwindow,&Form_MainWindow::Signal_AddFinger,this,[=](uint8_t id,uint8_t times,uint8_t param1,uint8_t param2){
        HID_Add_Finger(usb_handle,id,param1,param2,times);
    });
    /* 删除指纹 */
    connect(mainwindow,&Form_MainWindow::Signal_DeleteFinger,this,[=](uint8_t id){
        HID_Delete_Finger(usb_handle,id);
    });
    /* 刷新指纹列表 */
    connect(mainwindow,&Form_MainWindow::Signal_RefreshFinger,this,[=](){
        HID_Get_TableState(usb_handle);
    });
    /* 设置设置呼吸灯效 */
    connect(mainwindow,&Form_MainWindow::Signal_SetBreathRGB,this,[=](uint8_t color_R,uint8_t color_G,uint8_t color_B,uint8_t interval){
        HID_Send_Breath_RGB(usb_handle,color_R,color_G,color_B,interval);
    });
    /* 设置开机密码 */
    connect(mainwindow,&Form_MainWindow::Signal_SetWindowsPassword,this,[=](QString password,uint8_t fingertype,uint8_t id){
        HID_Send_WindowsPassword(usb_handle,(Finger_Type_e)fingertype,password,id);
    });
    /* 设置密码 */
    connect(mainwindow,&Form_MainWindow::Signal_SetPassword,this,[=](QString password,uint8_t fingertype,uint8_t id){
        HID_Send_Password(usb_handle,(Finger_Type_e)fingertype,password,id);
    });
    /* 设置账号+密码 */
    connect(mainwindow,&Form_MainWindow::Signal_SetAccount_Password,this,[=](QString account,QString password,uint8_t fingertype,uint8_t id){
        HID_Send_Account_Password(usb_handle,(Finger_Type_e)fingertype,account,password,id);
    });
    connect(mainwindow,&Form_MainWindow::Signal_SetQuickStart,this,[=](uint8_t fingertype,QUICK_START_e startID,uint8_t index){
        HID_Send_QuickStart(usb_handle,(Finger_Type_e)fingertype,startID,index);
    });
    /* 更新指纹注册状态 */
    connect(msgHandler,&Msg_Handler::Signal_Update_EnrollState,mainwindow,&Form_MainWindow::Slot_EnrollState);

    connect(mainwindow,&Form_MainWindow::Signal_SetShortcut,this,[=](uint8_t fingertype,uint8_t func,char* key,uint8_t key_len,uint8_t index){
        HID_Send_Shortcut(usb_handle,(Finger_Type_e)fingertype,func,key,key_len,index);
    });

    connect(mainwindow,&Form_MainWindow::Signal_SetActionFunc,this,[=](uint8_t func,uint8_t action){
        HID_Set_Action_Func(usb_handle,func,action);
    });

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
                           //HID_Send_Breath_RGB(usb_handle,0xFF,0xFF,0xFF,30);
                           //HID_Get_FW_HW_Msg(usb_handle);
                           msleep(1000);
                           HID_Get_TableState(usb_handle);
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
            //qDebug() << "connect ok";
            rec_num = hid_read_timeout(usb_handle,rec_buffer,REC_LEN,200);
            if(rec_num > 0)
            {
                msgHandler->Data_Resolve(rec_buffer);
            }
        }
        //msleep(1000);
    }
}
