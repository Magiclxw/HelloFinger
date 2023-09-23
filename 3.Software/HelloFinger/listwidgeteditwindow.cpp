#include "listwidgeteditwindow.h"
#include "ui_listwidgeteditwindow.h"

QString inputText;

ListWidgetEditWindow::ListWidgetEditWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ListWidgetEditWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("重命名");
    connect(ui->btn_ok,&QPushButton::clicked,this,[=](){
        inputText = ui->lineEdit->text();
        emit btn_ok_Clicked();
        ui->lineEdit->clear();
        this->close();
    });

    connect(ui->btn_cancel,&QPushButton::clicked,this,[=](){
        this->close();
    });
}

ListWidgetEditWindow::~ListWidgetEditWindow()
{
    delete ui;
}
