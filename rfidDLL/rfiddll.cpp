#include "rfiddll.h"
#include <QDebug>

RfidDLL::RfidDLL()
{
    qDebug() << "RfidDLL->DLL created, initialising";
}

void RfidDLL::initialiseSerialPort()
{
    serial = new QSerialPort(this);
    serial->setPortName("com3"); // set this to what is the real port
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    // serial->setFlowControl(QSerialPort::NoFlowControl);
    serial->setFlowControl(QSerialPort::HardwareControl);

    if (serial->open(QIODevice::ReadWrite))
    {
        qDebug() << "RfidDLL->Port opened: " << serial->portName();
    }else {
        qDebug() << "RfidDLL->Error while opening port" << serial->portName();
    }
    connect(serial, SIGNAL(readyRead()), this, SLOT(readByteStream()));
}

void RfidDLL::readByteStream()
{
    char data[20];
    int bytesread;
    bytesread = serial->read(data,20);
    data[bytesread] = '\0';

    if (bytesread>10)
    {
        cardSerialNumber = data;
        cardSerialNumber.remove(0, 3);
        cardSerialNumber.chop(3);
        qDebug() << "RfidDLL->cardSerialNumber: " << cardSerialNumber;
    }
    else
        qDebug() << "RfidDLL->Error reading card";

    emit userLoginSignal(cardSerialNumber);
}

void RfidDLL::simulateUserLoggedIn()
{
    emit userLoginSignal("A123456789");
}
