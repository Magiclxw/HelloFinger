#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "listwidgeteditwindow.h"
#include "usbthread.h"
#include <QPainter>

extern uint8_t TableState[8];

uint8_t lwIndex = 0;
uint8_t rowIndex = 0;
QColor colCheck("#99ffff");
QColor colUncheck("#ffffff");

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowIcon(QIcon(":/Icon.jpg"));
    setWindowTitle("HelloFinger");
    setWindowFlags(Qt::WindowStaysOnTopHint);   //保持顶层显示
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

    connect(ui->listWidget,&QListWidget::itemDoubleClicked,this,[=](){  //列表项双击信号
        QModelIndex index = ui->listWidget->currentIndex();
        rowIndex = index.row();
        listwidgeteditwindow->show();
    });

    connect(listwidgeteditwindow,&ListWidgetEditWindow::btn_ok_Clicked,this,[=](){
        ui->listWidget->item(rowIndex)->setText(inputText);
    });
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


