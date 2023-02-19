#include "listwidgeteditwindow.h"
#include "ui_listwidgeteditwindow.h"

QString inputText;

ListWidgetEditWindow::ListWidgetEditWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ListWidgetEditWindow)
{
    ui->setupUi(this);
    connect(ui->btn_ok,&QPushButton::clicked,this,[=](){
        inputText = ui->lineEdit->text();
        emit btn_ok_Clicked();
        ui->lineEdit->clear();
        this->hide();
    });
}

ListWidgetEditWindow::~ListWidgetEditWindow()
{
    delete ui;
}
