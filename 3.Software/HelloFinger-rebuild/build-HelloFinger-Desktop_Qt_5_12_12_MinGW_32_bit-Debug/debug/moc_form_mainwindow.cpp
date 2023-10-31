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
    QByteArrayData data[84];
    char stringdata0[1828];
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
QT_MOC_LITERAL(40, 491, 14), // "Slot_AddFinger"
QT_MOC_LITERAL(41, 506, 16), // "Slot_EnrollState"
QT_MOC_LITERAL(42, 523, 6), // "state1"
QT_MOC_LITERAL(43, 530, 6), // "state2"
QT_MOC_LITERAL(44, 537, 17), // "Slot_DeleteFinger"
QT_MOC_LITERAL(45, 555, 18), // "Slot_RefreshFinger"
QT_MOC_LITERAL(46, 574, 21), // "Slot_UpdateIndexTable"
QT_MOC_LITERAL(47, 596, 23), // "Slot_SetWindowsPassword"
QT_MOC_LITERAL(48, 620, 16), // "Slot_SetPassword"
QT_MOC_LITERAL(49, 637, 24), // "Slot_SetAccount_Password"
QT_MOC_LITERAL(50, 662, 18), // "Slot_SetQuickStart"
QT_MOC_LITERAL(51, 681, 17), // "Slot_SetBreathRGB"
QT_MOC_LITERAL(52, 699, 16), // "Slot_RGB_Display"
QT_MOC_LITERAL(53, 716, 20), // "Slot_ChangeItemValue"
QT_MOC_LITERAL(54, 737, 18), // "Slot_SaveItemValue"
QT_MOC_LITERAL(55, 756, 16), // "Slot_SetShortcut"
QT_MOC_LITERAL(56, 773, 25), // "Slot_DeleteListWidgetItem"
QT_MOC_LITERAL(57, 799, 18), // "Slot_Chat_Send_Msg"
QT_MOC_LITERAL(58, 818, 17), // "Slot_SetFingerRGB"
QT_MOC_LITERAL(59, 836, 15), // "Slot_ShowWindow"
QT_MOC_LITERAL(60, 852, 9), // "Slot_Exit"
QT_MOC_LITERAL(61, 862, 47), // "on_listWidget_task_1_customCo..."
QT_MOC_LITERAL(62, 910, 52), // "on_listWidget_table_state_cus..."
QT_MOC_LITERAL(63, 963, 47), // "on_listWidget_task_2_customCo..."
QT_MOC_LITERAL(64, 1011, 47), // "on_listWidget_task_3_customCo..."
QT_MOC_LITERAL(65, 1059, 47), // "on_listWidget_task_4_customCo..."
QT_MOC_LITERAL(66, 1107, 47), // "on_listWidget_task_5_customCo..."
QT_MOC_LITERAL(67, 1155, 56), // "on_listWidget_table_state_key..."
QT_MOC_LITERAL(68, 1212, 47), // "on_listWidget_task_6_customCo..."
QT_MOC_LITERAL(69, 1260, 50), // "on_listWidget_hidwindow_custo..."
QT_MOC_LITERAL(70, 1311, 38), // "on_pushButton_chat_copy_answe..."
QT_MOC_LITERAL(71, 1350, 39), // "on_pushButton_action_play_pau..."
QT_MOC_LITERAL(72, 1390, 39), // "on_pushButton_action_calculat..."
QT_MOC_LITERAL(73, 1430, 33), // "on_pushButton_action_chat_cli..."
QT_MOC_LITERAL(74, 1464, 37), // "on_pushButton_action_computer..."
QT_MOC_LITERAL(75, 1502, 34), // "on_pushButton_action_email_cl..."
QT_MOC_LITERAL(76, 1537, 37), // "on_pushButton_action_explorer..."
QT_MOC_LITERAL(77, 1575, 33), // "on_pushButton_action_mute_cli..."
QT_MOC_LITERAL(78, 1609, 34), // "on_pushButton_action_power_cl..."
QT_MOC_LITERAL(79, 1644, 40), // "on_pushButton_action_screen_s..."
QT_MOC_LITERAL(80, 1685, 34), // "on_pushButton_action_sleep_cl..."
QT_MOC_LITERAL(81, 1720, 35), // "on_pushButton_action_weakup_c..."
QT_MOC_LITERAL(82, 1756, 35), // "on_pushButton_RGB_next_page_c..."
QT_MOC_LITERAL(83, 1792, 35) // "on_pushButton_RGB_last_page_c..."

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
    "stopColor\0Slot_AddFinger\0Slot_EnrollState\0"
    "state1\0state2\0Slot_DeleteFinger\0"
    "Slot_RefreshFinger\0Slot_UpdateIndexTable\0"
    "Slot_SetWindowsPassword\0Slot_SetPassword\0"
    "Slot_SetAccount_Password\0Slot_SetQuickStart\0"
    "Slot_SetBreathRGB\0Slot_RGB_Display\0"
    "Slot_ChangeItemValue\0Slot_SaveItemValue\0"
    "Slot_SetShortcut\0Slot_DeleteListWidgetItem\0"
    "Slot_Chat_Send_Msg\0Slot_SetFingerRGB\0"
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
    "on_pushButton_RGB_last_page_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Form_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      55,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      13,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    4,  289,    2, 0x06 /* Public */,
       8,    1,  298,    2, 0x06 /* Public */,
      10,    0,  301,    2, 0x06 /* Public */,
      11,    0,  302,    2, 0x06 /* Public */,
      12,    3,  303,    2, 0x06 /* Public */,
      16,    3,  310,    2, 0x06 /* Public */,
      17,    4,  317,    2, 0x06 /* Public */,
      19,    3,  326,    2, 0x06 /* Public */,
      22,    4,  333,    2, 0x06 /* Public */,
      27,    5,  342,    2, 0x06 /* Public */,
      32,    1,  353,    2, 0x06 /* Public */,
      34,    2,  356,    2, 0x06 /* Public */,
      36,    4,  361,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      40,    0,  370,    2, 0x0a /* Public */,
      41,    2,  371,    2, 0x0a /* Public */,
      44,    0,  376,    2, 0x0a /* Public */,
      45,    0,  377,    2, 0x0a /* Public */,
      46,    0,  378,    2, 0x0a /* Public */,
      47,    0,  379,    2, 0x0a /* Public */,
      48,    0,  380,    2, 0x0a /* Public */,
      49,    0,  381,    2, 0x0a /* Public */,
      50,    1,  382,    2, 0x0a /* Public */,
      51,    0,  385,    2, 0x0a /* Public */,
      52,    0,  386,    2, 0x0a /* Public */,
      53,    0,  387,    2, 0x0a /* Public */,
      54,    0,  388,    2, 0x0a /* Public */,
      55,    0,  389,    2, 0x0a /* Public */,
      56,    0,  390,    2, 0x0a /* Public */,
      57,    0,  391,    2, 0x0a /* Public */,
      58,    0,  392,    2, 0x0a /* Public */,
      59,    0,  393,    2, 0x08 /* Private */,
      60,    0,  394,    2, 0x08 /* Private */,
      61,    1,  395,    2, 0x08 /* Private */,
      62,    1,  398,    2, 0x08 /* Private */,
      63,    1,  401,    2, 0x08 /* Private */,
      64,    1,  404,    2, 0x08 /* Private */,
      65,    1,  407,    2, 0x08 /* Private */,
      66,    1,  410,    2, 0x08 /* Private */,
      67,    1,  413,    2, 0x08 /* Private */,
      68,    1,  416,    2, 0x08 /* Private */,
      69,    1,  419,    2, 0x08 /* Private */,
      70,    0,  422,    2, 0x08 /* Private */,
      71,    0,  423,    2, 0x08 /* Private */,
      72,    0,  424,    2, 0x08 /* Private */,
      73,    0,  425,    2, 0x08 /* Private */,
      74,    0,  426,    2, 0x08 /* Private */,
      75,    0,  427,    2, 0x08 /* Private */,
      76,    0,  428,    2, 0x08 /* Private */,
      77,    0,  429,    2, 0x08 /* Private */,
      78,    0,  430,    2, 0x08 /* Private */,
      79,    0,  431,    2, 0x08 /* Private */,
      80,    0,  432,    2, 0x08 /* Private */,
      81,    0,  433,    2, 0x08 /* Private */,
      82,    0,  434,    2, 0x08 /* Private */,
      83,    0,  435,    2, 0x08 /* Private */,

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

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,   42,   43,
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
        case 13: _t->Slot_AddFinger(); break;
        case 14: _t->Slot_EnrollState((*reinterpret_cast< uint8_t(*)>(_a[1])),(*reinterpret_cast< uint8_t(*)>(_a[2]))); break;
        case 15: _t->Slot_DeleteFinger(); break;
        case 16: _t->Slot_RefreshFinger(); break;
        case 17: _t->Slot_UpdateIndexTable(); break;
        case 18: _t->Slot_SetWindowsPassword(); break;
        case 19: _t->Slot_SetPassword(); break;
        case 20: _t->Slot_SetAccount_Password(); break;
        case 21: _t->Slot_SetQuickStart((*reinterpret_cast< QUICK_START_e(*)>(_a[1]))); break;
        case 22: _t->Slot_SetBreathRGB(); break;
        case 23: _t->Slot_RGB_Display(); break;
        case 24: _t->Slot_ChangeItemValue(); break;
        case 25: _t->Slot_SaveItemValue(); break;
        case 26: _t->Slot_SetShortcut(); break;
        case 27: _t->Slot_DeleteListWidgetItem(); break;
        case 28: _t->Slot_Chat_Send_Msg(); break;
        case 29: _t->Slot_SetFingerRGB(); break;
        case 30: _t->Slot_ShowWindow(); break;
        case 31: _t->Slot_Exit(); break;
        case 32: _t->on_listWidget_task_1_customContextMenuRequested((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 33: _t->on_listWidget_table_state_customContextMenuRequested((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 34: _t->on_listWidget_task_2_customContextMenuRequested((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 35: _t->on_listWidget_task_3_customContextMenuRequested((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 36: _t->on_listWidget_task_4_customContextMenuRequested((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 37: _t->on_listWidget_task_5_customContextMenuRequested((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 38: _t->on_listWidget_table_state_key_customContextMenuRequested((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 39: _t->on_listWidget_task_6_customContextMenuRequested((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 40: _t->on_listWidget_hidwindow_customContextMenuRequested((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 41: _t->on_pushButton_chat_copy_answer_clicked(); break;
        case 42: _t->on_pushButton_action_play_pause_clicked(); break;
        case 43: _t->on_pushButton_action_calculator_clicked(); break;
        case 44: _t->on_pushButton_action_chat_clicked(); break;
        case 45: _t->on_pushButton_action_computer_clicked(); break;
        case 46: _t->on_pushButton_action_email_clicked(); break;
        case 47: _t->on_pushButton_action_explorer_clicked(); break;
        case 48: _t->on_pushButton_action_mute_clicked(); break;
        case 49: _t->on_pushButton_action_power_clicked(); break;
        case 50: _t->on_pushButton_action_screen_save_clicked(); break;
        case 51: _t->on_pushButton_action_sleep_clicked(); break;
        case 52: _t->on_pushButton_action_weakup_clicked(); break;
        case 53: _t->on_pushButton_RGB_next_page_clicked(); break;
        case 54: _t->on_pushButton_RGB_last_page_clicked(); break;
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
        if (_id < 55)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 55;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 55)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 55;
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
