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
    QByteArrayData data[44];
    char stringdata0[640];
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
QT_MOC_LITERAL(14, 169, 5), // "index"
QT_MOC_LITERAL(15, 175, 18), // "Signal_SetPassword"
QT_MOC_LITERAL(16, 194, 26), // "Signal_SetAccount_Password"
QT_MOC_LITERAL(17, 221, 7), // "account"
QT_MOC_LITERAL(18, 229, 19), // "Signal_SetBreathRGB"
QT_MOC_LITERAL(19, 249, 7), // "color_R"
QT_MOC_LITERAL(20, 257, 7), // "color_G"
QT_MOC_LITERAL(21, 265, 7), // "color_B"
QT_MOC_LITERAL(22, 273, 8), // "interval"
QT_MOC_LITERAL(23, 282, 18), // "Signal_SetShortcut"
QT_MOC_LITERAL(24, 301, 4), // "func"
QT_MOC_LITERAL(25, 306, 5), // "char*"
QT_MOC_LITERAL(26, 312, 3), // "key"
QT_MOC_LITERAL(27, 316, 7), // "key_len"
QT_MOC_LITERAL(28, 324, 14), // "Slot_AddFinger"
QT_MOC_LITERAL(29, 339, 16), // "Slot_EnrollState"
QT_MOC_LITERAL(30, 356, 6), // "state1"
QT_MOC_LITERAL(31, 363, 6), // "state2"
QT_MOC_LITERAL(32, 370, 17), // "Slot_DeleteFinger"
QT_MOC_LITERAL(33, 388, 18), // "Slot_RefreshFinger"
QT_MOC_LITERAL(34, 407, 21), // "Slot_UpdateIndexTable"
QT_MOC_LITERAL(35, 429, 23), // "Slot_SetWindowsPassword"
QT_MOC_LITERAL(36, 453, 16), // "Slot_SetPassword"
QT_MOC_LITERAL(37, 470, 24), // "Slot_SetAccount_Password"
QT_MOC_LITERAL(38, 495, 17), // "Slot_SetBreathRGB"
QT_MOC_LITERAL(39, 513, 16), // "Slot_RGB_Display"
QT_MOC_LITERAL(40, 530, 20), // "Slot_ChangeItemValue"
QT_MOC_LITERAL(41, 551, 18), // "Slot_SaveItemValue"
QT_MOC_LITERAL(42, 570, 16), // "Slot_SetShortcut"
QT_MOC_LITERAL(43, 587, 52) // "on_listWidget_table_state_cus..."

    },
    "Form_MainWindow\0Signal_AddFinger\0\0"
    "uint8_t\0pos\0times\0param1\0param2\0"
    "Signal_DeleteFinger\0id\0Signal_RefreshFinger\0"
    "Signal_UpdateIndexTable\0"
    "Signal_SetWindowsPassword\0password\0"
    "index\0Signal_SetPassword\0"
    "Signal_SetAccount_Password\0account\0"
    "Signal_SetBreathRGB\0color_R\0color_G\0"
    "color_B\0interval\0Signal_SetShortcut\0"
    "func\0char*\0key\0key_len\0Slot_AddFinger\0"
    "Slot_EnrollState\0state1\0state2\0"
    "Slot_DeleteFinger\0Slot_RefreshFinger\0"
    "Slot_UpdateIndexTable\0Slot_SetWindowsPassword\0"
    "Slot_SetPassword\0Slot_SetAccount_Password\0"
    "Slot_SetBreathRGB\0Slot_RGB_Display\0"
    "Slot_ChangeItemValue\0Slot_SaveItemValue\0"
    "Slot_SetShortcut\0"
    "on_listWidget_table_state_customContextMenuRequested"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Form_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    4,  129,    2, 0x06 /* Public */,
       8,    1,  138,    2, 0x06 /* Public */,
      10,    0,  141,    2, 0x06 /* Public */,
      11,    0,  142,    2, 0x06 /* Public */,
      12,    2,  143,    2, 0x06 /* Public */,
      15,    2,  148,    2, 0x06 /* Public */,
      16,    3,  153,    2, 0x06 /* Public */,
      18,    4,  160,    2, 0x06 /* Public */,
      23,    4,  169,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      28,    0,  178,    2, 0x0a /* Public */,
      29,    2,  179,    2, 0x0a /* Public */,
      32,    0,  184,    2, 0x0a /* Public */,
      33,    0,  185,    2, 0x0a /* Public */,
      34,    0,  186,    2, 0x0a /* Public */,
      35,    0,  187,    2, 0x0a /* Public */,
      36,    0,  188,    2, 0x0a /* Public */,
      37,    0,  189,    2, 0x0a /* Public */,
      38,    0,  190,    2, 0x0a /* Public */,
      39,    0,  191,    2, 0x0a /* Public */,
      40,    0,  192,    2, 0x0a /* Public */,
      41,    0,  193,    2, 0x0a /* Public */,
      42,    0,  194,    2, 0x0a /* Public */,
      43,    1,  195,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 3,    4,    5,    6,    7,
    QMetaType::Void, 0x80000000 | 3,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 3,   13,   14,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 3,   13,   14,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, 0x80000000 | 3,   17,   13,   14,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 3,   19,   20,   21,   22,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 25, 0x80000000 | 3, 0x80000000 | 3,   24,   26,   27,   14,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,   30,   31,
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
        case 4: _t->Signal_SetWindowsPassword((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< uint8_t(*)>(_a[2]))); break;
        case 5: _t->Signal_SetPassword((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< uint8_t(*)>(_a[2]))); break;
        case 6: _t->Signal_SetAccount_Password((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< uint8_t(*)>(_a[3]))); break;
        case 7: _t->Signal_SetBreathRGB((*reinterpret_cast< uint8_t(*)>(_a[1])),(*reinterpret_cast< uint8_t(*)>(_a[2])),(*reinterpret_cast< uint8_t(*)>(_a[3])),(*reinterpret_cast< uint8_t(*)>(_a[4]))); break;
        case 8: _t->Signal_SetShortcut((*reinterpret_cast< uint8_t(*)>(_a[1])),(*reinterpret_cast< char*(*)>(_a[2])),(*reinterpret_cast< uint8_t(*)>(_a[3])),(*reinterpret_cast< uint8_t(*)>(_a[4]))); break;
        case 9: _t->Slot_AddFinger(); break;
        case 10: _t->Slot_EnrollState((*reinterpret_cast< uint8_t(*)>(_a[1])),(*reinterpret_cast< uint8_t(*)>(_a[2]))); break;
        case 11: _t->Slot_DeleteFinger(); break;
        case 12: _t->Slot_RefreshFinger(); break;
        case 13: _t->Slot_UpdateIndexTable(); break;
        case 14: _t->Slot_SetWindowsPassword(); break;
        case 15: _t->Slot_SetPassword(); break;
        case 16: _t->Slot_SetAccount_Password(); break;
        case 17: _t->Slot_SetBreathRGB(); break;
        case 18: _t->Slot_RGB_Display(); break;
        case 19: _t->Slot_ChangeItemValue(); break;
        case 20: _t->Slot_SaveItemValue(); break;
        case 21: _t->Slot_SetShortcut(); break;
        case 22: _t->on_listWidget_table_state_customContextMenuRequested((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
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
            using _t = void (Form_MainWindow::*)(QString , uint8_t );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Form_MainWindow::Signal_SetWindowsPassword)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (Form_MainWindow::*)(QString , uint8_t );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Form_MainWindow::Signal_SetPassword)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (Form_MainWindow::*)(QString , QString , uint8_t );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Form_MainWindow::Signal_SetAccount_Password)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (Form_MainWindow::*)(uint8_t , uint8_t , uint8_t , uint8_t );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Form_MainWindow::Signal_SetBreathRGB)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (Form_MainWindow::*)(uint8_t , char * , uint8_t , uint8_t );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Form_MainWindow::Signal_SetShortcut)) {
                *result = 8;
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
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 23)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 23;
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
void Form_MainWindow::Signal_SetWindowsPassword(QString _t1, uint8_t _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Form_MainWindow::Signal_SetPassword(QString _t1, uint8_t _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void Form_MainWindow::Signal_SetAccount_Password(QString _t1, QString _t2, uint8_t _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void Form_MainWindow::Signal_SetBreathRGB(uint8_t _t1, uint8_t _t2, uint8_t _t3, uint8_t _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void Form_MainWindow::Signal_SetShortcut(uint8_t _t1, char * _t2, uint8_t _t3, uint8_t _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
