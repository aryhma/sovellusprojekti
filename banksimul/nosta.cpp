#include "nosta.h"
#include "ui_nosta.h"

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
