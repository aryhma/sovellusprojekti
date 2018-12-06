#include "pincodedialog.h"
#include "ui_pincodedialog.h"

PincodeDialog::PincodeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PincodeDialog)
{
    ui->setupUi(this);
}

PincodeDialog::~PincodeDialog()
{
    delete ui;
}

void PincodeDialog::on_pushButton_clicked()
{
    pin="1234";
    emit receivedPIN(pin);

    this->close();
}
