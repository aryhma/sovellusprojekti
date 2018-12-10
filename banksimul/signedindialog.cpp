#include "signedindialog.h"
#include "ui_signedindialog.h"

SignedInDialog::SignedInDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignedInDialog)
{
    ui->setupUi(this);
}

SignedInDialog::~SignedInDialog()
{
    delete ui;
}
