#ifndef RFIDDLL_H
#define RFIDDLL_H
#include <QSerialPort>

#include <QObject>
#include "rfiddll_global.h"


class RFIDDLLSHARED_EXPORT RfidDLL: public QObject
{
    Q_OBJECT
public:
    RfidDLL();
    void RFIDDLLSHARED_EXPORT initialiseSerialPort();

private:
    QSerialPort *serial;
    QString cardSerialNumber = "empty";

signals:
    void RFIDDLLSHARED_EXPORT userLoginSignal(QString);

private slots:
    void  readByteStream();

public slots:
    void RFIDDLLSHARED_EXPORT simulateUserLoggedIn();
};

#endif // RFIDDLL_H
