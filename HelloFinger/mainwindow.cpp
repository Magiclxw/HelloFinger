#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "listwidgeteditwindow.h"
#include "usbthread.h"
#include <QPainter>
#include "enrollstate.h"
#include <QDebug>
#include <QFileInfo>
#include <QSettings>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QFile>
#include "GlobalMouseKey/globalkeyevent.h"
#include <QMetaEnum>
#include <QString>
#include <QKeyEvent>
#include <QListWidget>
#include <QColor>

extern uint8_t TableState[8];

uint8_t lwIndex = 0;
uint8_t rowIndex = 0;
uint8_t g_enroll_param[2] = {0};    //注册指纹过程返回参数
/* RGB三色控制 */
uint8_t color_R = 0;
uint8_t color_G = 0;
uint8_t color_B = 0;

QColor colCheck("#99ffff"); //指纹有效颜色
QColor colUncheck("#ffffff");   //指纹无效颜色

enrollstate *enroll;


QAction *AddAction; //添加指纹
QAction *RefreshAction; //刷新列表
QAction *DeleteAction;  //删除指纹
QAction *Func_unlock;   //解锁功能
QAction *Func_shortcut; //快捷键
QAction *Func_enterAccount_Password;     //输入账号
QAction *Func_enterPassword;    //输入密码
QAction *Func_openApp;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowIcon(QIcon(":/Icon.jpg"));
    setWindowTitle("HelloFinger");
    //setWindowFlags(Qt::WindowStaysOnTopHint);   //保持顶层显示

    ui->listWidget->setContextMenuPolicy(Qt::CustomContextMenu);    //通过触发信号的方式现实菜单

    this->setContextMenuPolicy(Qt::NoContextMenu);

    QMenuBar *bar = menuBar();
    this->setMenuBar(bar);
    QMenu *Menu = bar->addMenu("MENU");

    bar->setVisible(false);
    ui->lineedit_windowsPassword->setEchoMode(QLineEdit::Password);
    ui->lineEdit_password->setEchoMode(QLineEdit::Password);
    ui->lineEdit_password_o->setEchoMode(QLineEdit::Password);

    enroll = new enrollstate;

    AddAction = Menu->addAction("增加");
    RefreshAction = Menu->addAction("刷新");
    DeleteAction = Menu->addAction("删除");
    Func_unlock = Menu->addAction("解锁");
    Func_shortcut = Menu->addAction("快捷键");
    Func_enterAccount_Password = Menu->addAction("输入账号/密码");
    Func_enterPassword = Menu->addAction("输入密码");

    connect(AddAction,&QAction::triggered,this,[=](){
        uint8_t checkedRow = 0;
        QModelIndex index = ui->listWidget->currentIndex();
        checkedRow = index.row();
        enroll->show(); //弹出注册状态窗口
        uint8_t times = 4;
        uint8_t param[2] = {0x00,0x00};
        emit SI_AddFinger(checkedRow,times,param[0],param[1]);
    });

    connect(RefreshAction,&QAction::triggered,this,[=](){
        emit SI_FingerRefresh();
    });

    connect(DeleteAction,&QAction::triggered,this,[=](){
        uint8_t checkedRow = 0;
        QModelIndex index = ui->listWidget->currentIndex();
        checkedRow = index.row();
        emit SI_FingerDelete(checkedRow);
    });

    connect(Func_unlock,&QAction::triggered,this,[=](){
        ui->stackedWidget->setCurrentIndex(1);
    });

    connect(Func_enterAccount_Password,&QAction::triggered,this,[=](){
        ui->stackedWidget->setCurrentIndex(2);
    });

    connect(Func_enterPassword,&QAction::triggered,this,[=](){
        ui->stackedWidget->setCurrentIndex(3);
    });

    connect(ui->pushButton_windowspassword,&QPushButton::clicked,this,[=](){
        QString windows_password = ui->lineedit_windowsPassword->text();
        emit SI_USB_SEND_WindowsPassword(windows_password);
        qDebug()<<windows_password;
    });

    QFile file("hello.ini");
    QFile jsonFile("jsonFile.json");

    /* INI格式文件处理 */
    /* 判断文件有无 此方式只能存储ascii码格式文件，不方便于文本存储*/
    //if(!file.open(QIODevice::ReadOnly)){    //文件不存在
    //    QSettings *iniWrite = new QSettings("hello.ini",QSettings::IniFormat);
    //    //iniWrite->setValue("item0/value","你好单独发放嘎嘎地方都是发大水发士大夫撒对光反射");
    //    for(int i=0;i<60;i++){  //赋予默认值：0~59
    //        QString item = "item";
    //        item.append(QString::number(i));
    //        iniWrite->setValue(item+"/value",i);
    //    }
    //    delete iniWrite;
    //}else{  // 文件存在
    //    QSettings *iniRead = new QSettings("hello.ini",QSettings::IniFormat);
    //    for(int i=0;i<60;i++){
    //        QString item = "item";
    //        item.append(QString::number(i));
    //        ui->listWidget->item(i)->setText(iniRead->value(item+"/value").toString());
    //    }
    //}
    //file.close();


    ListWidgetEditWindow *listwidgeteditwindow = new ListWidgetEditWindow;

    /* 更新listwidget状态 */
    for (int i=0;i<8 ;i++ ) {
        for(int j=0;j<8;j++){
            if(TableState[i] & 0x01){
                ui->listWidget->item(lwIndex)->setBackgroundColor(colCheck);
                lwIndex++;
                TableState[i] >>= 1;
            }else{
                lwIndex++;
                TableState[i] >>= 1;
            }
        }
    }

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
                ui->listWidget->item(i)->setText(value.toString());
            }
        }
    }
   // connect(ui->add,&QPushButton::clicked,this,[=](){   //添加指纹
   //     uint8_t checkedRow = 0;
   //     QModelIndex index = ui->listWidget->currentIndex();
   //     checkedRow = index.row();
   //     enroll->show();
   //     uint8_t times = 4;
   //     uint8_t param[2] = {0x00,0x00};
   //     emit SI_AddFinger(checkedRow,times,param);
   // });
   //
   // connect(ui->fdelete,&QPushButton::clicked,this,[=](){   //删除指纹
   //     uint8_t checkedRow = 0;
   //     QModelIndex index = ui->listWidget->currentIndex();
   //     checkedRow = index.row();
   //     emit SI_FingerDelete(checkedRow);
   // });
   //
   // connect(ui->refresh,&QPushButton::clicked,this,[=](){   //刷新指纹列表
   //     emit SI_FingerRefresh();
   // });

    connect(this,&MainWindow::SI_TableStateUpdata_T,enroll,&enrollstate::SL_InterfaceUpdate);   //更新指纹注册状态

    connect(enroll,&enrollstate::SI_Enroll_Finished,this,[=](){ //连接指纹注册完成信号
        emit SI_FingerRefresh();    //刷新指纹列表
    });

    connect(ui->listWidget,&QListWidget::itemDoubleClicked,this,[=](){  //列表项双击信号
        QModelIndex index = ui->listWidget->currentIndex();
        rowIndex = index.row();
        listwidgeteditwindow->show();
    });

    connect(listwidgeteditwindow,&ListWidgetEditWindow::btn_ok_Clicked,this,[=](){
        ui->listWidget->item(rowIndex)->setText(inputText);
        QJsonObject mainObj;
        QJsonObject subObj;
        QString item = "item";
        //item.append(QString::number(rowIndex));
        //subObj.insert(item,inputText);
        //mainObj.insert("ListConfig",QJsonValue(subObj));
        //QJsonDocument doc(mainObj);
        //QByteArray data = doc.toJson();
        QFile file("jsonFile.json");
        file.open(QIODevice::ReadWrite);
        QByteArray data = file.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        //if(doc.isObject()){
            mainObj = doc.object();
            //QString listconfig = "ListConfig";
            item.append(QString::number(rowIndex));
            mainObj.insert(item,inputText);
            //mainObj.insert(listconfig,subObj);
        //}
        QJsonDocument writeDoc(mainObj);
        QByteArray writeArry = writeDoc.toJson();
        file.seek(0);       //回到文件开头
        file.write(writeArry);      //文件重写
        file.close();
    });

    connect(ui->R_Slider,&QSlider::sliderMoved,this,&MainWindow::SL_UpdateRGB);
    connect(ui->G_Slider,&QSlider::sliderMoved,this,&MainWindow::SL_UpdateRGB);
    connect(ui->B_Slider,&QSlider::sliderMoved,this,&MainWindow::SL_UpdateRGB);

    GlobalKeyEvent::installKeyEvent();
    connect(GlobalKeyEvent::getInstance(),&GlobalKeyEvent::keyEvent,this,&MainWindow::on_keyEvent);

}


void MainWindow::SL_EnrollStateUpdate(void)
{
    qDebug() << "SL_EnrollStateUpdate";
    emit SI_TableStateUpdata_T();
}

void MainWindow::SL_TableStateUpdate(void)
{
    lwIndex = 0;
    for (int i=0;i<8 ;i++ ) {
        for(int j=0;j<8;j++){
            if(TableState[i] & 0x01){
                ui->listWidget->item(lwIndex)->setBackgroundColor(colCheck);
                lwIndex++;
                TableState[i] >>= 1;
            }else{
                ui->listWidget->item(lwIndex)->setBackgroundColor(colUncheck);
                lwIndex++;
                TableState[i] >>= 1;
            }
        }
    }
    memset(TableState,0,8);
}


void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    QPixmap pix;
    pix.load(":/MainPic.jpg");

    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

void MainWindow::on_keyEvent(QKeyEvent* event)  //全局按键事件
{
    QMetaEnum type = QMetaEnum::fromType<QEvent::Type>();
    QMetaEnum key = QMetaEnum::fromType<Qt::Key>();
    QMetaEnum keyboard = QMetaEnum::fromType<Qt::KeyboardModifiers>();
    QString str = QString("状态：[%1]\t按键：[%2]\t修饰：[%3]]").arg(type.valueToKey(event->type()))
                                           .arg(key.valueToKey(event->key()))
                                           .arg(QString(keyboard.valueToKeys(int(event->modifiers()))));
    if(!event->text().isEmpty())
    {
        str += QString("\t字符：[%1]").arg(event->text());
    }
    qDebug() << "字符" << str;
    delete event;       // 使用完成后记得delete
}


void MainWindow::on_listWidget_customContextMenuRequested(const QPoint &pos)
{
    Q_UNUSED(pos);

    // 新建Menu菜单
    QMenu *ptr = new QMenu(this);
    ptr->setFixedWidth(100);

    // 添加Actions创建菜单项
    ptr->addAction(AddAction);
    ptr->addAction(RefreshAction);
    // 添加一个分割线
    ptr->addSeparator();
    ptr->addAction(DeleteAction);
    QMenu *functionMenu = new QMenu("功能");
    functionMenu->addAction(Func_unlock);
    functionMenu->addAction(Func_shortcut);
    functionMenu->addAction(Func_enterAccount_Password);
    functionMenu->addAction(Func_enterPassword);
    ptr->addMenu(functionMenu);
    // 在鼠标光标位置显示右键快捷菜单
    ptr->exec(QCursor::pos());
    // 手工创建的指针必须手工删除
    delete ptr;
}

void MainWindow::SL_UpdateRGB()
{
    QPalette p;
    color_R = ui->R_Slider->value();
    color_G = ui->G_Slider->value();
    color_B = ui->B_Slider->value();
    p.setColor(QPalette::Window,QColor(color_R,color_G,color_B));
    ui->widget_2->setAutoFillBackground(true);
    ui->widget_2->setPalette(p);
}

MainWindow::~MainWindow()
{
    delete ui;
}



