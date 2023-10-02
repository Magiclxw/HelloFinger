#include "form_mainwindow.h"
#include "ui_form_mainwindow.h"
#include <QMenu>
#include <QMenuBar>
#include <QTimer>
#include <QString>
#include <QSizePolicy>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
#include <QMetaEnum>
#include <QKeyEvent>
#include "lib/GlobalMouseKey/globalkeyevent.h"
#include "qcoreevent.h"
#include "form_hidewindow.h"

QColor colCheck(0,255,255);       //指纹有效颜色
QColor colUncheck(255,255,255);   //指纹无效颜色

QAction *Action_Add;                    //添加指纹
QAction *Action_Refresh;                //刷新列表
QAction *Action_Delete;                 //删除指纹
QAction *Action_unlock;                 //解锁功能
QAction *Action_shortcut;               //快捷键
QAction *Action_enterAccount_Password;  //输入账号
QAction *Action_enterPassword;          //输入密码
QAction *Action_openApp;                //快捷启动

/* RGB三色控制 */
float color_R = 0;
float color_G = 0;
float color_B = 0;
uint8_t dir = 0;
float tmp_R = 0;
float tmp_G = 0;
float tmp_B = 0;
float R_decrease = 0;
float G_decrease = 0;
float B_decrease = 0;
uint8_t interval = 0;

QString tableContent = "tableContent.json";

QTimer *rgb_timer = NULL;

Form_MainWindow::Form_MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Form_MainWindow)
{
    ui->setupUi(this);
    ui->pushButton_save_param->hide();
    this->setWindowTitle("HelloFinger");
    this->setFixedSize(this->width(),this->height());

    Form_HideWindow *hidewindow = new Form_HideWindow;
    hidewindow->show();

    QMenuBar *bar = menuBar();
    this->setMenuBar(bar);
    QMenu *Menu = bar->addMenu("MENU");
    bar->setVisible(false);

    rgb_timer = new QTimer; //初始化rgb显示定时器

    Action_Add = Menu->addAction("增加");
    Action_Delete = Menu->addAction("删除");
    Action_unlock = Menu->addAction("解锁");
    Action_Refresh = Menu->addAction("刷新");
    Action_shortcut = Menu->addAction("快捷键");
    Action_enterPassword = Menu->addAction("输入密码");
    Action_enterAccount_Password = Menu->addAction("输入账号/密码");
    /* 注册按键监听事件 */
    GlobalKeyEvent::installKeyEvent();
    connect(GlobalKeyEvent::getInstance(),&GlobalKeyEvent::keyEvent,this,&Form_MainWindow::on_keyEvent);

    File_Update_TableContent(tableContent);

    ui->listWidget_table_state->setContextMenuPolicy(Qt::CustomContextMenu);
    this->setContextMenuPolicy(Qt::NoContextMenu);

    connect(Action_Add,SIGNAL(triggered()),this,SLOT(Slot_AddFinger()));    //连接添加指纹槽函数
    connect(Action_Delete,SIGNAL(triggered()),this,SLOT(Slot_DeleteFinger()));   //连接删除指纹槽函数
    connect(Action_Refresh,SIGNAL(triggered()),this,SLOT(Slot_RefreshFinger()));    //连接刷新指纹列表槽函数
    connect(Action_unlock,&QAction::triggered,this,[=](){ui->stackedWidget->setCurrentWidget(ui->page_windows_password);}); //修改当前显示界面
    connect(ui->pushButton_save_windows_password,&QPushButton::clicked,this,&Form_MainWindow::Slot_SetWindowsPassword);     //连接windows解锁功能槽函数
    connect(Action_enterAccount_Password,&QAction::triggered,this,[=](){ui->stackedWidget->setCurrentWidget(ui->page_account_password);});    //修改当前显示界面
    connect(ui->pushButton_save_account_password,&QPushButton::clicked,this,&Form_MainWindow::Slot_SetAccount_Password);    //连接输入账号密码槽函数
    connect(Action_enterPassword,&QAction::triggered,this,[=](){ui->stackedWidget->setCurrentWidget(ui->page_account_password);});    //连接输入密码槽函数
    connect(ui->pushButton_password,&QPushButton::clicked,this,&Form_MainWindow::Slot_SetPassword);
    //connect(Action_openApp,SIGNAL(triggered()),this,SLOT());
    //connect(Action_shortcut,SIGNAL(triggered()),this,SLOT());
    connect(ui->slider_R,&QSlider::valueChanged,this,&Form_MainWindow::Slot_SetBreathRGB);   //拖动滑动条后更新显示状态
    connect(ui->slider_G,&QSlider::valueChanged,this,&Form_MainWindow::Slot_SetBreathRGB);
    connect(ui->slider_B,&QSlider::valueChanged,this,&Form_MainWindow::Slot_SetBreathRGB);
    connect(ui->slider_interval,&QSlider::valueChanged,this,&Form_MainWindow::Slot_SetBreathRGB);
    connect(rgb_timer,&QTimer::timeout,this,&Form_MainWindow::Slot_RGB_Display);    //启动呼吸灯动画
    connect(ui->tabWidget,&QTabWidget::tabBarClicked,this,&Form_MainWindow::Slot_SetBreathRGB); //切换tabbar状态后启动呼吸灯动画
    connect(ui->pushButton_save_rgb,&QPushButton::clicked,this,[=](){emit Signal_SetBreathRGB((uint8_t)tmp_R,(uint8_t)tmp_G,(uint8_t)tmp_B,interval);});
    connect(ui->listWidget_table_state,&QListWidget::itemDoubleClicked,this,&Form_MainWindow::Slot_ChangeItemValue);
    connect(ui->pushButton_save_param,&QPushButton::clicked,this,&Form_MainWindow::Slot_SaveItemValue);
    connect(ui->pushButton_save_shortcut,&QPushButton::clicked,this,&Form_MainWindow::Slot_SetShortcut);  //保存快捷键功能

    QFile file("hello.ini");

}

void Form_MainWindow::Slot_UpdateIndexTable()
{
    uint8_t lwIndex = 0;
    for (int i=0;i<8 ;i++ ) {
        for(int j=0;j<8;j++){
            if(TableState[i] & 0x01){
                ui->listWidget_table_state->item(lwIndex)->setBackgroundColor(colCheck);
                lwIndex++;
                TableState[i] >>= 1;
            }else{
                ui->listWidget_table_state->item(lwIndex)->setBackgroundColor(colUncheck);
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
    uint8_t param[2] = {0x00,0x00};
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

void Form_MainWindow::Slot_SetAccount_Password()
{
    QString account = this->ui->lineEdit_ap_account->text();
    QString password = this->ui->lineEdit_ap_password->text();
    if(account.length() == 0 || password.length() == 0)
    {
        return;
    }
    else
    {
        emit Signal_SetAccount_Password(account,password,this->ui->listWidget_table_state->currentIndex().row());
    }

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
    QString password = ui->lineEdit_password->text();
    if(password.length() == 0)
    {
        return;
    }
    else
    {
        emit Signal_SetPassword(password,this->ui->listWidget_table_state->currentIndex().row());
    }
}

void Form_MainWindow::Slot_SetWindowsPassword()
{
    QString password = ui->lineEdit_windows_password->text();
    if(password.length() == 0)
    {
        return;
    }
    else
    {
        emit Signal_SetWindowsPassword(password,this->ui->listWidget_table_state->currentIndex().row());
    }

}

void Form_MainWindow::Slot_ChangeItemValue()
{
    ui->listWidget_table_state->currentItem()->setFlags(ui->listWidget_table_state->currentItem()->flags()|Qt::ItemIsEditable);
    ui->pushButton_save_param->show();
}

void Form_MainWindow::Slot_SaveItemValue()
{
    uint8_t rowIndex = ui->listWidget_table_state->currentIndex().row();
    QString inputText = ui->listWidget_table_state->item(rowIndex)->text();
    qDebug() << inputText;
    QJsonObject mainObj;
    QJsonObject subObj;
    QString item = "item";
    QFile file(tableContent);
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


void Form_MainWindow::on_keyEvent(QKeyEvent* event)  //全局按键事件
{
    QMetaEnum type = QMetaEnum::fromType<QEvent::Type>();
    QMetaEnum key = QMetaEnum::fromType<Qt::Key>();
    QMetaEnum keyboard = QMetaEnum::fromType<Qt::KeyboardModifiers>();
    QString str = QString("状态：[%1]\t按键：[%2]\t修饰：[%3]]").arg(type.valueToKey(event->type()),0)
                                           .arg(key.valueToKey(event->key()),0)
                                           .arg(QString(keyboard.valueToKeys(int(event->modifiers()))));
    if(!event->text().isEmpty())
    {
        str += QString("\t字符：[%1]").arg(event->text());
    }
    qDebug() << "字符" << str;
    QString key_type = type.valueToKey(event->type());
    QString key_value = key.valueToKey(event->key());
    QString key_modify = keyboard.valueToKeys(int(event->modifiers()));
    qDebug() << "字符" << key_type << key_value << key_modify;
//    if(event->type() == QEvent::KeyPress){
//        if(event->key() == Qt::Key_Up)
//        {
//            if(event->modifiers() == (Qt::ShiftModifier|Qt::ControlModifier|Qt::AltModifier))
//            {
//                qDebug() << "hot key up";
//            }
//        }
//        if(event->key() == Qt::Key_Down)
//        {
//            if(event->modifiers() == (Qt::ShiftModifier|Qt::ControlModifier|Qt::AltModifier))
//            {
//                qDebug() << "hot key Down";
//            }
//        }

//    }
    //if(key_type == "KeyPress")
    //{
    //    if(key_value == "Key_Up")
    //    {
    //        if(key_modify == "ShiftModifier|ControlModifier|AltModifier")
    //        {
    //            qDebug() << "hot key up";
    //        }
    //    }
    //    if(key_value == "Key_Down")
    //    {
    //        if(key_modify == "ShiftModifier|ControlModifier|AltModifier")
    //        {
    //            qDebug() << "hot key Down";
    //        }
    //    }
    //}
    delete event;       // 使用完成后记得delete
}

void Form_MainWindow::File_Update_TableContent(QString path)
{
    QFile jsonFile(path);
    /* JSON格式文件处理 */
    if(!jsonFile.open(QIODevice::ReadOnly)){    //文件不存在
        //QJsonObject mainObj;
        QJsonObject subObj;
        for(int i=1;i<60;i++){
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
            for(int i=0;i<60;i++){
                QString item = "item";
                item.append(QString::number(i));
                QJsonValue value = obj.value(item);
                //QJsonObject subObj = value.toObject();
                ui->listWidget_table_state->item(i)->setText(value.toString());
            }
        }
    }
}

void Form_MainWindow::File_Save_Shortcut()
{

}

void Form_MainWindow::Slot_SetShortcut()
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
        key[0] = ui->comboBox_key_1->currentText().toUtf8().toHex().toUInt();
    }
    if(ui->comboBox_key_2->currentText()!="空")
    {
        key_len ++;
        key[1] = ui->comboBox_key_2->currentText().toUtf8().toHex().toUInt();
    }
    if(ui->comboBox_key_3->currentText()!="空")
    {
        key_len ++;
        key[2] = ui->comboBox_key_3->currentText().toUtf8().toHex().toUInt();
    }
    if(ui->comboBox_key_4->currentText()!="空")
    {
        key_len ++;
        key[3] = ui->comboBox_key_4->currentText().toUtf8().toHex().toUInt();
    }
    if(ui->comboBox_key_5->currentText()!="空")
    {
        key_len ++;
        key[4] = ui->comboBox_key_5->currentText().toUtf8().toHex().toUInt();
    }
    if(ui->comboBox_key_6->currentText()!="空")
    {
        key_len ++;
        key[5] = ui->comboBox_key_6->currentText().toUtf8().toHex().toUInt();
    }

    index = ui->listWidget_table_state->currentIndex().row();
    emit Signal_SetShortcut(func_key,(char*)key,key_len,index);
    qDebug() << "key = " << key_len;

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
    ptr->addMenu(functionMenu);
    // 在鼠标光标位置显示右键快捷菜单
    ptr->exec(QCursor::pos());
    // 手工创建的指针必须手工删除
    delete ptr;
}

