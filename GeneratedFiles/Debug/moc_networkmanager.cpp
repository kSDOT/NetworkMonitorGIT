/****************************************************************************
** Meta object code from reading C++ file 'networkmanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../networkmanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'networkmanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_sta__NetworkManager_t {
    QByteArrayData data[18];
    char stringdata0[267];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_sta__NetworkManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_sta__NetworkManager_t qt_meta_stringdata_sta__NetworkManager = {
    {
QT_MOC_LITERAL(0, 0, 19), // "sta::NetworkManager"
QT_MOC_LITERAL(1, 20, 8), // "dataRead"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 28), // "std::vector<QList<QString> >"
QT_MOC_LITERAL(4, 59, 14), // "toolbarMessage"
QT_MOC_LITERAL(5, 74, 19), // "newAdapterClearData"
QT_MOC_LITERAL(6, 94, 14), // "aliasesChanged"
QT_MOC_LITERAL(7, 109, 10), // "lookupDone"
QT_MOC_LITERAL(8, 120, 15), // "filterInstalled"
QT_MOC_LITERAL(9, 136, 12), // "selectDevice"
QT_MOC_LITERAL(10, 149, 16), // "updateDeviceList"
QT_MOC_LITERAL(11, 166, 10), // "getAliases"
QT_MOC_LITERAL(12, 177, 25), // "std::map<QString,QString>"
QT_MOC_LITERAL(13, 203, 10), // "setAliases"
QT_MOC_LITERAL(14, 214, 10), // "getDevices"
QT_MOC_LITERAL(15, 225, 13), // "getIpDnsCache"
QT_MOC_LITERAL(16, 239, 13), // "setIpDnsCache"
QT_MOC_LITERAL(17, 253, 13) // "installFilter"

    },
    "sta::NetworkManager\0dataRead\0\0"
    "std::vector<QList<QString> >\0"
    "toolbarMessage\0newAdapterClearData\0"
    "aliasesChanged\0lookupDone\0filterInstalled\0"
    "selectDevice\0updateDeviceList\0getAliases\0"
    "std::map<QString,QString>\0setAliases\0"
    "getDevices\0getIpDnsCache\0setIpDnsCache\0"
    "installFilter"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_sta__NetworkManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   89,    2, 0x06 /* Public */,
       4,    2,   96,    2, 0x06 /* Public */,
       4,    1,  101,    2, 0x26 /* Public | MethodCloned */,
       5,    0,  104,    2, 0x06 /* Public */,
       6,    0,  105,    2, 0x06 /* Public */,
       7,    1,  106,    2, 0x06 /* Public */,
       8,    1,  109,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    1,  112,    2, 0x0a /* Public */,
      10,    0,  115,    2, 0x0a /* Public */,
      11,    0,  116,    2, 0x0a /* Public */,
      13,    1,  117,    2, 0x0a /* Public */,
      14,    0,  120,    2, 0x0a /* Public */,
      15,    0,  121,    2, 0x0a /* Public */,
      16,    1,  122,    2, 0x0a /* Public */,
      17,    1,  125,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int, QMetaType::QTime,    2,    2,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    0x80000000 | 12,
    QMetaType::Void, 0x80000000 | 12,    2,
    QMetaType::Void,
    0x80000000 | 12,
    QMetaType::Void, 0x80000000 | 12,    2,
    QMetaType::Void, QMetaType::QString,    2,

       0        // eod
};

void sta::NetworkManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<NetworkManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->dataRead((*reinterpret_cast< const std::vector<QList<QString> >(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QTime(*)>(_a[3]))); break;
        case 1: _t->toolbarMessage((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->toolbarMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->newAdapterClearData(); break;
        case 4: _t->aliasesChanged(); break;
        case 5: _t->lookupDone((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->filterInstalled((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->selectDevice((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->updateDeviceList(); break;
        case 9: { std::map<QString,QString> _r = _t->getAliases();
            if (_a[0]) *reinterpret_cast< std::map<QString,QString>*>(_a[0]) = std::move(_r); }  break;
        case 10: _t->setAliases((*reinterpret_cast< const std::map<QString,QString>(*)>(_a[1]))); break;
        case 11: _t->getDevices(); break;
        case 12: { std::map<QString,QString> _r = _t->getIpDnsCache();
            if (_a[0]) *reinterpret_cast< std::map<QString,QString>*>(_a[0]) = std::move(_r); }  break;
        case 13: _t->setIpDnsCache((*reinterpret_cast< const std::map<QString,QString>(*)>(_a[1]))); break;
        case 14: _t->installFilter((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (NetworkManager::*)(const std::vector<QList<QString>> & , int , QTime );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NetworkManager::dataRead)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (NetworkManager::*)(QString , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NetworkManager::toolbarMessage)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (NetworkManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NetworkManager::newAdapterClearData)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (NetworkManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NetworkManager::aliasesChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (NetworkManager::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NetworkManager::lookupDone)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (NetworkManager::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NetworkManager::filterInstalled)) {
                *result = 6;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject sta::NetworkManager::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_sta__NetworkManager.data,
    qt_meta_data_sta__NetworkManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *sta::NetworkManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *sta::NetworkManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_sta__NetworkManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int sta::NetworkManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void sta::NetworkManager::dataRead(const std::vector<QList<QString>> & _t1, int _t2, QTime _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void sta::NetworkManager::toolbarMessage(QString _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 3
void sta::NetworkManager::newAdapterClearData()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void sta::NetworkManager::aliasesChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void sta::NetworkManager::lookupDone(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void sta::NetworkManager::filterInstalled(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
struct qt_meta_stringdata_sta__CaptureClass_t {
    QByteArrayData data[4];
    char stringdata0[48];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_sta__CaptureClass_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_sta__CaptureClass_t qt_meta_stringdata_sta__CaptureClass = {
    {
QT_MOC_LITERAL(0, 0, 17), // "sta::CaptureClass"
QT_MOC_LITERAL(1, 18, 12), // "startCapture"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 15) // "NetworkManager*"

    },
    "sta::CaptureClass\0startCapture\0\0"
    "NetworkManager*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_sta__CaptureClass[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

       0        // eod
};

void sta::CaptureClass::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CaptureClass *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->startCapture((*reinterpret_cast< NetworkManager*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< NetworkManager* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject sta::CaptureClass::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_sta__CaptureClass.data,
    qt_meta_data_sta__CaptureClass,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *sta::CaptureClass::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *sta::CaptureClass::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_sta__CaptureClass.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int sta::CaptureClass::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
