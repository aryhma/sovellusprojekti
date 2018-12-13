#include <QMessageBox>
#include "nosta.h"
#include "ui_nosta.h"
#include "dllmysql.h"
#include <QMessageBox>

Nosta::Nosta(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Nosta)
{
    ui->setupUi(this);
}

Nosta::~Nosta()
{
    delete ui;
}

void Nosta::on_btn20_clicked()
{
    nostoSumma=20;
    vaihdaTeksti(nostoSumma);
}

void Nosta::on_btn40_clicked()
{
    nostoSumma=40;
    vaihdaTeksti(nostoSumma);
}

void Nosta::on_btn60_clicked()
{
    nostoSumma=60;
    vaihdaTeksti(nostoSumma);
}

void Nosta::on_btn80_clicked()
{
    nostoSumma=80;
    vaihdaTeksti(nostoSumma);
}

void Nosta::on_btn100_clicked()
{
    nostoSumma=100;
    vaihdaTeksti(nostoSumma);
}

void Nosta::on_btnPeruuta_clicked()
{
    this->close();
}

void Nosta::on_btnnosta_clicked()
{
    if (nostoSumma>0)
    {
    saldoP = olio3MysqlDLL->raiseMoney(idTili, nostoSumma);
    //kanta palauttaa -1 arvon jos tilin saldo ei riita.
    if (saldoP < 0)
    {
        saldoP = olio3MysqlDLL->showBalance(idTili);
        QMessageBox eionnistu;
        QString teksti = QString("Rahan nostaminen epäonnistui\n"
                                 "Sinulla ei ole tilillä katetta\n\n"
                                 "Tilin saldo on: %1 €").arg(saldoP);
        eionnistu.setText(teksti);
        eionnistu.exec();
    }else
    {
        QMessageBox onnistui;
        QString teksti = QString("Nosto suoritettu\n"
                                 "Muistaa ottaa rahat\n\n"
                                 "Tilille jäi rahaa : %1 €").arg(saldoP);
        onnistui.setText(teksti);
        onnistui.exec();

        //sammutetaan nosto ikkuna vain hyvaksytysta nostosta.
        this->close();
    }
    }
}

void Nosta::vaihdaTeksti(int i)
{
    ui->btnnosta->setText("Nosta " +QString("%1").arg(i)+ "€");
}

void Nosta::on_spinBoxSumma_valueChanged()
{
    nostoSumma = ui->spinBoxSumma->value();
    vaihdaTeksti(nostoSumma);
}
