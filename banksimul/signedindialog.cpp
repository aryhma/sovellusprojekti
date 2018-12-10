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
    int idee = 1; //tama pitaisi korvata singnaalilla.. etta saadaan oikea tiliId.
    Kayttaja = olio2MysqlDLL->findName(idee);
    //qDebug() << "nimi on: " << Kayttaja ;

    //Kayttajan tietojen lisays kannasta tulevalla datalla.
    ui->lblTervetuloa->setText(ui->lblTervetuloa->text()+Kayttaja);
}

SignedInDialog::~SignedInDialog()
{
    delete ui;
}
