#include "pincodedll.h"
#include "pincodedialog.h"
#include <QDebug>

PincodeDLL::PincodeDLL()
{
    qDebug() << "PincodedDLL->DLL created, initialising";
}

void PincodeDLL::initialise()
{
}

void PincodeDLL::getPIN(QWidget *parent)
{
    qDebug() << "PincodedDLL->creating UI";

    PincodeDialog *dialog = new PincodeDialog(parent);
    dialog->show();

    connect(dialog, SIGNAL(receivedPIN(QString)), this, SLOT(receivedPIN(QString)));
}

void PincodeDLL::receivedPIN(QString s)
{
    qDebug() << "PincodeDLL->got PIN" << s << "- signaling";
    emit(validatePIN(s));
}
