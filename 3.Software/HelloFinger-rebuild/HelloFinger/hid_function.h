#ifndef HID_FUNCTION_H
#define HID_FUNCTION_H

#include <QObject>
#include "lib/hidapi.h"

#define HID_FIXED_LEN   5

#define ACTION_FUNC_CHAT    (0x03)
#define ACTION_FUNC_POWER   (0x01)
#define ACTION_FUNC_MEDIA   (0x02)
/* 多媒体按键值 */
#define KEY_RELEASE				(0x000000)
#define KEY_MEDIA					(0x000001)
#define KEY_EXPLORER			(0x000002)
#define KEY_CALCULATOR		(0x000004)
#define KEY_SCREEN_SAVE		(0x000008)
#define KEY_MY_COMPUTER		(0x000010)
#define KEY_MINIMIZE			(0x000020)
#define KEY_RECORD				(0x000040)
#define KEY_REWIND				(0x000080)
#define KEY_EMAIL					(0x000100)
#define KEY_WB_SEARCH			(0x000200)
#define KEY_WB_FAVORITES	(0x000400)
#define KEY_WB_HOME				(0x000800)
#define KEY_WB_BACK				(0x001000)
#define KEY_WB_FORWARD		(0x002000)
#define KEY_WB_STOP				(0x004000)
#define KEY_REFRESH				(0x008000)
#define KEY_VOLUME_ADD		(0x010000)
#define KEY_VOLUME_SUM		(0x020000)
#define KEY_MUTE					(0x040000)
#define KEY_PLAY_PAUSE		(0x080000)
#define KEY_NEXT_TRACK		(0x100000)
#define KEY_PREV_TRACK		(0x200000)
#define KEY_CD_STOP				(0x400000)
#define KEY_EJECT					(0x800000)

/* 电源功能按键值 */
#define KEY_POWER		(0x01)
#define KEY_SLEEP		(0x02)
#define KEY_WAKE_UP	(0x04)


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
int HID_Set_Action_Func(hid_device *usb_handle, uint8_t func,uint32_t action);
#endif // HID_FUNCTION_H
