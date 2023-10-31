#ifndef HID_FUNCTION_H
#define HID_FUNCTION_H

#include <QObject>
#include "lib/hidapi.h"

#define HID_FIXED_LEN   5

#define ACTION_FUNC_CHAT    (0x03)
#define ACTION_FUNC_POWER   (0x01)
#define ACTION_FUNC_MEDIA   (0x02)
/* 多媒体按键值 */
typedef enum MEDIA_KEY_TYPE
{
    MEDIA_KEY_TYPE_KEY_RELEASE = 0,
    MEDIA_KEY_TYPE_KEY_MEDIA,
    MEDIA_KEY_TYPE_KEY_EXPLORER,
    MEDIA_KEY_TYPE_KEY_CALCULATOR,
    MEDIA_KEY_TYPE_KEY_SCREEN_SAVE,
    MEDIA_KEY_TYPE_KEY_MY_COMPUTER,
    MEDIA_KEY_TYPE_KEY_MINIMIZE,
    MEDIA_KEY_TYPE_KEY_RECORD,
    MEDIA_KEY_TYPE_KEY_REWIND,
    MEDIA_KEY_TYPE_KEY_EMAIL,
    MEDIA_KEY_TYPE_KEY_WB_SEARCH,
    MEDIA_KEY_TYPE_KEY_WB_FAVORITES,
    MEDIA_KEY_TYPE_KEY_WB_HOME,
    MEDIA_KEY_TYPE_KEY_WB_BACK,
    MEDIA_KEY_TYPE_KEY_WB_FORWARD,
    MEDIA_KEY_TYPE_KEY_WB_STOP,
    MEDIA_KEY_TYPE_KEY_REFRESH,
    MEDIA_KEY_TYPE_KEY_VOLUME_ADD,
    MEDIA_KEY_TYPE_KEY_VOLUME_SUM,
    MEDIA_KEY_TYPE_KEY_MUTE,
    MEDIA_KEY_TYPE_KEY_PLAY_PAUSE,
    MEDIA_KEY_TYPE_KEY_NEXT_TRACK,
    MEDIA_KEY_TYPE_KEY_PREV_TRACK,
    MEDIA_KEY_TYPE_KEY_CD_STOP,
    MEDIA_KEY_TYPE_KEY_EJECT,
}MEDIA_KEY_TYPE_e;
/* 电源功能按键值 */
typedef enum POWER_KEY_TYPE
{
    POWER_KEY_TYPE_KEY_RELEASE = 0,
    POWER_KEY_TYPE_KEY_POWER,
    POWER_KEY_TYPE_KEY_SLEEP,
    POWER_KEY_TYPE_KEY_WAKE_UP
}POWER_KEY_TYPE_e;

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

typedef enum LED_COLOR_
{
    LED_COLOR_BLUE = 0x01,
    LED_COLOR_GREEN = 0x02,
    LED_COLOR_RED = 0x04
}LED_COLOR_e;


#define ENROLL_PARAM_LED_OFF  0x01
#define ENROLL_PARAM_PRETREATMENT_ENABLE 0x02
#define ENROLL_PARAM_CRITICAL_PROCESS_DISABLE 0x04
#define ENROLL_PARAM_COVER_ID_ENABLE   0x08
#define ENROLL_PARAM_REENROLL_DISABLE 0x01
#define ENROLL_PARAM_FINGER_LEAVE_ENABLE 0x02


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
int HID_Send_Finger_RGB(hid_device *usb_handle,uint8_t mode,uint8_t startColor,uint8_t stopColor,uint8_t cycle);
int HID_Get_FW_HW_Msg(hid_device *usb_handle);
int HID_Set_Action_Func(hid_device *usb_handle, uint8_t func,uint8_t action);
#endif // HID_FUNCTION_H
