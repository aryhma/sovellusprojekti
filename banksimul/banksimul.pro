#-------------------------------------------------
#
# Project created by QtCreator 2018-11-19T10:29:54
#
#-------------------------------------------------

QT       += core gui serialport sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = banksimul
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
        main.cpp \
        mainwindow.cpp \
    signedindialog.cpp \
    saldo.cpp \
    nosta.cpp \
    lahjoita.cpp \
    maksa.cpp

HEADERS += \
        mainwindow.h \
    signedindialog.h \
    saldo.h \
    nosta.h \
    lahjoita.h \
    maksa.h

FORMS += \
        mainwindow.ui \
    signedindialog.ui \
    saldo.ui \
    nosta.ui \
    lahjoita.ui \
    maksa.ui

LIBS += "$$PWD/../run/rfidDLL.dll"
LIBS += "$$PWD/../run/pincodeDLL.dll"
LIBS += "$$PWD/../run/DLLMySQL.dll"

# INCLUDEPATH += "$$PWD/dll"
INCLUDEPATH += "$$PWD/../DLLMySQL"
INCLUDEPATH += "$$PWD/../pincodeDLL"
INCLUDEPATH += "$$PWD/../rfidDLL"

DESTDIR = "$$PWD/../run/"

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
