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

/**
*@brief	发送对话内容
*@param	-question:对话内容
*@return 执行状态
*/
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

    connect(reply, &QNetworkReply::finished,this, [&]() {   //收到响应
        if (reply->error() == QNetworkReply::NoError) {     //响应正确
            QByteArray responseData = reply->readAll();
            QJsonDocument json = QJsonDocument::fromJson(responseData);
            if(json.isObject())
            {
                QJsonObject jsonObject = json.object();
                //QString request_id = jsonObject.value("request_id").toString();
                QJsonObject jsonObject1 = jsonObject["output"].toObject();
                QString answer = jsonObject1.value("text").toString();
                emit Signal_Chat_Msg_Received(answer);  //发送信号传递对话响应
            }
        } else {    //响应错误
            QByteArray responseData = reply->readAll();
            qDebug() << "API Error:" << reply->errorString();
            qDebug() << "text:" << responseData;
            emit Signal_Chat_Msg_Received(responseData);    //发送信号传递错误内容
        }
        qDebug() << reply->error();
        reply->deleteLater();
    });
}
