#-------------------------------------------------
#
# Project created by QtCreator 2017-04-12T08:38:55
#
#-------------------------------------------------

QT       += core serialport
QT -= qui

TARGET = rfidDLL
TEMPLATE = lib

DEFINES += RFIDDLL_LIBRARY

SOURCES += rfiddll.cpp

HEADERS += rfiddll.h\
        rfiddll_global.h

DESTDIR = "$$PWD/../run/"

unix {
    target.path = /usr/lib
    INSTALLS += target
}
