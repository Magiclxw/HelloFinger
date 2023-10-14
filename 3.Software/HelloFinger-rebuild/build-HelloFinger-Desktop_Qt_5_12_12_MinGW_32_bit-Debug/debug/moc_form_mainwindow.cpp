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
    QByteArrayData data[57];
    char stringdata0[1084];
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
QT_MOC_LITERAL(32, 378, 14), // "Slot_AddFinger"
QT_MOC_LITERAL(33, 393, 16), // "Slot_EnrollState"
QT_MOC_LITERAL(34, 410, 6), // "state1"
QT_MOC_LITERAL(35, 417, 6), // "state2"
QT_MOC_LITERAL(36, 424, 17), // "Slot_DeleteFinger"
QT_MOC_LITERAL(37, 442, 18), // "Slot_RefreshFinger"
QT_MOC_LITERAL(38, 461, 21), // "Slot_UpdateIndexTable"
QT_MOC_LITERAL(39, 483, 23), // "Slot_SetWindowsPassword"
QT_MOC_LITERAL(40, 507, 16), // "Slot_SetPassword"
QT_MOC_LITERAL(41, 524, 24), // "Slot_SetAccount_Password"
QT_MOC_LITERAL(42, 549, 18), // "Slot_SetQuickStart"
QT_MOC_LITERAL(43, 568, 17), // "Slot_SetBreathRGB"
QT_MOC_LITERAL(44, 586, 16), // "Slot_RGB_Display"
QT_MOC_LITERAL(45, 603, 20), // "Slot_ChangeItemValue"
QT_MOC_LITERAL(46, 624, 18), // "Slot_SaveItemValue"
QT_MOC_LITERAL(47, 643, 16), // "Slot_SetShortcut"
QT_MOC_LITERAL(48, 660, 25), // "Slot_DeleteQuickStartItem"
QT_MOC_LITERAL(49, 686, 47), // "on_listWidget_task_1_customCo..."
QT_MOC_LITERAL(50, 734, 52), // "on_listWidget_table_state_cus..."
QT_MOC_LITERAL(51, 787, 47), // "on_listWidget_task_2_customCo..."
QT_MOC_LITERAL(52, 835, 47), // "on_listWidget_task_3_customCo..."
QT_MOC_LITERAL(53, 883, 47), // "on_listWidget_task_4_customCo..."
QT_MOC_LITERAL(54, 931, 47), // "on_listWidget_task_5_customCo..."
QT_MOC_LITERAL(55, 979, 56), // "on_listWidget_table_state_key..."
QT_MOC_LITERAL(56, 1036, 47) // "on_listWidget_task_6_customCo..."

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
    "func\0char*\0key\0key_len\0Slot_AddFinger\0"
    "Slot_EnrollState\0state1\0state2\0"
    "Slot_DeleteFinger\0Slot_RefreshFinger\0"
    "Slot_UpdateIndexTable\0Slot_SetWindowsPassword\0"
    "Slot_SetPassword\0Slot_SetAccount_Password\0"
    "Slot_SetQuickStart\0Slot_SetBreathRGB\0"
    "Slot_RGB_Display\0Slot_ChangeItemValue\0"
    "Slot_SaveItemValue\0Slot_SetShortcut\0"
    "Slot_DeleteQuickStartItem\0"
    "on_listWidget_task_1_customContextMenuRequested\0"
    "on_listWidget_table_state_customContextMenuRequested\0"
    "on_listWidget_task_2_customContextMenuRequested\0"
    "on_listWidget_task_3_customContextMenuRequested\0"
    "on_listWidget_task_4_customContextMenuRequested\0"
    "on_listWidget_task_5_customContextMenuRequested\0"
    "on_listWidget_table_state_key_customContextMenuRequested\0"
    "on_listWidget_task_6_customContextMenuRequested"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Form_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      33,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    4,  179,    2, 0x06 /* Public */,
       8,    1,  188,    2, 0x06 /* Public */,
      10,    0,  191,    2, 0x06 /* Public */,
      11,    0,  192,    2, 0x06 /* Public */,
      12,    3,  193,    2, 0x06 /* Public */,
      16,    3,  200,    2, 0x06 /* Public */,
      17,    4,  207,    2, 0x06 /* Public */,
      19,    3,  216,    2, 0x06 /* Public */,
      22,    4,  223,    2, 0x06 /* Public */,
      27,    5,  232,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      32,    0,  243,    2, 0x0a /* Public */,
      33,    2,  244,    2, 0x0a /* Public */,
      36,    0,  249,    2, 0x0a /* Public */,
      37,    0,  250,    2, 0x0a /* Public */,
      38,    0,  251,    2, 0x0a /* Public */,
      39,    0,  252,    2, 0x0a /* Public */,
      40,    0,  253,    2, 0x0a /* Public */,
      41,    0,  254,    2, 0x0a /* Public */,
      42,    1,  255,    2, 0x0a /* Public */,
      43,    0,  258,    2, 0x0a /* Public */,
      44,    0,  259,    2, 0x0a /* Public */,
      45,    0,  260,    2, 0x0a /* Public */,
      46,    0,  261,    2, 0x0a /* Public */,
      47,    0,  262,    2, 0x0a /* Public */,
      48,    0,  263,    2, 0x0a /* Public */,
      49,    1,  264,    2, 0x08 /* Private */,
      50,    1,  267,    2, 0x08 /* Private */,
      51,    1,  270,    2, 0x08 /* Private */,
      52,    1,  273,    2, 0x08 /* Private */,
      53,    1,  276,    2, 0x08 /* Private */,
      54,    1,  279,    2, 0x08 /* Private */,
      55,    1,  282,    2, 0x08 /* Private */,
      56,    1,  285,    2, 0x08 /* Private */,

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

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,   34,   35,
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
    QMetaType::Void, QMetaType::QPoint,    4,
    QMetaType::Void, QMetaType::QPoint,    4,
    QMetaType::Void, QMetaType::QPoint,    4,
    QMetaType::Void, QMetaType::QPoint,    4,
    QMetaType::Void, QMetaType::QPoint,    4,
    QMetaType::Void, QMetaType::QPoint,    4,
    QMetaType::Void, QMetaType::QPoint,    4,
    QMetaType::Void, QMetaType::QPoint,    4,

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
        case 10: _t->Slot_AddFinger(); break;
        case 11: _t->Slot_EnrollState((*reinterpret_cast< uint8_t(*)>(_a[1])),(*reinterpret_cast< uint8_t(*)>(_a[2]))); break;
        case 12: _t->Slot_DeleteFinger(); break;
        case 13: _t->Slot_RefreshFinger(); break;
        case 14: _t->Slot_UpdateIndexTable(); break;
        case 15: _t->Slot_SetWindowsPassword(); break;
        case 16: _t->Slot_SetPassword(); break;
        case 17: _t->Slot_SetAccount_Password(); break;
        case 18: _t->Slot_SetQuickStart((*reinterpret_cast< QUICK_START_e(*)>(_a[1]))); break;
        case 19: _t->Slot_SetBreathRGB(); break;
        case 20: _t->Slot_RGB_Display(); break;
        case 21: _t->Slot_ChangeItemValue(); break;
        case 22: _t->Slot_SaveItemValue(); break;
        case 23: _t->Slot_SetShortcut(); break;
        case 24: _t->Slot_DeleteQuickStartItem(); break;
        case 25: _t->on_listWidget_task_1_customContextMenuRequested((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 26: _t->on_listWidget_table_state_customContextMenuRequested((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 27: _t->on_listWidget_task_2_customContextMenuRequested((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 28: _t->on_listWidget_task_3_customContextMenuRequested((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 29: _t->on_listWidget_task_4_customContextMenuRequested((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 30: _t->on_listWidget_task_5_customContextMenuRequested((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 31: _t->on_listWidget_table_state_key_customContextMenuRequested((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 32: _t->on_listWidget_task_6_customContextMenuRequested((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
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
        if (_id < 33)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 33;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 33)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 33;
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
