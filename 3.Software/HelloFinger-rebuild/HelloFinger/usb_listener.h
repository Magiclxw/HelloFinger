#ifndef USB_LISTENER_H
#define USB_LISTENER_H

#include <QAbstractNativeEventFilter>
#include <QDebug>
#include <QObject>
#include "Windows.h"
#include "Dbt.h"
#include "qwindowdefs.h"

#pragma execution_character_set("utf-8")

class USB_Listener : public QObject,public QAbstractNativeEventFilter
{
    Q_OBJECT
public:
    USB_Listener(QObject *parent = nullptr);
    void registerDevice(WId wid);
    bool nativeEventFilter(const QByteArray &eventType, void *message, long *result) override;//事件过滤
signals:
    void deviceIn(QString VID,QString PID);//USB设备插入
    void deviceOut(QString VID,QString PID);//USB设备拔出
};

#endif // USB_LISTENER_H
