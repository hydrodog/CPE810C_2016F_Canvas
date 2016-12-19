/****************************************************************************
** Meta object code from reading C++ file 'createassignmententry.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../AutomaticshiftingofDate/createassignmententry.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'createassignmententry.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_createassignmententry_t {
    QByteArrayData data[10];
    char stringdata0[125];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_createassignmententry_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_createassignmententry_t qt_meta_stringdata_createassignmententry = {
    {
QT_MOC_LITERAL(0, 0, 21), // "createassignmententry"
QT_MOC_LITERAL(1, 22, 11), // "nameChanged"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 12), // "themeChanged"
QT_MOC_LITERAL(4, 48, 21), // "expirationdateChanged"
QT_MOC_LITERAL(5, 70, 17), // "assignmentChanged"
QT_MOC_LITERAL(6, 88, 4), // "name"
QT_MOC_LITERAL(7, 93, 5), // "theme"
QT_MOC_LITERAL(8, 99, 14), // "expirationdate"
QT_MOC_LITERAL(9, 114, 10) // "assignment"

    },
    "createassignmententry\0nameChanged\0\0"
    "themeChanged\0expirationdateChanged\0"
    "assignmentChanged\0name\0theme\0"
    "expirationdate\0assignment"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_createassignmententry[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       4,   38, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    0,   35,    2, 0x06 /* Public */,
       4,    0,   36,    2, 0x06 /* Public */,
       5,    0,   37,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
       6, QMetaType::QString, 0x00495103,
       7, QMetaType::QString, 0x00495103,
       8, QMetaType::QDate, 0x00495103,
       9, QMetaType::QString, 0x00495103,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,

       0        // eod
};

void createassignmententry::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        createassignmententry *_t = static_cast<createassignmententry *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->nameChanged(); break;
        case 1: _t->themeChanged(); break;
        case 2: _t->expirationdateChanged(); break;
        case 3: _t->assignmentChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (createassignmententry::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&createassignmententry::nameChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (createassignmententry::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&createassignmententry::themeChanged)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (createassignmententry::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&createassignmententry::expirationdateChanged)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (createassignmententry::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&createassignmententry::assignmentChanged)) {
                *result = 3;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        createassignmententry *_t = static_cast<createassignmententry *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->name(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->theme(); break;
        case 2: *reinterpret_cast< QDate*>(_v) = _t->expirationdate(); break;
        case 3: *reinterpret_cast< QString*>(_v) = _t->assignment(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        createassignmententry *_t = static_cast<createassignmententry *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setName(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setTheme(*reinterpret_cast< QString*>(_v)); break;
        case 2: _t->setExpirationdate(*reinterpret_cast< QDate*>(_v)); break;
        case 3: _t->setAssignment(*reinterpret_cast< QString*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
    Q_UNUSED(_a);
}

const QMetaObject createassignmententry::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_createassignmententry.data,
      qt_meta_data_createassignmententry,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *createassignmententry::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *createassignmententry::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_createassignmententry.stringdata0))
        return static_cast<void*>(const_cast< createassignmententry*>(this));
    return QObject::qt_metacast(_clname);
}

int createassignmententry::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 4;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void createassignmententry::nameChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void createassignmententry::themeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void createassignmententry::expirationdateChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void createassignmententry::assignmentChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
