/****************************************************************************
** Meta object code from reading C++ file 'msg_handler.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../HelloFinger/msg_handler.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'msg_handler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Msg_Handler_t {
    QByteArrayData data[11];
    char stringdata0[132];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Msg_Handler_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Msg_Handler_t qt_meta_stringdata_Msg_Handler = {
    {
QT_MOC_LITERAL(0, 0, 11), // "Msg_Handler"
QT_MOC_LITERAL(1, 12, 24), // "Signal_Update_TableState"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 25), // "Signal_Update_EnrollState"
QT_MOC_LITERAL(4, 64, 7), // "uint8_t"
QT_MOC_LITERAL(5, 72, 6), // "state1"
QT_MOC_LITERAL(6, 79, 6), // "state2"
QT_MOC_LITERAL(7, 86, 26), // "Signal_Update_Firmware_Msg"
QT_MOC_LITERAL(8, 113, 5), // "char*"
QT_MOC_LITERAL(9, 119, 4), // "date"
QT_MOC_LITERAL(10, 124, 7) // "version"

    },
    "Msg_Handler\0Signal_Update_TableState\0"
    "\0Signal_Update_EnrollState\0uint8_t\0"
    "state1\0state2\0Signal_Update_Firmware_Msg\0"
    "char*\0date\0version"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Msg_Handler[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,
       3,    2,   30,    2, 0x06 /* Public */,
       7,    2,   35,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4, 0x80000000 | 4,    5,    6,
    QMetaType::Void, 0x80000000 | 8, 0x80000000 | 8,    9,   10,

       0        // eod
};

void Msg_Handler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Msg_Handler *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Signal_Update_TableState(); break;
        case 1: _t->Signal_Update_EnrollState((*reinterpret_cast< uint8_t(*)>(_a[1])),(*reinterpret_cast< uint8_t(*)>(_a[2]))); break;
        case 2: _t->Signal_Update_Firmware_Msg((*reinterpret_cast< char*(*)>(_a[1])),(*reinterpret_cast< char*(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Msg_Handler::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Msg_Handler::Signal_Update_TableState)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Msg_Handler::*)(uint8_t , uint8_t );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Msg_Handler::Signal_Update_EnrollState)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Msg_Handler::*)(char * , char * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Msg_Handler::Signal_Update_Firmware_Msg)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Msg_Handler::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_Msg_Handler.data,
    qt_meta_data_Msg_Handler,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Msg_Handler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Msg_Handler::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Msg_Handler.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Msg_Handler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void Msg_Handler::Signal_Update_TableState()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Msg_Handler::Signal_Update_EnrollState(uint8_t _t1, uint8_t _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Msg_Handler::Signal_Update_Firmware_Msg(char * _t1, char * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
