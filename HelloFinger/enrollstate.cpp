#include "enrollstate.h"
#include "ui_enrollstate.h"
#include <QDebug>
#include <QPropertyAnimation>
#include "entrance.h"

extern uint8_t g_enroll_param[2];
extern uint8_t table_state_flag;

QPropertyAnimation *animation;
QTimer *delay_timer;

enrollstate::enrollstate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::enrollstate)
{
    ui->setupUi(this);
    //animation = new QPropertyAnimation(this,"windowOpacity");

    delay_timer = new QTimer;

    setWindowFlags(Qt::FramelessWindowHint);
    connect(animation,&QPropertyAnimation::finished,this,[=](){
        //this->close();

    });//效果显示完后关闭

    connect(delay_timer,&QTimer::timeout,this,[=](){
        //animation = new QPropertyAnimation(this,"windowOpacity");
        //animation->setDuration(2000);
        //animation->setStartValue(1);
        //animation->setEndValue(0);
        //animation->start();
        this->hide();
        delay_timer->stop();
    });
}

enrollstate::~enrollstate()
{
    delete ui;
}


void enrollstate::SL_InterfaceUpdate(void)
{
    qDebug() << "InterfaceUpdate";

    switch (g_enroll_param[0]) {
        case 0x03:
            ui->state->setText("手指移开");
            break;
        case 0x01:
            ui->state->setText("放下手指");
            break;
        case 0x06:
            ui->state->setText("录入成功");
//            animation = new QPropertyAnimation(this,"windowOpacity");
//            animation->setDuration(2000);
//            animation->setStartValue(1);
//            animation->setEndValue(0);
            emit SI_Enroll_Finished();  //录入成功后发送成功信号，槽对列表执行刷新操作
//            animation->start();
            delay_timer->start(1000);
            //this->hide();
            break;
        //case 0x04:
        //    ui->state->setText("指纹重复");
        //    break;
        //case 0x05:
        //    ui->state->setText("超时");
        //    break;
        default: break;
    }

}
