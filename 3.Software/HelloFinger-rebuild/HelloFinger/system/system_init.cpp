#include "system_init.h"
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include "interface.h"
QFile file("config.ini");
QFile jsonFile("table_name.json");

System_Init::System_Init(QObject *parent) : QObject(parent)
{

}


void File_TableName_Init(QMainWindow mainwindow)
{
    if(!jsonFile.open(QIODevice::ReadOnly))//文件不存在
    {
        //QJsonObject mainObj;
        QJsonObject subObj;
        for(int i=1;i<60;i++)
        {
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
    }
    else
    {                                      //文件存在
        QByteArray data = jsonFile.readAll();
        jsonFile.close();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        if(doc.isObject())
        {
            QJsonObject obj = doc.object();
            //QString data = "ListConfig";
            for(int i=0;i<60;i++)
            {
                QString item = "item";
                item.append(QString::number(i));
                QJsonValue value = obj.value(item);
                //QJsonObject subObj = value.toObject();
                //mainwindow->ui->listWidget->item(i)->setText(value.toString());
            }
        }
    }
}
