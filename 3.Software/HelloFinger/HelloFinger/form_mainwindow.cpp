#include "form_mainwindow.h"
#include "ui_form_mainwindow.h"
#include <QMenu>
#include <QMenuBar>
#include <QTimer>
#include <QString>
#include <QSizePolicy>
#include <QString>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
#include <QMetaEnum>
#include <QKeyEvent>
#include "lib/GlobalMouseKey/globalkeyevent.h"
#include "qcoreevent.h"
#include "form_hidewindow.h"
#include <QDragEnterEvent>
#include <QMimeData>
#include "system/system_init.h"
#include <QFileInfo>
#include <QFileIconProvider>
#include <QLabel>
#include <QDesktopServices>
#include <QProcess>
#include <QTextCodec>
#include "hid_function.h"
#include "interface_chat.h"
#include <QClipboard>
#include <QWindow>
#include "form_chatsetting.h"


QColor itemValid(0,255,255);       //指纹有效颜色
QColor itemUnValid(255,255,255);   //指纹无效颜色
QColor itemkeyValid(0,255,0);       //指纹+按键有效颜色
QColor itemkeyUnValid(255,255,255);   //指纹+按键无效颜色

QAction *Action_Add;                    //添加指纹
QAction *Action_Refresh;                //刷新列表
QAction *Action_Delete;                 //删除指纹
QAction *Action_unlock;                 //解锁功能
QAction *Action_shortcut;               //快捷键
QAction *Action_enterAccount_Password;  //输入账号
QAction *Action_enterPassword;          //输入密码
QAction *Action_setQuickStart1;                //快捷启动
QAction *Action_setQuickStart2;                //快捷启动
QAction *Action_setQuickStart3;                //快捷启动
QAction *Action_setQuickStart4;                //快捷启动
QAction *Action_setQuickStart5;                //快捷启动
QAction *Action_setQuickStart6;                //快捷启动
QAction *Action_listWidget_Delete_Item;        //删除索引表项

/* RGB三色控制 */
float color_R = 0;
float color_G = 0;
float color_B = 0;
uint8_t dir = 0;    //亮度增减方向
float tmp_R = 0;
float tmp_G = 0;
float tmp_B = 0;
float R_decrease = 0;
float G_decrease = 0;
float B_decrease = 0;
uint8_t interval = 0;   //亮度改变间隔

QString chat_rec_last_msg;  //记录接收到的对话信息

QString table_1_Content = "config/table1Content.json";
QString table_2_Content = "config/table2Content.json";

QTimer *rgb_timer = NULL;   //灯效演示定时器
QTimer *hidewindowHold_timer = NULL;    //侧边栏超时隐藏定时器

Form_HideWindow *hidewindow = NULL;
interface_chat *chat = NULL;


Form_MainWindow::Form_MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Form_MainWindow)
{
    ui->setupUi(this);
    /* 隐藏保存参数按键 */
    ui->pushButton_save_param->hide();
    ui->pushButton_save_param_key->hide();

    this->setWindowTitle("HelloFinger");
    this->setWindowIcon(QIcon(":/icon/main_icon.jpg"));
    this->setFixedSize(this->width(),this->height());

    InitSysTray();  //放置托盘

    QFile file(":/qss/lightgray.css"); // 创建QFile对象，指定样式表文件路径
    file.open(QFile::ReadOnly); // 打开文件，只读模式
    QString styleSheet = QLatin1String(file.readAll()); // 读取文件内容到字符串
    setStyleSheet(styleSheet); // 应用样式表

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));   //设置编码格式

    ui->textEdit_chat_input->setPlaceholderText("此处输入对话内容");

    ui->lineEdit_email->setText(AUTHOR_EMAIL);
    ui->lineEdit_group->setText(AUTHOR_GROUP);
    ui->lineEdit_developer_group->setText(AUTHOR_DEVELOPER_GROUP);
    ui->label_software_version->setText(SOFTWARE_VERSION);
    ui->label_software_build_time->setText(__DATE__);

    hidewindow = new Form_HideWindow;
    hidewindow->show();
    hidewindow->File_Update_Hidewindow_Content();   //更新侧边栏内容

    chat = new interface_chat;

    QMenuBar *bar = menuBar();
    this->setMenuBar(bar);
    QMenu *Menu = bar->addMenu("MENU");
    QMenu *ListWidgetMenu = bar->addMenu("MENU");
    bar->setVisible(false);

    Update_QuickStart_Content();   //更新快捷启动列表
    Update_HideWindow_List();      //更新侧边栏启动列表

    rgb_timer = new QTimer; //初始化rgb显示定时器
    hidewindowHold_timer = new QTimer; //初始化侧边栏隐藏定时器

    Action_Add = Menu->addAction("增加");
    Action_Delete = Menu->addAction("删除");
    Action_unlock = Menu->addAction("解锁");
    Action_Refresh = Menu->addAction("刷新");
    Action_shortcut = Menu->addAction("快捷键");
    Action_enterPassword = Menu->addAction("输入密码");
    Action_enterAccount_Password = Menu->addAction("输入账号/密码");
    Action_setQuickStart1 = Menu->addAction("快捷启动流程1");
    Action_setQuickStart2 = Menu->addAction("快捷启动流程2");
    Action_setQuickStart3 = Menu->addAction("快捷启动流程3");
    Action_setQuickStart4 = Menu->addAction("快捷启动流程4");
    Action_setQuickStart5 = Menu->addAction("快捷启动流程5");
    Action_setQuickStart6 = Menu->addAction("快捷启动流程6");
    Action_listWidget_Delete_Item = ListWidgetMenu->addAction("删除");
    /* 注册按键监听事件 */
    GlobalKeyEvent::installKeyEvent();
    connect(GlobalKeyEvent::getInstance(),&GlobalKeyEvent::keyEvent,this,&Form_MainWindow::on_keyEvent);

    File_Update_TableContent(table_1_Content);  //更新索引表1(指纹)
    File_Update_TableContent(table_2_Content);  //更新索引表2(指纹+按键)

    ui->listWidget_table_state->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->listWidget_table_state_key->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->listWidget_task_1->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->listWidget_task_2->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->listWidget_task_3->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->listWidget_task_4->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->listWidget_task_5->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->listWidget_task_6->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->listWidget_hidwindow->setContextMenuPolicy(Qt::CustomContextMenu);
    this->setContextMenuPolicy(Qt::NoContextMenu);

    connect(Action_Add,&QAction::triggered,this,&Form_MainWindow::Slot_AddFinger);    //连接添加指纹槽函数
    connect(Action_Delete,&QAction::triggered,this,&Form_MainWindow::Slot_DeleteFinger);   //连接删除指纹槽函数
    connect(Action_Refresh,&QAction::triggered,this,&Form_MainWindow::Slot_RefreshFinger);    //连接刷新指纹列表槽函数
    connect(Action_unlock,&QAction::triggered,this,[=](){ui->stackedWidget->setCurrentWidget(ui->page_windows_password);ui->stackedWidget_key->setCurrentWidget(ui->page_windows_password_key);}); //当前界面切换为开机密码配置
    connect(Action_shortcut,&QAction::triggered,this,[=](){ui->stackedWidget->setCurrentWidget(ui->page_shortcut);ui->stackedWidget_key->setCurrentWidget(ui->page_shortcut_key);});    //当前界面切换为快捷键配置
    connect(Action_enterAccount_Password,&QAction::triggered,this,[=](){ui->stackedWidget->setCurrentWidget(ui->page_account_password);ui->stackedWidget_key->setCurrentWidget(ui->page_account_password_key);});    //当前界面切换为账号密码配置
    connect(Action_enterPassword,&QAction::triggered,this,[=](){ui->stackedWidget->setCurrentWidget(ui->page_password);ui->stackedWidget_key->setCurrentWidget(ui->page_password_key);});    //当前界面切换为密码配置
    connect(Action_listWidget_Delete_Item,&QAction::triggered,this,&Form_MainWindow::Slot_DeleteListWidgetItem);    //删除选中指纹模版
    connect(Action_setQuickStart1,&QAction::triggered,this,[=](){Slot_SetQuickStart(QUICK_START_1);});  //执行快捷启动功能1
    connect(Action_setQuickStart2,&QAction::triggered,this,[=](){Slot_SetQuickStart(QUICK_START_2);});  //执行快捷启动功能2
    connect(Action_setQuickStart3,&QAction::triggered,this,[=](){Slot_SetQuickStart(QUICK_START_3);});  //执行快捷启动功能3
    connect(Action_setQuickStart4,&QAction::triggered,this,[=](){Slot_SetQuickStart(QUICK_START_4);});  //执行快捷启动功能4
    connect(Action_setQuickStart5,&QAction::triggered,this,[=](){Slot_SetQuickStart(QUICK_START_5);});  //执行快捷启动功能5
    connect(Action_setQuickStart6,&QAction::triggered,this,[=](){Slot_SetQuickStart(QUICK_START_6);});  //执行快捷启动功能6
    connect(ui->slider_R,&QSlider::valueChanged,this,&Form_MainWindow::Slot_SetBreathRGB);   //拖动滑动条后更新显示状态
    connect(ui->slider_G,&QSlider::valueChanged,this,&Form_MainWindow::Slot_SetBreathRGB);
    connect(ui->slider_B,&QSlider::valueChanged,this,&Form_MainWindow::Slot_SetBreathRGB);
    connect(ui->slider_interval,&QSlider::valueChanged,this,&Form_MainWindow::Slot_SetBreathRGB);
    connect(rgb_timer,&QTimer::timeout,this,&Form_MainWindow::Slot_RGB_Display);    //启动呼吸灯动画
    connect(ui->tabWidget,&QTabWidget::tabBarClicked,this,&Form_MainWindow::Slot_SetBreathRGB); //切换tabbar状态后启动呼吸灯动画
    connect(ui->listWidget_table_state,&QListWidget::itemDoubleClicked,this,&Form_MainWindow::Slot_ChangeItemValue);    //修改列表项名称
    connect(ui->listWidget_table_state_key,&QListWidget::itemDoubleClicked,this,&Form_MainWindow::Slot_ChangeItemValue);    //修改列表项名称
    connect(ui->pushButton_save_windows_password,&QPushButton::clicked,this,&Form_MainWindow::Slot_SetWindowsPassword);     //设置windows解锁密码
    connect(ui->pushButton_save_account_password,&QPushButton::clicked,this,&Form_MainWindow::Slot_SetAccount_Password);    //设置账号密码
    connect(ui->pushButton_password,&QPushButton::clicked,this,&Form_MainWindow::Slot_SetPassword); //设置密码
    connect(ui->pushButton_save_param,&QPushButton::clicked,this,&Form_MainWindow::Slot_SaveItemValue); //保存列表项名
    connect(ui->pushButton_save_param_key,&QPushButton::clicked,this,&Form_MainWindow::Slot_SaveItemValue); //保存列表项名
    connect(ui->pushButton_save_shortcut,&QPushButton::clicked,this,&Form_MainWindow::Slot_SetShortcut);  //保存快捷键功能
    connect(ui->pushButton_save_shortcut_key,&QPushButton::clicked,this,&Form_MainWindow::Slot_SetShortcut);  //保存快捷键功能
    connect(ui->pushButton_save_windows_password_key,&QPushButton::clicked,this,&Form_MainWindow::Slot_SetWindowsPassword);     //设置windows解锁密码
    connect(ui->pushButton_save_account_password_key,&QPushButton::clicked,this,&Form_MainWindow::Slot_SetAccount_Password);    //设置账号密码
    connect(ui->pushButton_password_key,&QPushButton::clicked,this,&Form_MainWindow::Slot_SetPassword); //设置密码
    connect(ui->pushButton_save_rgb,&QPushButton::clicked,this,[=](){emit Signal_SetBreathRGB((uint8_t)tmp_R,(uint8_t)tmp_G,(uint8_t)tmp_B,interval);});    //设置RGB呼吸灯效
    connect(ui->pushButton_save_finger_rgb,&QPushButton::clicked,this,&Form_MainWindow::Slot_SetFingerRGB); //设置指纹RGB等效
    connect(ui->pushButton_chat_setting,&QPushButton::clicked,this,&Form_MainWindow::Slot_Popup_ChatSettingWindow); //AI对话配置

    connect(this,&Form_MainWindow::Signal_UpdateHideWindowCheckedItem,hidewindow,&Form_HideWindow::Slot_UpdateCheckedItem); //更新侧边栏被选中项目
    connect(hidewindowHold_timer,&QTimer::timeout,hidewindow,[=](){hidewindow->hideWindow();hidewindowHold_timer->stop();});    //侧边栏定时超时停止
    connect(this,&Form_MainWindow::Signal_OpenHidewindowItem,hidewindow,&Form_HideWindow::Slot_OpenItem);   //打开侧边栏项目程序

    connect(ui->pushButton_chat_data_send,&QPushButton::clicked,this,&Form_MainWindow::Slot_Chat_Send_Msg); //发送对话内容
    connect(chat,&interface_chat::Signal_Chat_Msg_Received,this,&Form_MainWindow::Chat_RevMsg_Handler); //处理接收对话内容
}

void Form_MainWindow::Slot_UpdateIndexTable()
{
    uint8_t lwIndex = 0;
    for (int i=0;i<8 ;i++ )
    {
        for(int j=0;j<8;j++)
        {
            if(TableState[i] & 0x01)
            {
                ui->listWidget_table_state->item(lwIndex)->setBackgroundColor(itemValid);
                ui->listWidget_table_state_key->item(lwIndex)->setBackgroundColor(itemkeyValid);
                lwIndex++;
                TableState[i] >>= 1;
            }else{
                ui->listWidget_table_state->item(lwIndex)->setBackgroundColor(itemUnValid);
                ui->listWidget_table_state_key->item(lwIndex)->setBackgroundColor(itemkeyUnValid);
                lwIndex++;
                TableState[i] >>= 1;
            }
        }
    }
}

void Form_MainWindow::Slot_AddFinger()
{
    uint8_t checkedRow = 0;
    QModelIndex index = this->ui->listWidget_table_state->currentIndex();
    checkedRow = index.row();
    //enroll->show(); //弹出注册状态窗口
    ui->stackedWidget->setCurrentWidget(ui->page_enrollState);
    uint8_t times = 4;  //注册次数
    uint8_t param[2] = {0x00,ENROLL_PARAM_REENROLL_DISABLE|ENROLL_PARAM_LED_OFF};
    emit Signal_AddFinger(checkedRow,times,param[0],param[1]);
    ui->label_enroll_state->setText("放下手指");
}

void Form_MainWindow::Slot_EnrollState(uint8_t state1,uint8_t state2)
{
    static uint8_t process = 0;
    uint8_t step = 8;
    if(state1 == 0x01)
    {
        process += step;
        ui->label_enroll_state->setText("获取指纹");
    }
    if(state1 == 0x02)
    {
        process += step;
        ui->label_enroll_state->setText("生成特征");
    }
    if(state1 == 0x03)
    {
        process += step;
        ui->label_enroll_state->setText("重新放下手指");
    }
    if(state1 == 0x05 && state2 == 0xF1)
    {
        process = 0;
        ui->label_enroll_state->setText("指纹重复");
    }
    if(state1 == 0x06 && state2 == 0xF2)
    {
        process = 100;
        ui->label_enroll_state->setText("注册成功");
    }
    ui->progressBar->setValue(process);
    if(process == 100) process = 0;
}

void Form_MainWindow::Slot_DeleteFinger()
{
    uint8_t checkedRow = 0;
    QModelIndex index = this->ui->listWidget_table_state->currentIndex();
    checkedRow = index.row();
    emit Signal_DeleteFinger(checkedRow);
}

void Form_MainWindow::Slot_RefreshFinger()
{
    emit Signal_RefreshFinger();
}



void Form_MainWindow::Slot_SetBreathRGB()
{
    /* RGB三色控制 */
    color_R = this->ui->slider_R->value();
    color_G = this->ui->slider_G->value();
    color_B = this->ui->slider_B->value();
    interval = this->ui->slider_interval->value();
    tmp_R = color_R;
    tmp_G = color_G;
    tmp_B = color_B;
    ui->label_R_value->setText(QString::number(tmp_R));
    ui->label_G_value->setText(QString::number(tmp_G));
    ui->label_B_value->setText(QString::number(tmp_B));
    ui->label_interval_value->setText(QString::number(interval));
    R_decrease = tmp_R/40;
    G_decrease = tmp_G/40;
    B_decrease = tmp_B/40;
    dir = 0;
    rgb_timer->start(interval);
}



void Form_MainWindow::Slot_RGB_Display()
{
    QPalette p;

    if(dir == 0)
    {
        color_R -= R_decrease;
        color_G -= G_decrease;
        color_B -= B_decrease;
        if((color_R < R_decrease && tmp_R > R_decrease) || (color_G < G_decrease && tmp_G > G_decrease) || (color_B < B_decrease && tmp_B > B_decrease))
        {
            color_R = 0;
            color_G = 0;
            color_B = 0;
            dir = 1;
        }
    }
    else if(dir == 1)
    {
        color_R += R_decrease;
        color_G += G_decrease;
        color_B += B_decrease;
        if(color_R > tmp_R-R_decrease || color_G > tmp_G-G_decrease || color_B > tmp_B-B_decrease)
        {
            color_R = tmp_R;
            color_G = tmp_G;
            color_B = tmp_B;
            dir = 0;
        }
    }
    p.setColor(QPalette::Window,QColor(color_R,color_G,color_B));
    ui->frame_color->setAutoFillBackground(true);
    ui->frame_color->setPalette(p);

    if(ui->tabWidget->currentWidget() != ui->tab_RGB)
    {
        rgb_timer->stop();
    }
}

void Form_MainWindow::Slot_SetPassword()
{
    uint8_t finger_type = ui->tabWidget_finger_func->currentIndex();
    {
        if(finger_type == FINGER)
        {
            QString password = ui->lineEdit_password->text();
            if(password.length() == 0)
            {
                return;
            }
            emit Signal_SetPassword(password,finger_type,this->ui->listWidget_table_state->currentIndex().row());
        }
        else
        {
            QString password = ui->lineEdit_password_key->text();
            if(password.length() == 0)
            {
                return;
            }
            emit Signal_SetPassword(password,finger_type,this->ui->listWidget_table_state_key->currentIndex().row());
        }

    }
}

void Form_MainWindow::Slot_SetWindowsPassword()
{
    uint8_t finger_type = ui->tabWidget_finger_func->currentIndex();
    if(finger_type == FINGER)
    {
        QString password = ui->lineEdit_windows_password->text();
        if(password.length() == 0)
        {
            return;
        }
        emit Signal_SetWindowsPassword(password,finger_type,this->ui->listWidget_table_state->currentIndex().row());
    }
    else
    {
        QString password = ui->lineEdit_windows_password_key->text();
        if(password.length() == 0)
        {
            return;
        }
        emit Signal_SetWindowsPassword(password,finger_type,this->ui->listWidget_table_state_key->currentIndex().row());
    }

}

void Form_MainWindow::Slot_SetAccount_Password()
{
    uint8_t finger_type = ui->tabWidget_finger_func->currentIndex();


    if(finger_type == FINGER)
    {
        QString account = this->ui->lineEdit_ap_account->text();
        QString password = this->ui->lineEdit_ap_password->text();
        if(account.length() == 0 || password.length() == 0)
        {
            return;
        }
        emit Signal_SetAccount_Password(account,password,finger_type,this->ui->listWidget_table_state->currentIndex().row());
    }
    else
    {
        QString account = this->ui->lineEdit_ap_account_key->text();
        QString password = this->ui->lineEdit_ap_password_key->text();
        if(account.length() == 0 || password.length() == 0)
        {
            return;
        }
        emit Signal_SetAccount_Password(account,password,finger_type,this->ui->listWidget_table_state_key->currentIndex().row());
    }

}

void Form_MainWindow::Slot_SetQuickStart(QUICK_START_e startID)
{
    uint8_t finger_type = ui->tabWidget_finger_func->currentIndex();
    qDebug() << "quick start id = " << startID;
    if(finger_type == FINGER)
    {

        emit Signal_SetQuickStart(finger_type,startID,this->ui->listWidget_table_state->currentIndex().row());
    }
    if(finger_type == FINGER_KEY)
    {
        emit Signal_SetQuickStart(finger_type,startID,this->ui->listWidget_table_state->currentIndex().row());
    }
}

void Form_MainWindow::Slot_ChangeItemValue()
{
    uint8_t finger_type = ui->tabWidget_finger_func->currentIndex();
    if(finger_type == FINGER)
    {
        ui->listWidget_table_state->currentItem()->setFlags(ui->listWidget_table_state->currentItem()->flags()|Qt::ItemIsEditable);
        ui->pushButton_save_param->show();
    }
    if(finger_type == FINGER_KEY)
    {
        ui->listWidget_table_state_key->currentItem()->setFlags(ui->listWidget_table_state_key->currentItem()->flags()|Qt::ItemIsEditable);
        ui->pushButton_save_param_key->show();
    }
}

void Form_MainWindow::Slot_SaveItemValue()
{
    uint8_t finger_type = ui->tabWidget_finger_func->currentIndex();
    if(finger_type == FINGER)
    {
        uint8_t rowIndex = ui->listWidget_table_state->currentIndex().row();
        QString inputText = ui->listWidget_table_state->item(rowIndex)->text();
        qDebug() << inputText;
        QJsonObject mainObj;
        QJsonObject subObj;
        QString item = "item";
        QFile file(table_1_Content);
        file.open(QIODevice::ReadWrite);
        QByteArray data = file.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        mainObj = doc.object();
        item.append(QString::number(rowIndex));
        mainObj.insert(item,inputText);
        QJsonDocument writeDoc(mainObj);
        QByteArray writeArry = writeDoc.toJson();
        file.seek(0);       //回到文件开头
        file.write(writeArry);      //文件重写
        file.close();
        ui->pushButton_save_param->hide();  //保存完成后隐藏保存按键
    }
    if(finger_type == FINGER_KEY)
    {
        uint8_t rowIndex = ui->listWidget_table_state_key->currentIndex().row();
        QString inputText = ui->listWidget_table_state_key->item(rowIndex)->text();
        qDebug() << inputText;
        QJsonObject mainObj;
        QJsonObject subObj;
        QString item = "item";
        QFile file(table_2_Content);
        file.open(QIODevice::ReadWrite);
        QByteArray data = file.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        mainObj = doc.object();
        item.append(QString::number(rowIndex));
        mainObj.insert(item,inputText);
        QJsonDocument writeDoc(mainObj);
        QByteArray writeArry = writeDoc.toJson();
        file.seek(0);       //回到文件开头
        file.write(writeArry);      //文件重写
        file.close();
        ui->pushButton_save_param_key->hide();  //保存完成后隐藏保存按键
    }

}

void Form_MainWindow::Slot_DeleteListWidgetItem()
{
    QWidget *func_type = ui->tabWidget->currentWidget();
    if(func_type == ui->tab_quickstart)
    {
        uint8_t page = ui->toolBox->currentIndex();
        uint8_t item = 0;
        switch (page)
        {
        case 0:
        {
            item = ui->listWidget_task_1->currentIndex().row();
            break;
        }
        case 1:
        {
            item = ui->listWidget_task_2->currentIndex().row();
            break;
        }
        case 2:
        {
            item = ui->listWidget_task_3->currentIndex().row();
            break;
        }
        case 3:
        {
            item = ui->listWidget_task_4->currentIndex().row();
            break;
        }
        case 4:
        {
            item = ui->listWidget_task_5->currentIndex().row();
            break;
        }
        case 5:
        {
            item = ui->listWidget_task_6->currentIndex().row();
            break;
        }

        }
        File_FastStart_Save(page,item,0,"");
        Update_QuickStart_Content();
    }
    if(func_type == ui->tab_hidwindow)
    {
        uint8_t item = 0;
        item = ui->listWidget_hidwindow->currentIndex().row();
        File_HideWindow_Content_Save("",item);
        Update_HideWindow_List();
        hidewindow->File_Update_Hidewindow_Content();
    }
}

void Form_MainWindow::Slot_Update_FirmwareMsg(char* date,char* version)
{
    qDebug() << "date" << date;
    qDebug() << "version" << version;
    ui->label_build_date->setText(date);
    ui->label_firmware_version->setText(version);
}

/**
*@brief	更新硬件信息
*@param	-flashId:flash id号
*@param -ch9329_ver:ch9329版本号
*@param -fpm383cSN:fpm383c SN号
*@return NULL
*/
void Form_MainWindow::Slot_Update_HardwareMsg(uint8_t* flashId,char ch9329_ver,char* fpm383cSN)
{
    QString t_fpm383cSN = QString::fromUtf8(fpm383cSN);
    uint16_t t_flashId = flashId[0] | flashId[1]<<8;
    char t_ch9329_ver[2] = {ch9329_ver,0};
    ui->label_flashId->setText(QString::number(t_flashId,16).toUpper());
    ui->label_ch9329_version->setText("V1." + QString::fromUtf8(t_ch9329_ver));
    ui->label_fpm383_sn->setText(t_fpm383cSN);
}

void Form_MainWindow::on_keyEvent(QKeyEvent* event)  //全局按键事件
{
    /* 当前状态信息 */
//    QMetaEnum type = QMetaEnum::fromType<QEvent::Type>();
//    QMetaEnum key = QMetaEnum::fromType<Qt::Key>();
//    QMetaEnum keyboard = QMetaEnum::fromType<Qt::KeyboardModifiers>();
//    QString str = QString("状态：[%1]\t按键：[%2]\t修饰：[%3]]").arg(type.valueToKey(event->type()),0)
//                                           .arg(key.valueToKey(event->key()),0)
//                                           .arg(QString(keyboard.valueToKeys(int(event->modifiers()))));
//    if(!event->text().isEmpty())
//    {
//        str += QString("\t字符：[%1]").arg(event->text());
//    }
//    qDebug() << "字符" << str;
//    QString key_type = type.valueToKey(event->type());
//    QString key_value = key.valueToKey(event->key());
//    QString key_modify = keyboard.valueToKeys(int(event->modifiers()));
//    qDebug() << "字符" << key_type << key_value << key_modify;

    if(event->type() == QEvent::KeyPress){
        if(event->key() == Qt::Key_Left)
        {
            if(event->modifiers() == (Qt::ShiftModifier|Qt::ControlModifier|Qt::AltModifier))
            {
//                uint8_t currentIndex = ui->listWidget_table_state->currentIndex().row();
//                uint8_t nextIndex = currentIndex+1;

//                if(currentIndex == ui->listWidget_table_state->count()-1)
//                {
//                    nextIndex = 0;
//                }
//                ui->listWidget_table_state->setCurrentRow(nextIndex);
                //ui->listWidget_table_state->item(nextIndex)->setSelected(true);
                hidewindowHold_timer->setInterval(HIDEWINDOW_HOLD_TIME);    //重新计时
                emit Signal_UpdateHideWindowCheckedItem(Qt::Key_Left);
                //qDebug() << "current index = " << currentIndex << "next index = " << nextIndex;
            }
        }
        if(event->key() == Qt::Key_Right)
        {
            if(event->modifiers() == (Qt::ShiftModifier|Qt::ControlModifier|Qt::AltModifier))
            {
//                uint8_t currentIndex = ui->listWidget_table_state->currentIndex().row();
//                uint8_t nextIndex = currentIndex-1;
//                if(currentIndex == 0 )
//                {
//                    nextIndex = ui->listWidget_table_state->count()-1;
//                }
//                ui->listWidget_table_state->setCurrentRow(nextIndex);
                //ui->listWidget_table_state->item(nextIndex)->setSelected(true);
                hidewindowHold_timer->setInterval(HIDEWINDOW_HOLD_TIME);    //重新计时
                emit Signal_UpdateHideWindowCheckedItem(Qt::Key_Right);
                //qDebug() << "current index = " << currentIndex << "next index = " << nextIndex;
            }
        }
        if(event->key() == Qt::Key_F1) //编码器按下(侧边栏未显示)
        {
            if(event->modifiers() == (Qt::ShiftModifier|Qt::ControlModifier|Qt::AltModifier))
            {
                hidewindow->showWindow();

                qDebug() << "encoder ";
                hidewindowHold_timer->start(HIDEWINDOW_HOLD_TIME);
            }
        }
        if(event->key() == Qt::Key_F2)//显示/隐藏Action界面
        {
            if(event->modifiers() == (Qt::ShiftModifier|Qt::ControlModifier|Qt::AltModifier))
            {
                if(this->isVisible() == true && ui->tabWidget->currentWidget() == ui->tab_chat)
                {
                    this->hide();
                }
                else
                {
                    this->show();
                    ui->tabWidget->setCurrentWidget(ui->tab_chat);
                }

            }
        }
        if(event->key() == Qt::Key_F3)  //编码器按下(侧边栏已显示)
        {
            if(event->modifiers() == (Qt::ShiftModifier|Qt::ControlModifier|Qt::AltModifier))
            {
                emit Signal_OpenHidewindowItem();
            }
        }
        if(event->key() == Qt::Key_0)
        {
            if(event->modifiers() == (Qt::ControlModifier|Qt::MetaModifier))
            {
                qDebug() << "press key 0";
                uint8_t page = 0;
                uint8_t start_num = 0;
                start_num = ui->listWidget_task_1->count();
                for (uint8_t i=0; i<start_num; i++)
                {
                    QString path = File_FastStart_Read(page,i).toLocal8Bit();
                    QProcess::startDetached(path);
                    //QDesktopServices::openUrl(QUrl(path));
                }
            }
        }
        if(event->key() == Qt::Key_1)
        {
            if(event->modifiers() == (Qt::MetaModifier|Qt::ControlModifier))
            {
                uint8_t page = 1;
                uint8_t start_num = 0;
                start_num = ui->listWidget_task_2->count();
                for (uint8_t i=0; i<start_num; i++)
                {
                    QString path = File_FastStart_Read(page,i).toLocal8Bit();
                    QProcess::startDetached(path);
                }
            }
        }
        if(event->key() == Qt::Key_2)
        {
            if(event->modifiers() == (Qt::ControlModifier|Qt::MetaModifier))
            {
                uint8_t page = 2;
                uint8_t start_num = 0;
                start_num = ui->listWidget_task_3->count();
                for (uint8_t i=0; i<start_num; i++)
                {
                    QString path = File_FastStart_Read(page,i).toLocal8Bit();
                    QProcess::startDetached(path);
                    //QDesktopServices::openUrl(QUrl(path));
                }
            }
        }
        if(event->key() == Qt::Key_3)
        {
            if(event->modifiers() == (Qt::ControlModifier|Qt::MetaModifier))
            {
                uint8_t page = 3;
                uint8_t start_num = 0;
                start_num = ui->listWidget_task_4->count();
                for (uint8_t i=0; i<start_num; i++)
                {
                    QString path = File_FastStart_Read(page,i).toLocal8Bit();
                    QProcess::startDetached(path);
                    //QDesktopServices::openUrl(QUrl(path));
                }
            }
        }
        if(event->key() == Qt::Key_4)
        {
            if(event->modifiers() == (Qt::ControlModifier|Qt::MetaModifier))
            {
                uint8_t page = 4;
                uint8_t start_num = 0;
                start_num = ui->listWidget_task_5->count();
                for (uint8_t i=0; i<start_num; i++)
                {
                    QString path = File_FastStart_Read(page,i).toLocal8Bit();
                    QProcess::startDetached(path);
                    //QDesktopServices::openUrl(QUrl(path));
                }
            }
        }
        if(event->key() == Qt::Key_5)
        {
            if(event->modifiers() == (Qt::ControlModifier|Qt::MetaModifier))
            {
                uint8_t page = 5;
                uint8_t start_num = 0;
                start_num = ui->listWidget_task_6->count();
                for (uint8_t i=0; i<start_num; i++)
                {
                    QString path = File_FastStart_Read(page,i).toLocal8Bit();
                    QProcess::startDetached(path);
                    //QDesktopServices::openUrl(QUrl(path));
                }
            }
        }

    }
    delete event;
}

void Form_MainWindow::File_Update_TableContent(QString path)
{
    QFile jsonFile(path);
    /* JSON格式文件处理 */
    if(!jsonFile.open(QIODevice::ReadOnly)){    //文件不存在
        //QJsonObject mainObj;
        QJsonObject subObj;
        for(int i=0;i<60;i++){
            QString item = "item";
            item.append(QString::number(i));
            subObj.insert(item,QJsonValue(QString::number(i)));
        }
        //mainObj.insert("ListConfig",QJsonValue(subObj));
        //QJsonDocument doc(mainObj);
        QJsonDocument doc(subObj);
        QByteArray data = doc.toJson();
        jsonFile.open(QIODevice::ReadWrite);
        jsonFile.write(data);
        jsonFile.close();
    }else{                                      //文件存在
        QByteArray data = jsonFile.readAll();
        jsonFile.close();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        if(doc.isObject()){
            QJsonObject obj = doc.object();
            //QString data = "ListConfig";
            //uint8_t finger_type = ui->tabWidget_finger_func->currentIndex();
            //if(finger_type == FINGER)
            //{
            if(path == table_1_Content)
            {
                qDebug() << "finger";
                for(int i=0;i<60;i++){
                    QString item = "item";
                    item.append(QString::number(i));
                    QJsonValue value = obj.value(item);
                    //QJsonObject subObj = value.toObject();

                    ui->listWidget_table_state->item(i)->setText(value.toString());
                }
            }

            //}
            //else
            //{
            if(path == table_2_Content)
            {
                qDebug() << "finger key";
                for(int i=0;i<60;i++){
                    QString item = "item";
                    item.append(QString::number(i));
                    QJsonValue value = obj.value(item);
                    //QJsonObject subObj = value.toObject();

                    ui->listWidget_table_state_key->item(i)->setText(value.toString());
                }
            }

            //}

        }
    }
}

//更新快捷启动列表
void Form_MainWindow::Update_QuickStart_Content()
{

    for (uint8_t i=0; i<6; i++ )
    {
        uint8_t item = 0;
        uint8_t itemNum = 0;
        switch (i) {
        case 0:
        {
            ui->listWidget_task_1->clear();
            break;
        }
        case 1:
        {
            ui->listWidget_task_2->clear();
            break;
        }
        case 2:
        {
            ui->listWidget_task_3->clear();
            break;
        }
        case 3:
        {
            ui->listWidget_task_4->clear();
            break;
        }
        case 4:
        {
            ui->listWidget_task_5->clear();
            break;
        }
        case 5:
        {
            ui->listWidget_task_6->clear();
            break;
        }
        }
        itemNum = File_Fast_Start_Num_Get(i,item);
        while(1)
        {

            if(item == itemNum)
            {
                break;
            }
            QString path = File_FastStart_Read(i,item);
            {
                QListWidgetItem *listwidgetitem = new QListWidgetItem;
                QFileInfo fileInfo(path);
                QFileIconProvider iconProvider;
                QString fileName = fileInfo.fileName();
                QIcon icon = iconProvider.icon(fileInfo);
                QLabel label;
                label.setPixmap(icon.pixmap(50,50));
                listwidgetitem->setIcon(icon);
                listwidgetitem->setText(fileName);
                switch (i)
                {
                case 0:
                {
                    ui->listWidget_task_1->addItem(listwidgetitem);
                    break;
                }
                case 1:
                {
                    ui->listWidget_task_2->addItem(listwidgetitem);
                    break;
                }
                case 2:
                {
                    ui->listWidget_task_3->addItem(listwidgetitem);
                    break;
                }
                case 3:
                {
                    ui->listWidget_task_4->addItem(listwidgetitem);
                    break;
                }
                case 4:
                {
                    ui->listWidget_task_5->addItem(listwidgetitem);
                    break;
                }
                case 5:
                {
                    ui->listWidget_task_6->addItem(listwidgetitem);
                    break;
                }
                }


//                if(checkState == true)
//                {
//                    item->setCheckState(Qt::Checked);
//                }
            }
            item++;
        }
    }
}

void Form_MainWindow::Update_HideWindow_List()
{
    uint8_t item = 0;
    uint8_t itemNum = 0;
    itemNum = File_HideWindow_ItemNum_Get();
    ui->listWidget_hidwindow->clear();
    while(1)
    {

        if(item == itemNum)
        {
            break;
        }
        QString path = File_HideWindow_Item_Read(item);
        {
            QListWidgetItem *listwidgetitem = new QListWidgetItem;
            QFileInfo fileInfo(path);
            QFileIconProvider iconProvider;
            QString fileName = fileInfo.fileName();
            QIcon icon = iconProvider.icon(fileInfo);
            QLabel label;
            label.setPixmap(icon.pixmap(50,50));
            listwidgetitem->setIcon(icon);
            listwidgetitem->setText(fileName);

            ui->listWidget_hidwindow->addItem(listwidgetitem);
        }
        item++;
    }
}

void Form_MainWindow::Slot_SetShortcut()
{
    uint8_t fingertype = ui->tabWidget_finger_func->currentIndex();

    if(fingertype == FINGER)
    {
        QString sfunc_key = ui->comboBox_func_key->currentText();
        uint8_t func_key = 0;
        uint8_t key[6] = {0};
        uint8_t key_len = 0;
        uint8_t index = 0;

        if(sfunc_key.contains("Ctrl"))
        {
            func_key |= Qt::ControlModifier >> 26;
            qDebug() << "conatins ctrl";
        }
        if(sfunc_key.contains("Shift"))
        {
            func_key |= Qt::ShiftModifier >> 24;
            qDebug() << "conatins shift";
        }
        if(sfunc_key.contains("Win"))
        {
            func_key |= Qt::MetaModifier >> 25;
            qDebug() << "conatins win";
        }
        if(sfunc_key.contains("Alt"))
        {
            func_key |= Qt::AltModifier >> 25;
            qDebug() << "conatins alt";
        }
        if(ui->comboBox_key_1->currentText()!="空")
        {
            key_len ++;
            key[0] = ui->comboBox_key_1->currentText().toLatin1().at(0);
        }
        if(ui->comboBox_key_2->currentText()!="空")
        {
            key_len ++;
            key[1] = ui->comboBox_key_2->currentText().toLatin1().at(0);
        }
        if(ui->comboBox_key_3->currentText()!="空")
        {
            key_len ++;
            key[2] = ui->comboBox_key_3->currentText().toLatin1().at(0);
        }
        if(ui->comboBox_key_4->currentText()!="空")
        {
            key_len ++;
            key[3] = ui->comboBox_key_4->currentText().toLatin1().at(0);
        }
        if(ui->comboBox_key_5->currentText()!="空")
        {
            key_len ++;
            key[4] = ui->comboBox_key_5->currentText().toLatin1().at(0);
        }
        if(ui->comboBox_key_6->currentText()!="空")
        {
            key_len ++;
            key[5] = ui->comboBox_key_6->currentText().toLatin1().at(0);
        }

        index = ui->listWidget_table_state->currentIndex().row();
        emit Signal_SetShortcut(fingertype,func_key,(char*)key,key_len,index);
    }
    if(fingertype == FINGER_KEY)
    {
        QString sfunc_key = ui->comboBox_func_key_key->currentText();
        uint8_t func_key = 0;
        uint8_t key[6] = {0};
        uint8_t key_len = 0;
        uint8_t index = 0;

        if(sfunc_key.contains("Ctrl"))
        {
            func_key |= Qt::ControlModifier >> 26;
            qDebug() << "conatins ctrl";
        }
        if(sfunc_key.contains("Shift"))
        {
            func_key |= Qt::ShiftModifier >> 24;
            qDebug() << "conatins shift";
        }
        if(sfunc_key.contains("Win"))
        {
            func_key |= Qt::MetaModifier >> 25;
            qDebug() << "conatins win";
        }
        if(sfunc_key.contains("Alt"))
        {
            func_key |= Qt::AltModifier >> 25;
            qDebug() << "conatins alt";
        }
        if(ui->comboBox_key_with_key_1->currentText()!="空")
        {
            key_len ++;
            key[0] = ui->comboBox_key_with_key_1->currentText().toLatin1().at(0);
        }
        if(ui->comboBox_key_with_key_2->currentText()!="空")
        {
            key_len ++;
            key[1] = ui->comboBox_key_with_key_2->currentText().toLatin1().at(0);
        }
        if(ui->comboBox_key_with_key_3->currentText()!="空")
        {
            key_len ++;
            key[2] = ui->comboBox_key_with_key_3->currentText().toLatin1().at(0);
        }
        if(ui->comboBox_key_with_key_4->currentText()!="空")
        {
            key_len ++;
            key[3] = ui->comboBox_key_with_key_4->currentText().toLatin1().at(0);
        }
        if(ui->comboBox_key_with_key_5->currentText()!="空")
        {
            key_len ++;
            key[4] = ui->comboBox_key_with_key_5->currentText().toLatin1().at(0);
        }
        if(ui->comboBox_key_with_key_6->currentText()!="空")
        {
            key_len ++;
            key[5] = ui->comboBox_key_with_key_6->currentText().toLatin1().at(0);
        }

        index = ui->listWidget_table_state_key->currentIndex().row();
        emit Signal_SetShortcut(fingertype,func_key,(char*)key,key_len,index);
    }

}

void Form_MainWindow::Slot_Chat_Send_Msg(void)
{
    QString msg = ui->textEdit_chat_input->toPlainText();
    chat->Chat_Send_Question(msg);
}

void Form_MainWindow::Slot_SetFingerRGB(void)
{
    uint8_t mode = ui->comboBox_finger_func->currentIndex()+1;
    uint8_t startColor = 0;
    uint8_t stopColor = 0;
    uint8_t interval = 0;

    if(ui->checkBox_start_R->checkState() == Qt::Checked)
    {
        startColor |= LED_COLOR_RED;
    }
    if(ui->checkBox_start_G->checkState() == Qt::Checked)
    {
        startColor |= LED_COLOR_GREEN;
    }
    if(ui->checkBox_start_B->checkState() == Qt::Checked)
    {
        startColor |= LED_COLOR_BLUE;
    }

    if(ui->checkBox_stop_R->checkState() == Qt::Checked)
    {
        stopColor |= LED_COLOR_RED;
    }
    if(ui->checkBox_stop_G->checkState() == Qt::Checked)
    {
        stopColor |= LED_COLOR_GREEN;
    }
    if(ui->checkBox_stop_B->checkState() == Qt::Checked)
    {
        stopColor |= LED_COLOR_BLUE;
    }

    interval = ui->spinBox_rgb_cycle->value();

    emit Signal_SetFingerRGB(mode,startColor,stopColor,interval);

}

void Form_MainWindow::dropEvent(QDropEvent *event)           // 放下事件
{
    uint8_t page_index = 0; //文件拖入页索引
    const QMimeData *mimeData = event->mimeData();      // 获取MIME数据
    if(mimeData->hasUrls()){                            // 如果数据中包含URL
        QList<QUrl> urlList = mimeData->urls();         // 获取URL列表
        // 将其中第一个URL表示为本地文件路径
        QString fileName = urlList.at(0).toLocalFile();
        qDebug() << "url:" << fileName;
        if(ui->tabWidget->currentWidget() == ui->tab_quickstart)
        {
            uint8_t page = ui->toolBox->currentIndex();
            uint8_t index = 0;
            switch (page)
            {
            case 0:
            {
                index = ui->listWidget_task_1->count();
                break;
            }
            case 1:
            {
                index = ui->listWidget_task_2->count();
                break;
            }
            case 2:
            {
                index = ui->listWidget_task_3->count();
                break;
            }
            case 3:
            {
                index = ui->listWidget_task_4->count();
                break;
            }
            case 4:
            {
                index = ui->listWidget_task_5->count();
                break;
            }
            case 5:
            {
                index = ui->listWidget_task_6->count();
                break;
            }
            default:break;
            }
            qDebug() << "page =" << page;
            File_FastStart_Save(page,index,0,fileName);
            Update_QuickStart_Content();
        }
        if(ui->tabWidget->currentWidget() == ui->tab_hidwindow)
        {
            uint8_t index = ui->listWidget_hidwindow->count();
            File_HideWindow_Content_Save(fileName,index);
            Update_HideWindow_List();
            hidewindow->File_Update_Hidewindow_Content();
        }
    }
    page_index = ui->toolBox->currentIndex();

}

void Form_MainWindow::dragEnterEvent(QDragEnterEvent *event) // 拖动进入事件
{
    if(event->mimeData()->hasUrls())                    // 数据中是否包含URL
        event->acceptProposedAction();                  // 如果是则接收动作
    else event->ignore();                               // 否则忽略该事件
}

/* 监听窗口是否进入最小化状态 */
//void Form_MainWindow::changeEvent(QEvent *event)
//{
//    if(event->type()!=QEvent::WindowStateChange) return;
//    if(this->windowState()==Qt::WindowMinimized)
//    {
//        qDebug() << "min";
//    }
//}

void Form_MainWindow::Chat_RevMsg_Handler(QString msg)
{
    //ui->textEdit_chat_output->setText(msg);
    chat_rec_last_msg = msg;
    QString ask = "问：\r\n"+ui->textEdit_chat_input->toPlainText();
    QString answer = "答：\r\n"+msg+"\r\n----------------------------\r\n";
    ui->textEdit_chat_output->append(ask);
    ui->textEdit_chat_input->clear();
    ui->textEdit_chat_output->append(answer);
}

void Form_MainWindow::Slot_Popup_ChatSettingWindow(void)
{
    Form_ChatSetting *chatsetting = new Form_ChatSetting;
    chatsetting->show();
}

void Form_MainWindow::InitSysTray()
{
    m_sysTrayIcon = new QSystemTrayIcon(this);

    QIcon icon = QIcon(":/icon/main_icon.jpg");

    m_sysTrayIcon->setIcon(icon);

    m_sysTrayIcon->setToolTip("HelloFinger");

    connect(m_sysTrayIcon,&QSystemTrayIcon::activated,[=](QSystemTrayIcon::ActivationReason reason){
        if(reason == QSystemTrayIcon::DoubleClick)
        {
            this->show();
        }
    });

    createAction();
    createMenu();

    m_sysTrayIcon->show();
}

void Form_MainWindow::createAction()
{
    m_shoWindow = new QAction("显示主界面",this);
    connect(m_shoWindow,&QAction::triggered,this,&Form_MainWindow::Slot_ShowWindow);
    m_exit = new QAction("退出",this);
    connect(m_exit,&QAction::triggered,this,&Form_MainWindow::Slot_Exit);

}

void Form_MainWindow::createMenu()
{
    m_menu = new QMenu(this);
    //新增菜单项---显示主界面
    m_menu->addAction(m_shoWindow);
    //增加分隔符
    m_menu->addSeparator();
    //新增菜单项---退出程序
    m_menu->addAction(m_exit);
    //把QMenu赋给QSystemTrayIcon对象
    m_sysTrayIcon->setContextMenu(m_menu);
}

void Form_MainWindow::Slot_ShowWindow()
{
    this->show();
}

void Form_MainWindow::Slot_Exit()
{
    qApp->exit();
}

void Form_MainWindow::closeEvent(QCloseEvent *event)
{
    //忽略窗口关闭事件
        QApplication::setQuitOnLastWindowClosed( true );
        this->hide();
        event->ignore();
}

Form_MainWindow::~Form_MainWindow()
{
    delete ui;
}


void Form_MainWindow::on_listWidget_table_state_customContextMenuRequested(const QPoint &pos)
{
    Q_UNUSED(pos);

    // 新建Menu菜单
    QMenu *ptr = new QMenu(this);
    QMenu *functionMenu = new QMenu("功能");
    //ptr->setFixedWidth(100);

    // 添加Actions创建菜单项
    ptr->addAction(Action_Add);
    ptr->addAction(Action_Refresh);
    ptr->addAction(Action_Delete);

    functionMenu->addAction(Action_unlock);
    functionMenu->addAction(Action_shortcut);
    functionMenu->addAction(Action_enterAccount_Password);
    functionMenu->addAction(Action_enterPassword);
    functionMenu->addAction(Action_setQuickStart1);
    functionMenu->addAction(Action_setQuickStart2);
    functionMenu->addAction(Action_setQuickStart3);
    functionMenu->addAction(Action_setQuickStart4);
    functionMenu->addAction(Action_setQuickStart5);
    functionMenu->addAction(Action_setQuickStart6);

    ptr->addMenu(functionMenu);
    // 在鼠标光标位置显示右键快捷菜单
    ptr->exec(QCursor::pos());
    // 手工创建的指针必须手工删除
    delete ptr;
}



void Form_MainWindow::on_listWidget_task_1_customContextMenuRequested(const QPoint &pos)
{
    Q_UNUSED(pos);
    QMenu *ptr = new QMenu(this);
    ptr->addAction(Action_listWidget_Delete_Item);
    ptr->exec(QCursor::pos());
    delete ptr;

}


void Form_MainWindow::on_listWidget_task_2_customContextMenuRequested(const QPoint &pos)
{
    Q_UNUSED(pos);
    QMenu *ptr = new QMenu(this);
    ptr->addAction(Action_listWidget_Delete_Item);
    ptr->exec(QCursor::pos());
    delete ptr;
}


void Form_MainWindow::on_listWidget_task_3_customContextMenuRequested(const QPoint &pos)
{
    Q_UNUSED(pos);
    QMenu *ptr = new QMenu(this);
    ptr->addAction(Action_listWidget_Delete_Item);
    ptr->exec(QCursor::pos());
    delete ptr;
}


void Form_MainWindow::on_listWidget_task_4_customContextMenuRequested(const QPoint &pos)
{
    Q_UNUSED(pos);
    QMenu *ptr = new QMenu(this);
    ptr->addAction(Action_listWidget_Delete_Item);
    ptr->exec(QCursor::pos());
    delete ptr;
}


void Form_MainWindow::on_listWidget_task_5_customContextMenuRequested(const QPoint &pos)
{
    Q_UNUSED(pos);
    QMenu *ptr = new QMenu(this);
    ptr->addAction(Action_listWidget_Delete_Item);
    ptr->exec(QCursor::pos());
    delete ptr;
}


void Form_MainWindow::on_listWidget_task_6_customContextMenuRequested(const QPoint &pos)
{
    Q_UNUSED(pos);
    QMenu *ptr = new QMenu(this);
    ptr->addAction(Action_listWidget_Delete_Item);
    ptr->exec(QCursor::pos());
    delete ptr;
}

void Form_MainWindow::on_listWidget_hidwindow_customContextMenuRequested(const QPoint &pos)
{
    Q_UNUSED(pos);
    QMenu *ptr = new QMenu(this);
    ptr->addAction(Action_listWidget_Delete_Item);
    ptr->exec(QCursor::pos());
    delete ptr;
}

void Form_MainWindow::on_listWidget_table_state_key_customContextMenuRequested(const QPoint &pos)
{
    Q_UNUSED(pos);

    // 新建Menu菜单
    QMenu *ptr = new QMenu(this);
    QMenu *functionMenu = new QMenu("功能");
    //ptr->setFixedWidth(100);

    // 添加Actions创建菜单项
    functionMenu->addAction(Action_unlock);
    functionMenu->addAction(Action_shortcut);
    functionMenu->addAction(Action_enterAccount_Password);
    functionMenu->addAction(Action_enterPassword);
    functionMenu->addAction(Action_setQuickStart1);
    functionMenu->addAction(Action_setQuickStart2);
    functionMenu->addAction(Action_setQuickStart3);
    functionMenu->addAction(Action_setQuickStart4);
    functionMenu->addAction(Action_setQuickStart5);
    functionMenu->addAction(Action_setQuickStart6);

    ptr->addMenu(functionMenu);
    // 在鼠标光标位置显示右键快捷菜单
    ptr->exec(QCursor::pos());
    // 手工创建的指针必须手工删除
    delete ptr;
}


void Form_MainWindow::on_pushButton_chat_copy_answer_clicked()
{
    QClipboard *clip = QApplication::clipboard();
    if(chat_rec_last_msg != NULL)
    {
        clip->setText(chat_rec_last_msg);
    }


}


void Form_MainWindow::on_pushButton_action_play_pause_clicked()
{
    emit Signal_SetActionFunc(ACTION_FUNC_MEDIA,MEDIA_KEY_TYPE_KEY_PLAY_PAUSE);
}


void Form_MainWindow::on_pushButton_action_calculator_clicked()
{
    emit Signal_SetActionFunc(ACTION_FUNC_MEDIA,MEDIA_KEY_TYPE_KEY_CALCULATOR);
}



void Form_MainWindow::on_pushButton_action_chat_clicked()
{
    emit Signal_SetActionFunc(ACTION_FUNC_CHAT,ACTION_FUNC_CHAT);
}


void Form_MainWindow::on_pushButton_action_computer_clicked()
{
    emit Signal_SetActionFunc(ACTION_FUNC_MEDIA,MEDIA_KEY_TYPE_KEY_MY_COMPUTER);
}


void Form_MainWindow::on_pushButton_action_email_clicked()
{
    emit Signal_SetActionFunc(ACTION_FUNC_MEDIA,MEDIA_KEY_TYPE_KEY_EMAIL);
}


void Form_MainWindow::on_pushButton_action_explorer_clicked()
{
    emit Signal_SetActionFunc(ACTION_FUNC_MEDIA,MEDIA_KEY_TYPE_KEY_REWIND);
}


void Form_MainWindow::on_pushButton_action_mute_clicked()
{
    emit Signal_SetActionFunc(ACTION_FUNC_MEDIA,MEDIA_KEY_TYPE_KEY_MUTE);
}


void Form_MainWindow::on_pushButton_action_power_clicked()
{
    emit Signal_SetActionFunc(ACTION_FUNC_POWER,POWER_KEY_TYPE_KEY_POWER);
}


void Form_MainWindow::on_pushButton_action_screen_save_clicked()
{
    emit Signal_SetActionFunc(ACTION_FUNC_MEDIA,MEDIA_KEY_TYPE_KEY_SCREEN_SAVE);
}


void Form_MainWindow::on_pushButton_action_sleep_clicked()
{
    emit Signal_SetActionFunc(ACTION_FUNC_POWER,POWER_KEY_TYPE_KEY_SLEEP);
}


void Form_MainWindow::on_pushButton_action_weakup_clicked()
{
    emit Signal_SetActionFunc(ACTION_FUNC_POWER,POWER_KEY_TYPE_KEY_WAKE_UP);
}


void Form_MainWindow::on_pushButton_RGB_next_page_clicked()
{
    ui->stackedWidget_RGB->setCurrentWidget(ui->page_finger_rgb);
}


void Form_MainWindow::on_pushButton_RGB_last_page_clicked()
{
    ui->stackedWidget_RGB->setCurrentWidget(ui->page_rgb);
}


void Form_MainWindow::on_pushButton_get_firmware_msg_clicked()
{
    emit Signal_GetFirmwareMsg();
}


void Form_MainWindow::on_pushButton_get_hardware_msg_clicked()
{
    emit Signal_GetHardwareMsg();
}


void Form_MainWindow::on_pushButton_update_clicked()
{
    QDesktopServices::openUrl(QUrl(QString(SOFTWARE_UPDATE_LINK)));
}
