#include "interface_chat.h"
#include "system/system_init.h"



QNetworkAccessManager manager;

// 构建API请求
QNetworkRequest request;
// 发送POST请求
QNetworkReply *reply;

interface_chat::interface_chat(QObject *parent) : QObject(parent)
{

}

void interface_chat::Chat_Send_Question(QString question)
{
    QString api_server;
    QByteArray api_key;
    File_Get_ChatAI_URL(&api_server);

    request.setUrl(QUrl(api_server));

    // 设置请求头部
    File_Get_ChatAI_KEY(&api_key);
    request.setRawHeader("Authorization", api_key);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // 构建请求数据
    QJsonObject data;
    data["model"] = "qwen-turbo";

    QJsonObject parameters;
    parameters["messages"] = QJsonArray::fromVariantList(QList<QVariant>() << QJsonObject{{"role", "system"}, {"content", "You are a helpful assistant."}}
                                                                 << QJsonObject{{"role", "user"}, {"content", question}});
    QJsonObject messages;
    messages["messages"] = parameters;

    data["input"] = parameters;

    reply = manager.post(request, QJsonDocument(data).toJson());

    connect(reply, &QNetworkReply::finished,this, [&]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray responseData = reply->readAll();
            QJsonDocument json = QJsonDocument::fromJson(responseData);
            if(json.isObject())
            {
                qDebug() << "obj";
                QJsonObject jsonObject = json.object();
                //QString request_id = jsonObject.value("request_id").toString();
                QJsonObject jsonObject1 = jsonObject["output"].toObject();
                QString text = jsonObject1.value("text").toString();
                emit Signal_Chat_Msg_Received(text);
            }
            if(json.isArray())
            {
                //qDebug() << "array";
            }

        } else {
            QByteArray responseData = reply->readAll();
            qDebug() << "API Error:" << reply->errorString();
            qDebug() << "text:" << responseData;
        }
        qDebug() << reply->error();
        //reply->deleteLater();
    });
}
