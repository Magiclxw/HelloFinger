#include "form_mainwindow.h"
#include "ui_form_mainwindow.h"


QColor colCheck("#99ffff"); //指纹有效颜色
QColor colUncheck("#ffffff");   //指纹无效颜色

Form_MainWindow::Form_MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Form_MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("HelloFinger");

}

void Form_MainWindow::Slot_Updata_TableState(uint8_t *tableState)
{
    uint8_t lwIndex = 0;
    for (int i=0;i<8 ;i++ ) {
        for(int j=0;j<8;j++){
            if(tableState[i] & 0x01){
                ui->listWidget_table_state->item(lwIndex)->setBackgroundColor(colCheck);
                lwIndex++;
                tableState[i] >>= 1;
            }else{
                ui->listWidget_table_state->item(lwIndex)->setBackgroundColor(colUncheck);
                lwIndex++;
                tableState[i] >>= 1;
            }
        }
    }
}

Form_MainWindow::~Form_MainWindow()
{
    delete ui;
}

