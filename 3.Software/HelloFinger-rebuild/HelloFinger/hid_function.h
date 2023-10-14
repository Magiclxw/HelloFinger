#ifndef HID_FUNCTION_H
#define HID_FUNCTION_H

#include <QObject>
#include "lib/hidapi.h"

#define HID_FIXED_LEN   5


typedef enum{
    TYPE_Windows_Password = 0,
    TYPE_Password,
    TYPE_Account_Password,
    TYPE_Shortcut,
    TYPE_QuickStart,
    TYPE_KEY_Windows_Password,
    TYPE_KEY_Password,
    TYPE_KEY_Account_Password,
    TYPE_KEY_Shortcut,
    TYPE_KEY_QuickStart,
}CMD_TYPE_e;

typedef enum
{
    QUICK_START_1,
    QUICK_START_2,
    QUICK_START_3,
    QUICK_START_4,
    QUICK_START_5,
    QUICK_START_6,
    QUICK_START_MAX,
}QUICK_START_e;

typedef enum {
    FINGER,
    FINGER_KEY
}Finger_Type_e ;

class Hid_Function : public QObject
{
    Q_OBJECT
public:
    explicit Hid_Function(QObject *parent = nullptr);

signals:

};

int HID_Get_TableState(hid_device *usb_handle);
int HID_Add_Finger(hid_device *usb_handle,uint8_t id,uint8_t param1,uint8_t param2,uint8_t times);
int HID_Delete_Finger(hid_device *usb_handle,uint8_t id);
int HID_Send_WindowsPassword(hid_device *usb_handle,Finger_Type_e fingertype,QString password,uint8_t index);
int HID_Send_Password(hid_device *usb_handle,Finger_Type_e fingertype,QString password,uint8_t index);
int HID_Send_Account_Password(hid_device *usb_handle,Finger_Type_e fingertype,QString account,QString password,uint8_t index);
int HID_Send_Shortcut(hid_device *usb_handle,Finger_Type_e fingertype,uint8_t func,char* key,uint8_t key_len,uint8_t index);
int HID_Send_QuickStart(hid_device *usb_handle,Finger_Type_e fingertype,QUICK_START_e startID,uint8_t index);
int HID_Send_Breath_RGB(hid_device *usb_handle,uint8_t color_R,uint8_t color_G,uint8_t color_B,uint8_t interval);
int HID_Get_FW_HW_Msg(hid_device *usb_handle);
#endif // HID_FUNCTION_H
