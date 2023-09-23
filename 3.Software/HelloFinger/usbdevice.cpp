#include "usbdevice.h"

USBDEVICE::USBDEVICE(QWidget *parent):QWidget (parent)
{

}

void USBDEVICE::registerDevice(WId wid)
{
    const GUID GUID_DEVINTERFACE =
    { 0xa5dcbf10, 0x6530, 0x11D2, { 0x90, 0x1F, 0x00, 0xC0, 0x4F, 0xB9, 0x51, 0xED }};

    HDEVNOTIFY hDevNotify;
    DEV_BROADCAST_DEVICEINTERFACE NotifacationFiler;
    ZeroMemory(&NotifacationFiler,sizeof(DEV_BROADCAST_DEVICEINTERFACE));
    NotifacationFiler.dbcc_size = sizeof(DEV_BROADCAST_DEVICEINTERFACE);
    NotifacationFiler.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
    NotifacationFiler.dbcc_classguid = GUID_DEVINTERFACE;


    for (int i = 0; i < sizeof(GUID_DEVINTERFACE)/sizeof(GUID); i++)  {
        hDevNotify = RegisterDeviceNotification((HANDLE)wid, &NotifacationFiler, DEVICE_NOTIFY_WINDOW_HANDLE);
        if (!hDevNotify) {
            qDebug()<<"注册设备失败!";
        }else{
            qDebug()<<"注册成功！";
        }
    }
}

bool USBDEVICE::nativeEventFilter(const QByteArray &eventType, void *message, long *result)
{
    Q_UNUSED(eventType);
    Q_UNUSED(result);
    MSG* msg = reinterpret_cast<MSG*>(message);
    int msgType = static_cast<int>(msg->message);
    if(msgType == WM_DEVICECHANGE){
        PDEV_BROADCAST_DEVICEINTERFACE lpdb = reinterpret_cast<PDEV_BROADCAST_DEVICEINTERFACE>(msg->lParam);
        switch (msg->wParam) {
        case DBT_DEVICEARRIVAL:
        {
            if(lpdb != nullptr && lpdb->dbcc_devicetype == DBT_DEVTYP_DEVICEINTERFACE){
                wchar_t*  c = lpdb->dbcc_name;
                QString loginStr = QString::fromWCharArray(c).toUpper();
                QString sign = loginStr.split("#")[1];
                QString VID = sign.split("&")[0];
                QString PID = sign.split("&")[1];
                emit deviceIn(VID,PID);
            }
            break;
        }
        case DBT_DEVICEREMOVECOMPLETE:{
            if(lpdb != nullptr && lpdb->dbcc_devicetype == DBT_DEVTYP_DEVICEINTERFACE){
                wchar_t*  c = lpdb->dbcc_name;
                QString loginStr = QString::fromWCharArray(c).toUpper();
                QString sign = loginStr.split("#")[1];
                QString VID = sign.split("&")[0];
                QString PID = sign.split("&")[1];
                emit deviceOut(VID,PID);
            }
            break;
        }
        default:
            break;
        }

    }
    return false;
}
