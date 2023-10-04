#include "system_init.h"
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include "interface.h"
#include <QSettings>
#include <QFileInfo>
#include <QFileIconProvider>
#include <QLabel>
#include <QJsonArray>

QString quick_start_file = "quick_start";
QString table_name_file = "table_name.json";


QFile jsonFile(table_name_file);

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

void File_FastStart_Save(uint8_t page,uint8_t index,uint8_t checkStete,QString path)
{
//    QString filePath;
//    filePath = quick_start_file;
//    filePath.append("_page"+QString::number(page)+".ini");
//    QFile file(filePath);

//    QSettings *iniWrite = new QSettings(filePath,QSettings::IniFormat);
//    QString item = "item"+QString::number(index);
//    iniWrite->setValue(item+"/checked",checkStete);
//    iniWrite->setValue(item+"/url",url);
//    delete iniWrite;

//    file.close();

    QString filePath;
    QJsonObject obj;
    filePath = quick_start_file;

    filePath.append("_page"+QString::number(page)+".json");
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {

    }
    else
    {
        QString item = "item"+QString::number(index);
        //QJsonArray arr;
        //arr.append(url);
        //obj[item] = arr;
        //QJsonDocument doc(obj);
        obj.insert(item,path);
        QJsonDocument doc(obj);
        QByteArray data = doc.toJson();
        file.write(data);
        file.close();
    }
}

QString File_FastStart_Read(uint8_t page,uint8_t index,uint8_t* checkState)
{
    QString path;
    QString filePath;
    QJsonObject obj;
    filePath = quick_start_file;
    //filePath.append("_page"+QString::number(page)+".ini");
    //QFile file(filePath);
    //if(file.open(QIODevice::ReadOnly))
    //{
    //    QSettings *iniRead = new QSettings(filePath,QSettings::IniFormat);
    //    QString item = "item";
    //    item.append(QString::number(index));
    //    url = iniRead->value(item+"/url").toString();
    //    *checkState = iniRead->value(item+"/checked").toUInt();
    //    delete iniRead;
    //
    //    return url;
    //}
    //return 0;
    filePath.append("_page"+QString::number(page)+".json");
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {

    }
    else
    {
        QByteArray data = file.readAll();
        file.close();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        if(!doc.isNull())
        {
            if(doc.isObject())
            {
                QJsonObject obj = doc.object();
                path = obj["item"+QString::number(index)].toString();
                qDebug() << "path:" << path;
            }

        }
        else
        {

        }

    }
    return path;
}

void Get_Icon_From_Path(QString path)
{
    QFileInfo fileInfo(path);
    QFileIconProvider iconProvider;
    QIcon icon = iconProvider.icon(fileInfo);
    QLabel label;
    label.setPixmap(icon.pixmap(32,32));

}


