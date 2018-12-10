#include "signedindialog.h"
#include "ui_signedindialog.h"

SignedInDialog::SignedInDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignedInDialog)
{
    ui->setupUi(this);
    //Kayttaja alustettava kannasta loytyvällä nimellä
    ui->lblTervetuloa->setText(ui->lblTervetuloa->text()+Kayttaja);
}

SignedInDialog::~SignedInDialog()
{
    delete ui;
}
