/****************************************************************************
** Meta object code from reading C++ file 'emulkbd.h'
**
** Created: Fri Jul 2 22:22:49 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "emulkbd.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'emulkbd.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_EmulKbd[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

       0        // eod
};

static const char qt_meta_stringdata_EmulKbd[] = {
    "EmulKbd\0"
};

const QMetaObject EmulKbd::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_EmulKbd,
      qt_meta_data_EmulKbd, 0 }
};

const QMetaObject *EmulKbd::metaObject() const
{
    return &staticMetaObject;
}

void *EmulKbd::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EmulKbd))
        return static_cast<void*>(const_cast< EmulKbd*>(this));
    return QFrame::qt_metacast(_clname);
}

int EmulKbd::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_EmulKey[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x09,
      22,    8,    8,    8, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_EmulKey[] = {
    "EmulKey\0\0keyPressed()\0keyReleased()\0"
};

const QMetaObject EmulKey::staticMetaObject = {
    { &QPushButton::staticMetaObject, qt_meta_stringdata_EmulKey,
      qt_meta_data_EmulKey, 0 }
};

const QMetaObject *EmulKey::metaObject() const
{
    return &staticMetaObject;
}

void *EmulKey::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EmulKey))
        return static_cast<void*>(const_cast< EmulKey*>(this));
    return QPushButton::qt_metacast(_clname);
}

int EmulKey::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: keyPressed(); break;
        case 1: keyReleased(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
