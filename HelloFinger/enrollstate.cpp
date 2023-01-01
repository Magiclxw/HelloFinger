#include "enrollstate.h"
#include "ui_enrollstate.h"
#include <QDebug>

extern uint8_t g_enroll_state;

enrollstate::enrollstate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::enrollstate)
{
    ui->setupUi(this);
}

enrollstate::~enrollstate()
{
    delete ui;
}


void enrollstate::SL_InterfaceUpdate(void)
{
    qDebug() << "InterfaceUpdate";
    switch (g_enroll_state) {
        case 0x01:
            ui->state->setText("手指移开");
            break;
        case 0x02:
            ui->state->setText("放下手指");
            break;
        case 0x03:
            ui->state->setText("录入成功");
            break;
        case 0x04:
            ui->state->setText("指纹重复");
            break;

        default: break;
    }

}
