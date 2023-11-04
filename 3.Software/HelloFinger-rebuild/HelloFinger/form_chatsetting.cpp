#include "form_chatsetting.h"
#include "ui_form_chatsetting.h"
#include "system/system_init.h"
#include <QFile>

Form_ChatSetting::Form_ChatSetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Form_ChatSetting)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    QFile file(":/qss/lightgray.css"); // 创建QFile对象，指定样式表文件路径
    file.open(QFile::ReadOnly); // 打开文件，只读模式
    QString styleSheet = QLatin1String(file.readAll()); // 读取文件内容到字符串
    setStyleSheet(styleSheet); // 应用样式表

    QString apiserver;
    QByteArray apikey;
    File_Get_ChatAI_URL(&apiserver);
    File_Get_ChatAI_KEY(&apikey);
    ui->lineEdit_chatURL->setText(apiserver);
    ui->lineEdit_chatKEY->setText(apikey);

    connect(ui->pushButton_save_chat_config,&QPushButton::clicked,this,[=](){
        File_Set_ChatAI(ui->lineEdit_chatURL->text(),ui->lineEdit_chatKEY->text());
        this->close();
    });

}

Form_ChatSetting::~Form_ChatSetting()
{
    delete ui;
}

void Form_ChatSetting::on_pushButton_cancel_chat_config_clicked()
{
    this->close();
}

