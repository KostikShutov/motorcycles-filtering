#-------------------------------------------------
#
# Project created by QtCreator 2019-03-10T21:00:01
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = filtering
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/edittor.cpp \
    src/searcher.cpp \
    src/edittor_menu/edittor_item1.cpp \
    src/edittor_menu/edittor_item0.cpp \
    src/edittor_menu/edittor_item2.cpp \
    src/edittor_menu/edittor_item3.cpp \
    src/edittor_menu/edittor_item4.cpp \
    src/edittor_menu/edittor_item5.cpp \
    src/edittor_menu/enter_value/logical.cpp \
    src/edittor_menu/enter_value/scalar.cpp \
    src/edittor_menu/enter_value/dimensional.cpp \
    src/classes/qvaluedialog.cpp \
    src/edittor_menu/set_value/logical_setter.cpp \
    src/edittor_menu/set_value/scalar_setter.cpp \
    src/edittor_menu/set_value/dimensional_setter.cpp \
    src/resulter.cpp

HEADERS += \
    src/mainwindow.h \
    src/edittor.h \
    src/searcher.h \
    src/edittor_menu/edittor_item1.h \
    src/edittor_menu/edittor_item0.h \
    src/edittor_menu/edittor_item2.h \
    src/edittor_menu/edittor_item3.h \
    src/edittor_menu/edittor_item4.h \
    src/edittor_menu/edittor_item5.h \
    src/edittor_menu/enter_value/logical.h \
    src/edittor_menu/enter_value/scalar.h \
    src/edittor_menu/enter_value/dimensional.h \
    src/classes/qvaluedialog.h \
    src/edittor_menu/set_value/logical_setter.h \
    src/edittor_menu/set_value/scalar_setter.h \
    src/edittor_menu/set_value/dimensional_setter.h \
    src/resulter.h

FORMS += \
    src/mainwindow.ui \
    src/edittor.ui \
    src/searcher.ui \
    src/edittor_menu/edittor_item1.ui \
    src/edittor_menu/edittor_item0.ui \
    src/edittor_menu/edittor_item2.ui \
    src/edittor_menu/edittor_item3.ui \
    src/edittor_menu/edittor_item4.ui \
    src/edittor_menu/edittor_item5.ui \
    src/edittor_menu/enter_value/logical.ui \
    src/edittor_menu/enter_value/scalar.ui \
    src/edittor_menu/enter_value/dimensional.ui \
    src/edittor_menu/set_value/logical_setter.ui \
    src/edittor_menu/set_value/scalar_setter.ui \
    src/edittor_menu/set_value/dimensional_setter.ui \
    src/resulter.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    recourses.qrc

win32:RC_ICONS += favicon.ico
