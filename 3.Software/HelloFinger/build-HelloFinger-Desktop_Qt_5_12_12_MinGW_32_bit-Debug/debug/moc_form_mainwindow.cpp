/****************************************************************************
** Meta object code from reading C++ file 'form_mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../HelloFinger/form_mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'form_mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Form_MainWindow_t {
    QByteArrayData data[99];
    char stringdata0[2133];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Form_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Form_MainWindow_t qt_meta_stringdata_Form_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 15), // "Form_MainWindow"
QT_MOC_LITERAL(1, 16, 16), // "Signal_AddFinger"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 7), // "uint8_t"
QT_MOC_LITERAL(4, 42, 3), // "pos"
QT_MOC_LITERAL(5, 46, 5), // "times"
QT_MOC_LITERAL(6, 52, 6), // "param1"
QT_MOC_LITERAL(7, 59, 6), // "param2"
QT_MOC_LITERAL(8, 66, 19), // "Signal_DeleteFinger"
QT_MOC_LITERAL(9, 86, 2), // "id"
QT_MOC_LITERAL(10, 89, 20), // "Signal_RefreshFinger"
QT_MOC_LITERAL(11, 110, 23), // "Signal_UpdateIndexTable"
QT_MOC_LITERAL(12, 134, 25), // "Signal_SetWindowsPassword"
QT_MOC_LITERAL(13, 160, 8), // "password"
QT_MOC_LITERAL(14, 169, 10), // "fingertype"
QT_MOC_LITERAL(15, 180, 5), // "index"
QT_MOC_LITERAL(16, 186, 18), // "Signal_SetPassword"
QT_MOC_LITERAL(17, 205, 26), // "Signal_SetAccount_Password"
QT_MOC_LITERAL(18, 232, 7), // "account"
QT_MOC_LITERAL(19, 240, 20), // "Signal_SetQuickStart"
QT_MOC_LITERAL(20, 261, 13), // "QUICK_START_e"
QT_MOC_LITERAL(21, 275, 7), // "startID"
QT_MOC_LITERAL(22, 283, 19), // "Signal_SetBreathRGB"
QT_MOC_LITERAL(23, 303, 7), // "color_R"
QT_MOC_LITERAL(24, 311, 7), // "color_G"
QT_MOC_LITERAL(25, 319, 7), // "color_B"
QT_MOC_LITERAL(26, 327, 8), // "interval"
QT_MOC_LITERAL(27, 336, 18), // "Signal_SetShortcut"
QT_MOC_LITERAL(28, 355, 4), // "func"
QT_MOC_LITERAL(29, 360, 5), // "char*"
QT_MOC_LITERAL(30, 366, 3), // "key"
QT_MOC_LITERAL(31, 370, 7), // "key_len"
QT_MOC_LITERAL(32, 378, 34), // "Signal_UpdateHideWindowChecke..."
QT_MOC_LITERAL(33, 413, 3), // "dir"
QT_MOC_LITERAL(34, 417, 20), // "Signal_SetActionFunc"
QT_MOC_LITERAL(35, 438, 6), // "action"
QT_MOC_LITERAL(36, 445, 19), // "Signal_SetFingerRGB"
QT_MOC_LITERAL(37, 465, 4), // "mode"
QT_MOC_LITERAL(38, 470, 10), // "startColor"
QT_MOC_LITERAL(39, 481, 9), // "stopColor"
QT_MOC_LITERAL(40, 491, 25), // "Signal_OpenHidewindowItem"
QT_MOC_LITERAL(41, 517, 21), // "Signal_GetFirmwareMsg"
QT_MOC_LITERAL(42, 539, 21), // "Signal_GetHardwareMsg"
QT_MOC_LITERAL(43, 561, 14), // "Slot_AddFinger"
QT_MOC_LITERAL(44, 576, 16), // "Slot_EnrollState"
QT_MOC_LITERAL(45, 593, 6), // "state1"
QT_MOC_LITERAL(46, 600, 6), // "state2"
QT_MOC_LITERAL(47, 607, 17), // "Slot_DeleteFinger"
QT_MOC_LITERAL(48, 625, 18), // "Slot_RefreshFinger"
QT_MOC_LITERAL(49, 644, 21), // "Slot_UpdateIndexTable"
QT_MOC_LITERAL(50, 666, 23), // "Slot_SetWindowsPassword"
QT_MOC_LITERAL(51, 690, 16), // "Slot_SetPassword"
QT_MOC_LITERAL(52, 707, 24), // "Slot_SetAccount_Password"
QT_MOC_LITERAL(53, 732, 18), // "Slot_SetQuickStart"
QT_MOC_LITERAL(54, 751, 17), // "Slot_SetBreathRGB"
QT_MOC_LITERAL(55, 769, 16), // "Slot_RGB_Display"
QT_MOC_LITERAL(56, 786, 20), // "Slot_ChangeItemValue"
QT_MOC_LITERAL(57, 807, 18), // "Slot_SaveItemValue"
QT_MOC_LITERAL(58, 826, 16), // "Slot_SetShortcut"
QT_MOC_LITERAL(59, 843, 25), // "Slot_DeleteListWidgetItem"
QT_MOC_LITERAL(60, 869, 18), // "Slot_Chat_Send_Msg"
QT_MOC_LITERAL(61, 888, 17), // "Slot_SetFingerRGB"
QT_MOC_LITERAL(62, 906, 28), // "Slot_Popup_ChatSettingWindow"
QT_MOC_LITERAL(63, 935, 23), // "Slot_Update_FirmwareMsg"
QT_MOC_LITERAL(64, 959, 4), // "date"
QT_MOC_LITERAL(65, 964, 7), // "version"
QT_MOC_LITERAL(66, 972, 23), // "Slot_Update_HardwareMsg"
QT_MOC_LITERAL(67, 996, 8), // "uint8_t*"
QT_MOC_LITERAL(68, 1005, 7), // "flashId"
QT_MOC_LITERAL(69, 1013, 10), // "ch9329_ver"
QT_MOC_LITERAL(70, 1024, 9), // "fpm383cSN"
QT_MOC_LITERAL(71, 1034, 15), // "Slot_ShowWindow"
QT_MOC_LITERAL(72, 1050, 9), // "Slot_Exit"
QT_MOC_LITERAL(73, 1060, 47), // "on_listWidget_task_1_customCo..."
QT_MOC_LITERAL(74, 1108, 52), // "on_listWidget_table_state_cus..."
QT_MOC_LITERAL(75, 1161, 47), // "on_listWidget_task_2_customCo..."
QT_MOC_LITERAL(76, 1209, 47), // "on_listWidget_task_3_customCo..."
QT_MOC_LITERAL(77, 1257, 47), // "on_listWidget_task_4_customCo..."
QT_MOC_LITERAL(78, 1305, 47), // "on_listWidget_task_5_customCo..."
QT_MOC_LITERAL(79, 1353, 56), // "on_listWidget_table_state_key..."
QT_MOC_LITERAL(80, 1410, 47), // "on_listWidget_task_6_customCo..."
QT_MOC_LITERAL(81, 1458, 50), // "on_listWidget_hidwindow_custo..."
QT_MOC_LITERAL(82, 1509, 38), // "on_pushButton_chat_copy_answe..."
QT_MOC_LITERAL(83, 1548, 39), // "on_pushButton_action_play_pau..."
QT_MOC_LITERAL(84, 1588, 39), // "on_pushButton_action_calculat..."
QT_MOC_LITERAL(85, 1628, 33), // "on_pushButton_action_chat_cli..."
QT_MOC_LITERAL(86, 1662, 37), // "on_pushButton_action_computer..."
QT_MOC_LITERAL(87, 1700, 34), // "on_pushButton_action_email_cl..."
QT_MOC_LITERAL(88, 1735, 37), // "on_pushButton_action_explorer..."
QT_MOC_LITERAL(89, 1773, 33), // "on_pushButton_action_mute_cli..."
QT_MOC_LITERAL(90, 1807, 34), // "on_pushButton_action_power_cl..."
QT_MOC_LITERAL(91, 1842, 40), // "on_pushButton_action_screen_s..."
QT_MOC_LITERAL(92, 1883, 34), // "on_pushButton_action_sleep_cl..."
QT_MOC_LITERAL(93, 1918, 35), // "on_pushButton_action_weakup_c..."
QT_MOC_LITERAL(94, 1954, 35), // "on_pushButton_RGB_next_page_c..."
QT_MOC_LITERAL(95, 1990, 35), // "on_pushButton_RGB_last_page_c..."
QT_MOC_LITERAL(96, 2026, 38), // "on_pushButton_get_hardware_ms..."
QT_MOC_LITERAL(97, 2065, 38), // "on_pushButton_get_firmware_ms..."
QT_MOC_LITERAL(98, 2104, 28) // "on_pushButton_update_clicked"

    },
    "Form_MainWindow\0Signal_AddFinger\0\0"
    "uint8_t\0pos\0times\0param1\0param2\0"
    "Signal_DeleteFinger\0id\0Signal_RefreshFinger\0"
    "Signal_UpdateIndexTable\0"
    "Signal_SetWindowsPassword\0password\0"
    "fingertype\0index\0Signal_SetPassword\0"
    "Signal_SetAccount_Password\0account\0"
    "Signal_SetQuickStart\0QUICK_START_e\0"
    "startID\0Signal_SetBreathRGB\0color_R\0"
    "color_G\0color_B\0interval\0Signal_SetShortcut\0"
    "func\0char*\0key\0key_len\0"
    "Signal_UpdateHideWindowCheckedItem\0"
    "dir\0Signal_SetActionFunc\0action\0"
    "Signal_SetFingerRGB\0mode\0startColor\0"
    "stopColor\0Signal_OpenHidewindowItem\0"
    "Signal_GetFirmwareMsg\0Signal_GetHardwareMsg\0"
    "Slot_AddFinger\0Slot_EnrollState\0state1\0"
    "state2\0Slot_DeleteFinger\0Slot_RefreshFinger\0"
    "Slot_UpdateIndexTable\0Slot_SetWindowsPassword\0"
    "Slot_SetPassword\0Slot_SetAccount_Password\0"
    "Slot_SetQuickStart\0Slot_SetBreathRGB\0"
    "Slot_RGB_Display\0Slot_ChangeItemValue\0"
    "Slot_SaveItemValue\0Slot_SetShortcut\0"
    "Slot_DeleteListWidgetItem\0Slot_Chat_Send_Msg\0"
    "Slot_SetFingerRGB\0Slot_Popup_ChatSettingWindow\0"
    "Slot_Update_FirmwareMsg\0date\0version\0"
    "Slot_Update_HardwareMsg\0uint8_t*\0"
    "flashId\0ch9329_ver\0fpm383cSN\0"
    "Slot_ShowWindow\0Slot_Exit\0"
    "on_listWidget_task_1_customContextMenuRequested\0"
    "on_listWidget_table_state_customContextMenuRequested\0"
    "on_listWidget_task_2_customContextMenuRequested\0"
    "on_listWidget_task_3_customContextMenuRequested\0"
    "on_listWidget_task_4_customContextMenuRequested\0"
    "on_listWidget_task_5_customContextMenuRequested\0"
    "on_listWidget_table_state_key_customContextMenuRequested\0"
    "on_listWidget_task_6_customContextMenuRequested\0"
    "on_listWidget_hidwindow_customContextMenuRequested\0"
    "on_pushButton_chat_copy_answer_clicked\0"
    "on_pushButton_action_play_pause_clicked\0"
    "on_pushButton_action_calculator_clicked\0"
    "on_pushButton_action_chat_clicked\0"
    "on_pushButton_action_computer_clicked\0"
    "on_pushButton_action_email_clicked\0"
    "on_pushButton_action_explorer_clicked\0"
    "on_pushButton_action_mute_clicked\0"
    "on_pushButton_action_power_clicked\0"
    "on_pushButton_action_screen_save_clicked\0"
    "on_pushButton_action_sleep_clicked\0"
    "on_pushButton_action_weakup_clicked\0"
    "on_pushButton_RGB_next_page_clicked\0"
    "on_pushButton_RGB_last_page_clicked\0"
    "on_pushButton_get_hardware_msg_clicked\0"
    "on_pushButton_get_firmware_msg_clicked\0"
    "on_pushButton_update_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Form_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      64,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      16,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    4,  334,    2, 0x06 /* Public */,
       8,    1,  343,    2, 0x06 /* Public */,
      10,    0,  346,    2, 0x06 /* Public */,
      11,    0,  347,    2, 0x06 /* Public */,
      12,    3,  348,    2, 0x06 /* Public */,
      16,    3,  355,    2, 0x06 /* Public */,
      17,    4,  362,    2, 0x06 /* Public */,
      19,    3,  371,    2, 0x06 /* Public */,
      22,    4,  378,    2, 0x06 /* Public */,
      27,    5,  387,    2, 0x06 /* Public */,
      32,    1,  398,    2, 0x06 /* Public */,
      34,    2,  401,    2, 0x06 /* Public */,
      36,    4,  406,    2, 0x06 /* Public */,
      40,    0,  415,    2, 0x06 /* Public */,
      41,    0,  416,    2, 0x06 /* Public */,
      42,    0,  417,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      43,    0,  418,    2, 0x0a /* Public */,
      44,    2,  419,    2, 0x0a /* Public */,
      47,    0,  424,    2, 0x0a /* Public */,
      48,    0,  425,    2, 0x0a /* Public */,
      49,    0,  426,    2, 0x0a /* Public */,
      50,    0,  427,    2, 0x0a /* Public */,
      51,    0,  428,    2, 0x0a /* Public */,
      52,    0,  429,    2, 0x0a /* Public */,
      53,    1,  430,    2, 0x0a /* Public */,
      54,    0,  433,    2, 0x0a /* Public */,
      55,    0,  434,    2, 0x0a /* Public */,
      56,    0,  435,    2, 0x0a /* Public */,
      57,    0,  436,    2, 0x0a /* Public */,
      58,    0,  437,    2, 0x0a /* Public */,
      59,    0,  438,    2, 0x0a /* Public */,
      60,    0,  439,    2, 0x0a /* Public */,
      61,    0,  440,    2, 0x0a /* Public */,
      62,    0,  441,    2, 0x0a /* Public */,
      63,    2,  442,    2, 0x0a /* Public */,
      66,    3,  447,    2, 0x0a /* Public */,
      71,    0,  454,    2, 0x08 /* Private */,
      72,    0,  455,    2, 0x08 /* Private */,
      73,    1,  456,    2, 0x08 /* Private */,
      74,    1,  459,    2, 0x08 /* Private */,
      75,    1,  462,    2, 0x08 /* Private */,
      76,    1,  465,    2, 0x08 /* Private */,
      77,    1,  468,    2, 0x08 /* Private */,
      78,    1,  471,    2, 0x08 /* Private */,
      79,    1,  474,    2, 0x08 /* Private */,
      80,    1,  477,    2, 0x08 /* Private */,
      81,    1,  480,    2, 0x08 /* Private */,
      82,    0,  483,    2, 0x08 /* Private */,
      83,    0,  484,    2, 0x08 /* Private */,
      84,    0,  485,    2, 0x08 /* Private */,
      85,    0,  486,    2, 0x08 /* Private */,
      86,    0,  487,    2, 0x08 /* Private */,
      87,    0,  488,    2, 0x08 /* Private */,
      88,    0,  489,    2, 0x08 /* Private */,
      89,    0,  490,    2, 0x08 /* Private */,
      90,    0,  491,    2, 0x08 /* Private */,
      91,    0,  492,    2, 0x08 /* Private */,
      92,    0,  493,    2, 0x08 /* Private */,
      93,    0,  494,    2, 0x08 /* Private */,
      94,    0,  495,    2, 0x08 /* Private */,
      95,    0,  496,    2, 0x08 /* Private */,
      96,    0,  497,    2, 0x08 /* Private */,
      97,    0,  498,    2, 0x08 /* Private */,
      98,    0,  499,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 3,    4,    5,    6,    7,
    QMetaType::Void, 0x80000000 | 3,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 3, 0x80000000 | 3,   13,   14,   15,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 3, 0x80000000 | 3,   13,   14,   15,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, 0x80000000 | 3, 0x80000000 | 3,   18,   13,   14,   15,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 20, 0x80000000 | 3,   14,   21,   15,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 3,   23,   24,   25,   26,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 29, 0x80000000 | 3, 0x80000000 | 3,   14,   28,   30,   31,   15,
    QMetaType::Void, QMetaType::Int,   33,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,   28,   35,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 3,   37,   38,   39,   26,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,   45,   46,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 20,   21,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 29, 0x80000000 | 29,   64,   65,
    QMetaType::Void, 0x80000000 | 67, QMetaType::Char, 0x80000000 | 29,   68,   69,   70,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,    4,
    QMetaType::Void, QMetaType::QPoint,    4,
    QMetaType::Void, QMetaType::QPoint,    4,
    QMetaType::Void, QMetaType::QPoint,    4,
    QMetaType::Void, QMetaType::QPoint,    4,
    QMetaType::Void, QMetaType::QPoint,    4,
    QMetaType::Void, QMetaType::QPoint,    4,
    QMetaType::Void, QMetaType::QPoint,    4,
    QMetaType::Void, QMetaType::QPoint,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Form_MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Form_MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Signal_AddFinger((*reinterpret_cast< uint8_t(*)>(_a[1])),(*reinterpret_cast< uint8_t(*)>(_a[2])),(*reinterpret_cast< uint8_t(*)>(_a[3])),(*reinterpret_cast< uint8_t(*)>(_a[4]))); break;
        case 1: _t->Signal_DeleteFinger((*reinterpret_cast< uint8_t(*)>(_a[1]))); break;
        case 2: _t->Signal_RefreshFinger(); break;
        case 3: _t->Signal_UpdateIndexTable(); break;
        case 4: _t->Signal_SetWindowsPassword((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< uint8_t(*)>(_a[2])),(*reinterpret_cast< uint8_t(*)>(_a[3]))); break;
        case 5: _t->Signal_SetPassword((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< uint8_t(*)>(_a[2])),(*reinterpret_cast< uint8_t(*)>(_a[3]))); break;
        case 6: _t->Signal_SetAccount_Password((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< uint8_t(*)>(_a[3])),(*reinterpret_cast< uint8_t(*)>(_a[4]))); break;
        case 7: _t->Signal_SetQuickStart((*reinterpret_cast< uint8_t(*)>(_a[1])),(*reinterpret_cast< QUICK_START_e(*)>(_a[2])),(*reinterpret_cast< uint8_t(*)>(_a[3]))); break;
        case 8: _t->Signal_SetBreathRGB((*reinterpret_cast< uint8_t(*)>(_a[1])),(*reinterpret_cast< uint8_t(*)>(_a[2])),(*reinterpret_cast< uint8_t(*)>(_a[3])),(*reinterpret_cast< uint8_t(*)>(_a[4]))); break;
        case 9: _t->Signal_SetShortcut((*reinterpret_cast< uint8_t(*)>(_a[1])),(*reinterpret_cast< uint8_t(*)>(_a[2])),(*reinterpret_cast< char*(*)>(_a[3])),(*reinterpret_cast< uint8_t(*)>(_a[4])),(*reinterpret_cast< uint8_t(*)>(_a[5]))); break;
        case 10: _t->Signal_UpdateHideWindowCheckedItem((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->Signal_SetActionFunc((*reinterpret_cast< uint8_t(*)>(_a[1])),(*reinterpret_cast< uint8_t(*)>(_a[2]))); break;
        case 12: _t->Signal_SetFingerRGB((*reinterpret_cast< uint8_t(*)>(_a[1])),(*reinterpret_cast< uint8_t(*)>(_a[2])),(*reinterpret_cast< uint8_t(*)>(_a[3])),(*reinterpret_cast< uint8_t(*)>(_a[4]))); break;
        case 13: _t->Signal_OpenHidewindowItem(); break;
        case 14: _t->Signal_GetFirmwareMsg(); break;
        case 15: _t->Signal_GetHardwareMsg(); break;
        case 16: _t->Slot_AddFinger(); break;
        case 17: _t->Slot_EnrollState((*reinterpret_cast< uint8_t(*)>(_a[1])),(*reinterpret_cast< uint8_t(*)>(_a[2]))); break;
        case 18: _t->Slot_DeleteFinger(); break;
        case 19: _t->Slot_RefreshFinger(); break;
        case 20: _t->Slot_UpdateIndexTable(); break;
        case 21: _t->Slot_SetWindowsPassword(); break;
        case 22: _t->Slot_SetPassword(); break;
        case 23: _t->Slot_SetAccount_Password(); break;
        case 24: _t->Slot_SetQuickStart((*reinterpret_cast< QUICK_START_e(*)>(_a[1]))); break;
        case 25: _t->Slot_SetBreathRGB(); break;
        case 26: _t->Slot_RGB_Display(); break;
        case 27: _t->Slot_ChangeItemValue(); break;
        case 28: _t->Slot_SaveItemValue(); break;
        case 29: _t->Slot_SetShortcut(); break;
        case 30: _t->Slot_DeleteListWidgetItem(); break;
        case 31: _t->Slot_Chat_Send_Msg(); break;
        case 32: _t->Slot_SetFingerRGB(); break;
        case 33: _t->Slot_Popup_ChatSettingWindow(); break;
        case 34: _t->Slot_Update_FirmwareMsg((*reinterpret_cast< char*(*)>(_a[1])),(*reinterpret_cast< char*(*)>(_a[2]))); break;
        case 35: _t->Slot_Update_HardwareMsg((*reinterpret_cast< uint8_t*(*)>(_a[1])),(*reinterpret_cast< char(*)>(_a[2])),(*reinterpret_cast< char*(*)>(_a[3]))); break;
        case 36: _t->Slot_ShowWindow(); break;
        case 37: _t->Slot_Exit(); break;
        case 38: _t->on_listWidget_task_1_customContextMenuRequested((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 39: _t->on_listWidget_table_state_customContextMenuRequested((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 40: _t->on_listWidget_task_2_customContextMenuRequested((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 41: _t->on_listWidget_task_3_customContextMenuRequested((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 42: _t->on_listWidget_task_4_customContextMenuRequested((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 43: _t->on_listWidget_task_5_customContextMenuRequested((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 44: _t->on_listWidget_table_state_key_customContextMenuRequested((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 45: _t->on_listWidget_task_6_customContextMenuRequested((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 46: _t->on_listWidget_hidwindow_customContextMenuRequested((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 47: _t->on_pushButton_chat_copy_answer_clicked(); break;
        case 48: _t->on_pushButton_action_play_pause_clicked(); break;
        case 49: _t->on_pushButton_action_calculator_clicked(); break;
        case 50: _t->on_pushButton_action_chat_clicked(); break;
        case 51: _t->on_pushButton_action_computer_clicked(); break;
        case 52: _t->on_pushButton_action_email_clicked(); break;
        case 53: _t->on_pushButton_action_explorer_clicked(); break;
        case 54: _t->on_pushButton_action_mute_clicked(); break;
        case 55: _t->on_pushButton_action_power_clicked(); break;
        case 56: _t->on_pushButton_action_screen_save_clicked(); break;
        case 57: _t->on_pushButton_action_sleep_clicked(); break;
        case 58: _t->on_pushButton_action_weakup_clicked(); break;
        case 59: _t->on_pushButton_RGB_next_page_clicked(); break;
        case 60: _t->on_pushButton_RGB_last_page_clicked(); break;
        case 61: _t->on_pushButton_get_hardware_msg_clicked(); break;
        case 62: _t->on_pushButton_get_firmware_msg_clicked(); break;
        case 63: _t->on_pushButton_update_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Form_MainWindow::*)(uint8_t , uint8_t , uint8_t , uint8_t );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Form_MainWindow::Signal_AddFinger)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Form_MainWindow::*)(uint8_t );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Form_MainWindow::Signal_DeleteFinger)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Form_MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Form_MainWindow::Signal_RefreshFinger)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Form_MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Form_MainWindow::Signal_UpdateIndexTable)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Form_MainWindow::*)(QString , uint8_t , uint8_t );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Form_MainWindow::Signal_SetWindowsPassword)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (Form_MainWindow::*)(QString , uint8_t , uint8_t );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Form_MainWindow::Signal_SetPassword)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (Form_MainWindow::*)(QString , QString , uint8_t , uint8_t );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Form_MainWindow::Signal_SetAccount_Password)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (Form_MainWindow::*)(uint8_t , QUICK_START_e , uint8_t );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Form_MainWindow::Signal_SetQuickStart)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (Form_MainWindow::*)(uint8_t , uint8_t , uint8_t , uint8_t );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Form_MainWindow::Signal_SetBreathRGB)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (Form_MainWindow::*)(uint8_t , uint8_t , char * , uint8_t , uint8_t );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Form_MainWindow::Signal_SetShortcut)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (Form_MainWindow::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Form_MainWindow::Signal_UpdateHideWindowCheckedItem)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (Form_MainWindow::*)(uint8_t , uint8_t );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Form_MainWindow::Signal_SetActionFunc)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (Form_MainWindow::*)(uint8_t , uint8_t , uint8_t , uint8_t );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Form_MainWindow::Signal_SetFingerRGB)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (Form_MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Form_MainWindow::Signal_OpenHidewindowItem)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (Form_MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Form_MainWindow::Signal_GetFirmwareMsg)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (Form_MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Form_MainWindow::Signal_GetHardwareMsg)) {
                *result = 15;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Form_MainWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_Form_MainWindow.data,
    qt_meta_data_Form_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Form_MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Form_MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Form_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int Form_MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 64)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 64;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 64)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 64;
    }
    return _id;
}

// SIGNAL 0
void Form_MainWindow::Signal_AddFinger(uint8_t _t1, uint8_t _t2, uint8_t _t3, uint8_t _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Form_MainWindow::Signal_DeleteFinger(uint8_t _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Form_MainWindow::Signal_RefreshFinger()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Form_MainWindow::Signal_UpdateIndexTable()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void Form_MainWindow::Signal_SetWindowsPassword(QString _t1, uint8_t _t2, uint8_t _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Form_MainWindow::Signal_SetPassword(QString _t1, uint8_t _t2, uint8_t _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void Form_MainWindow::Signal_SetAccount_Password(QString _t1, QString _t2, uint8_t _t3, uint8_t _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void Form_MainWindow::Signal_SetQuickStart(uint8_t _t1, QUICK_START_e _t2, uint8_t _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void Form_MainWindow::Signal_SetBreathRGB(uint8_t _t1, uint8_t _t2, uint8_t _t3, uint8_t _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void Form_MainWindow::Signal_SetShortcut(uint8_t _t1, uint8_t _t2, char * _t3, uint8_t _t4, uint8_t _t5)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void Form_MainWindow::Signal_UpdateHideWindowCheckedItem(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void Form_MainWindow::Signal_SetActionFunc(uint8_t _t1, uint8_t _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void Form_MainWindow::Signal_SetFingerRGB(uint8_t _t1, uint8_t _t2, uint8_t _t3, uint8_t _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void Form_MainWindow::Signal_OpenHidewindowItem()
{
    QMetaObject::activate(this, &staticMetaObject, 13, nullptr);
}

// SIGNAL 14
void Form_MainWindow::Signal_GetFirmwareMsg()
{
    QMetaObject::activate(this, &staticMetaObject, 14, nullptr);
}

// SIGNAL 15
void Form_MainWindow::Signal_GetHardwareMsg()
{
    QMetaObject::activate(this, &staticMetaObject, 15, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
