#ifndef USBDEVICE_H
#define USBDEVICE_H

#include <QAbstractNativeEventFilter>
#include <QWidget>
#include <QDebug>
#include <QObject>
#include "Windows.h"
#include "Dbt.h"

#pragma execution_character_set("utf-8")

class Q_DECL_EXPORT USBDEVICE :public QWidget,public QAbstractNativeEventFilter
{
    Q_OBJECT
public:
    USBDEVICE(QWidget* parent = nullptr);
    void registerDevice(WId wid);
    bool nativeEventFilter(const QByteArray &eventType, void *message, long *result) override;//事件过滤
signals:
    void deviceIn(QString VID,QString PID);//USB设备插入
    void deviceOut(QString VID,QString PID);//USB设备拔出
};

#endif // USBDEVICE_H
