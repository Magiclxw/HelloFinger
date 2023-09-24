#ifndef HID_FUNCTION_H
#define HID_FUNCTION_H

#include <QObject>
#include "lib/hidapi.h"

typedef enum{
    TYPE_Windows_Password = 0,
    TYPE_Password,
    TYPE_Account_Password,
    TYPE_Shortcut
}CMD_TYPE_e;

class Hid_Function : public QObject
{
    Q_OBJECT
public:
    explicit Hid_Function(QObject *parent = nullptr);

signals:

};

int HID_Get_TableState(hid_device *usb_handle);
int HID_Add_Finger(hid_device *usb_handle,uint8_t *param,uint8_t times,uint8_t id);
int HID_Delete_Finger(hid_device *usb_handle,uint8_t id);
int HID_Send_WindowsPassword(hid_device *usb_handle,QString password,uint8_t index);
int HID_Send_Account_Password(hid_device *usb_handle,QString account,QString password,uint8_t index);
int HID_Send_Breath_RGB(hid_device *usb_handle,uint8_t color_R,uint8_t color_G,uint8_t color_B,uint8_t interval);

#endif // HID_FUNCTION_H
