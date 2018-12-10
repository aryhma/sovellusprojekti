#include "signedindialog.h"
#include "ui_signedindialog.h"
#include "mainwindow.h"
#include <QDebug>

SignedInDialog::SignedInDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignedInDialog)
{
    ui->setupUi(this);

    olio2MysqlDLL = new DLLMySQL;

    //nimen haku

    //int tili = valitaTili();
    int idee = 1;
    QString nimi = olio2MysqlDLL->findName(idee);
    qDebug() << "nimi on: " << nimi ;
    Kayttaja=nimi;
    //Kayttaja alustettava kannasta loytyvällä nimellä
    ui->lblTervetuloa->setText(ui->lblTervetuloa->text()+Kayttaja);
}

SignedInDialog::~SignedInDialog()
{
    delete ui;
}
