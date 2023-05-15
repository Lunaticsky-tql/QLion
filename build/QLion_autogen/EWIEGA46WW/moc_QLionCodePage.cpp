/****************************************************************************
** Meta object code from reading C++ file 'QLionCodePage.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../QLionCodePage.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QLionCodePage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_QLionCodePage_t {
    uint offsetsAndSizes[14];
    char stringdata0[14];
    char stringdata1[21];
    char stringdata2[1];
    char stringdata3[21];
    char stringdata4[3];
    char stringdata5[26];
    char stringdata6[11];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_QLionCodePage_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_QLionCodePage_t qt_meta_stringdata_QLionCodePage = {
    {
        QT_MOC_LITERAL(0, 13),  // "QLionCodePage"
        QT_MOC_LITERAL(14, 20),  // "highlightCurrentLine"
        QT_MOC_LITERAL(35, 0),  // ""
        QT_MOC_LITERAL(36, 20),  // "updateLineNumberArea"
        QT_MOC_LITERAL(57, 2),  // "dy"
        QT_MOC_LITERAL(60, 25),  // "updateLineNumberAreaWidth"
        QT_MOC_LITERAL(86, 10)   // "setUnsaved"
    },
    "QLionCodePage",
    "highlightCurrentLine",
    "",
    "updateLineNumberArea",
    "dy",
    "updateLineNumberAreaWidth",
    "setUnsaved"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_QLionCodePage[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   38,    2, 0x08,    1 /* Private */,
       3,    2,   39,    2, 0x08,    2 /* Private */,
       5,    0,   44,    2, 0x08,    5 /* Private */,
       6,    0,   45,    2, 0x08,    6 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QRect, QMetaType::Int,    2,    4,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject QLionCodePage::staticMetaObject = { {
    QMetaObject::SuperData::link<QPlainTextEdit::staticMetaObject>(),
    qt_meta_stringdata_QLionCodePage.offsetsAndSizes,
    qt_meta_data_QLionCodePage,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_QLionCodePage_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QLionCodePage, std::true_type>,
        // method 'highlightCurrentLine'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateLineNumberArea'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QRect &, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'updateLineNumberAreaWidth'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setUnsaved'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void QLionCodePage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QLionCodePage *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->highlightCurrentLine(); break;
        case 1: _t->updateLineNumberArea((*reinterpret_cast< std::add_pointer_t<QRect>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 2: _t->updateLineNumberAreaWidth(); break;
        case 3: _t->setUnsaved(); break;
        default: ;
        }
    }
}

const QMetaObject *QLionCodePage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QLionCodePage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QLionCodePage.stringdata0))
        return static_cast<void*>(this);
    return QPlainTextEdit::qt_metacast(_clname);
}

int QLionCodePage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPlainTextEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
