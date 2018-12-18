#ifndef PINCODEDLL_H
#define PINCODEDLL_H

#include <QObject>
#include "pincodedll_global.h"


class PINCODEDLLSHARED_EXPORT PincodeDLL: public QObject
{
    Q_OBJECT
public:
    PincodeDLL();
    void PINCODEDLLSHARED_EXPORT getPIN(QWidget *);

private slots:
    void receivedPIN(QString);

signals:
    void PINCODEDLLSHARED_EXPORT validatePIN(QString);

};

#endif // PINCODEDLL_H
