#include "signedindialog.h"
#include "ui_signedindialog.h"
#include "mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QTableView>
#include <QSqlTableModel>

#include <QtGui>
#include <QGridLayout>

SignedInDialog::SignedInDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignedInDialog)
{
    ui->setupUi(this);

    olioSaldo = new Saldo(this);
    connect(this, SIGNAL(sendBalance(double)), olioSaldo, SLOT(naytaSaldo(double)));
    connect(this, SIGNAL(lahetaKayttaja(QString)), olioSaldo, SLOT(asetaKayttaja(QString)));
    connect(this, SIGNAL(lahetaTiliId(int)), olioSaldo, SLOT(naytaTapahtumat(int)));

}

SignedInDialog::~SignedInDialog()
{
    delete ui;
    delete olioSaldo;
    delete olioNosta;
    delete olioLahjoita;
    delete olioMaksa;
    delete olio2MysqlDLL;
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
    double saldo = olio2MysqlDLL->showBalance(idTili);

    emit sendBalance(saldo);
    emit lahetaKayttaja(Kayttaja);
    emit lahetaTiliId(idTili);
    olioSaldo->show();
}

void SignedInDialog::on_btnTapahtumat_clicked()
{
    showTable();
}

void SignedInDialog::on_btnNosta_clicked()
{
    olioNosta = new Nosta(this);
    olioNosta->asetaSaldo(olio2MysqlDLL->showBalance(idTili));
    olioNosta->asetaTili(idTili);
    olioNosta->show();
}

void SignedInDialog::on_btnLahjoita_clicked()
{
    olioLahjoita = new Lahjoita(this);
    olioLahjoita->asetaSaldo(olio2MysqlDLL->showBalance(idTili));
    olioLahjoita->asetaTili(idTili);
    olioLahjoita->show();
}

void SignedInDialog::on_btnMaksa_clicked()
{
    olioMaksa = new Maksa(this);
    olioMaksa->asetaSaldo(olio2MysqlDLL->showBalance(idTili));
    olioMaksa->asetaTili(idTili);
    olioMaksa->asetaLaskujenMaara(olio2MysqlDLL->invoiceCount(idTili));
    olioMaksa->show();
}

void SignedInDialog::showTable()
{
    tableWindow = new QWidget();
    btnPoistu = new QPushButton("Takaisin");
    QGridLayout *tableLay = new QGridLayout(tableWindow);
    QTableView *tapahtumat = new QTableView;

    tableWindow->setWindowTitle("Tilitapahtumat");
    tapahtumat->setModel(olio2MysqlDLL->showTransactions(idTili,15));
    tapahtumat->resizeColumnToContents(0);
    tableWindow->resize(350,400);
    tableLay->addWidget(tapahtumat);
    tableLay->addWidget(btnPoistu);
    tableWindow->setLayout(tableLay);
    tableWindow->show();

    connect(btnPoistu, SIGNAL(clicked()), this, SLOT(tableClose()));
}

void SignedInDialog::tableClose()
{
    tableWindow->close();
}
