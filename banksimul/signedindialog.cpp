#include "signedindialog.h"
#include "ui_signedindialog.h"
#include "mainwindow.h"
#include <QDebug>

SignedInDialog::SignedInDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignedInDialog)
{
    ui->setupUi(this);

}

SignedInDialog::~SignedInDialog()
{
    delete ui;
    //delete olio2MysqlDLL;
}

void SignedInDialog::asetaOtsikko()
{
    ui->lblTervetuloa->setText(ui->lblTervetuloa->text()+Kayttaja);
}

void SignedInDialog::on_btnUlos_clicked()
{
    this->close();
}
