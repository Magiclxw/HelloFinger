#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "listwidgeteditwindow.h"
#include "usbthread.h"
#include <QPainter>
#include "enrollstate.h"
#include <QDebug>

extern uint8_t TableState[8];

uint8_t lwIndex = 0;
uint8_t rowIndex = 0;
uint8_t g_enroll_state = 0;
QColor colCheck("#99ffff");
QColor colUncheck("#ffffff");

enrollstate *enroll;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowIcon(QIcon(":/Icon.jpg"));
    setWindowTitle("HelloFinger");
    //setWindowFlags(Qt::WindowStaysOnTopHint);   //保持顶层显示
    ListWidgetEditWindow *listwidgeteditwindow = new ListWidgetEditWindow;
    enroll = new enrollstate;
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

    connect(ui->add,&QPushButton::clicked,this,[=](){   //添加指纹
        uint8_t checkedRow = 0;
        QModelIndex index = ui->listWidget->currentIndex();
        checkedRow = index.row();
        enroll->show();
        uint8_t times = 4;
        uint8_t param[2] = {0x00,0x00};
        emit SI_AddFinger(checkedRow,times,param);
    });

    connect(ui->fdelete,&QPushButton::clicked,this,[=](){
        uint8_t checkedRow = 0;
        QModelIndex index = ui->listWidget->currentIndex();
        checkedRow = index.row();
        emit SI_FingerDelete(checkedRow);
    });

    connect(ui->refresh,&QPushButton::clicked,this,[=](){
        emit SI_FingerRefresh();
    });

    connect(this,&MainWindow::SI_TableStateUpdata_T,enroll,&enrollstate::SL_InterfaceUpdate);

    connect(ui->listWidget,&QListWidget::itemDoubleClicked,this,[=](){  //列表项双击信号
        QModelIndex index = ui->listWidget->currentIndex();
        rowIndex = index.row();
        listwidgeteditwindow->show();
    });

    connect(listwidgeteditwindow,&ListWidgetEditWindow::btn_ok_Clicked,this,[=](){
        ui->listWidget->item(rowIndex)->setText(inputText);
    });


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
}


void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    QPixmap pix;
    pix.load(":/MainPic.jpg");

    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

MainWindow::~MainWindow()
{
    delete ui;
}


