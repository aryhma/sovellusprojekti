#include "signedindialog.h"
#include "ui_signedindialog.h"
#include "mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QTableView>
#include <QSqlTableModel>

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

void SignedInDialog::on_btnSaldo_clicked()
{
    float saldo = olio2MysqlDLL->showBalance(idTili);
    QMessageBox saldoo;
    QString teksti = QString("Pankkitilin saldo on: %1").arg(saldo);
    saldoo.setText(teksti);
    saldoo.exec();
}

void SignedInDialog::on_btnTapahtumat_clicked()
{
    //QSqlTableModel testi =  olio2MysqlDLL->showTransactions();
    QTableView *tapahtumat = new QTableView;
    tapahtumat->setModel(olio2MysqlDLL->showTransactions(idTili));
    tapahtumat->setWindowTitle("Tilitapahtumat");
    tapahtumat->resizeColumnToContents(0);
    tapahtumat->resize(400,307);
    tapahtumat->show();
    //QTableView *view1 = new createView(olio2MysqlDLL->showTransactions(idTili)  , QObject::tr("Table Model (View 1)"));

    //view1->show();
}
