#-------------------------------------------------
#
# Project created by QtCreator 2017-04-12T08:38:55
#
#-------------------------------------------------
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


QT       += core
QT -= qui

TARGET = pincodeDLL
TEMPLATE = lib

DEFINES += PINCODEDLL_LIBRARY

CONFIG += c++11

SOURCES += pincodedll.cpp \
    pincodedialog.cpp

HEADERS += pincodedll.h\
        pincodedll_global.h \
    pincodedialog.h

FORMS += \
    pincodedialog.ui

unix {
    target.path = /usr/lib
    INSTALLS += target
}

