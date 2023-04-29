#include "enrollstate.h"
#include "ui_enrollstate.h"
#include <QDebug>
#include <QPropertyAnimation>

extern uint8_t g_enroll_state;

QPropertyAnimation *animation;

enrollstate::enrollstate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::enrollstate)
{
    ui->setupUi(this);
    animation = new QPropertyAnimation(this,"windowOpacity");
    setWindowFlags(Qt::FramelessWindowHint);
    connect(animation,&QPropertyAnimation::finished,this,[=](){
        this->hide();
    });//效果显示完后关闭
}

enrollstate::~enrollstate()
{
    delete ui;
}


void enrollstate::SL_InterfaceUpdate(void)
{
    qDebug() << "InterfaceUpdate";
    animation->setDuration(2000);
    animation->setStartValue(1);
    animation->setEndValue(0);
    switch (g_enroll_state) {
        case 0x01:
            ui->state->setText("手指移开");
            break;
        case 0x02:
            ui->state->setText("放下手指");
            break;
        case 0x03:
            ui->state->setText("录入成功");
            animation->start();
            //this->hide();
            break;
        case 0x04:
            ui->state->setText("指纹重复");
            break;

        default: break;
    }

}
