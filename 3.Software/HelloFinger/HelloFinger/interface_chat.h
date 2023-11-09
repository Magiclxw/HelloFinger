#ifndef INTERFACE_CHAT_H
#define INTERFACE_CHAT_H

#include <QObject>
#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>


class interface_chat : public QObject
{
    Q_OBJECT
public:
    explicit interface_chat(QObject *parent = nullptr);
    void Chat_Send_Question(QString question);

signals:
    void Signal_Chat_Msg_Received(QString msg);

};

#endif // INTERFACE_CHAT_H
