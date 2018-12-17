#include "saldo.h"
#include "ui_saldo.h"
#include <QDebug>
#include <QtGui>
#include <QVBoxLayout>

Saldo::Saldo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Saldo)
{
    ui->setupUi(this);
}

Saldo::~Saldo()
{
    delete ui;
}

void Saldo::naytaSaldo(double arvo)
{
    qDebug() << "Naytan saldoksi: " << arvo;
    ui->lblSaldo->setText(ui->lblSaldo->text() + QString("%1").arg(arvo));
}

void Saldo::asetaKayttaja(QString kayt)
{
    ui->lblOmistaja->setText(ui->lblOmistaja->text() + kayt);
}

void Saldo::naytaTapahtumat(int tiliId)
{
     ui->tableView->setModel(olioSaldoMysqlDLL->showTransactions(tiliId,5));
}
void Saldo::on_btnTakaisin_clicked()
{
    ui->lblOmistaja->setText("Tilinomistaja:    "); //Kentät tyhjennettävä valmiiksi seuraavaan kertaan.
    ui->lblSaldo->setText("Tilillä käytettävissä:    ");
    this->close();
}

