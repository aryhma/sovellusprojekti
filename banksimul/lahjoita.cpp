#include "lahjoita.h"
#include "ui_lahjoita.h"

Lahjoita::Lahjoita(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Lahjoita)
{
    ui->setupUi(this);
}

Lahjoita::~Lahjoita()
{
    delete ui;
}

void Lahjoita::on_btnBack_clicked()
{
    this->close();
}

void Lahjoita::on_btnAmnesty_clicked()
{
    //asetaTiedot()
}

void Lahjoita::on_btnWWF_clicked()
{

}

void Lahjoita::on_btnPunainenRisti_clicked()
{

}

void Lahjoita::on_btnKummitRy_clicked()
{

}

void Lahjoita::on_sBoxLahjSumma_valueChanged()
{
    lahjoitusSumma = ui->sBoxLahjSumma->value();
}

void Lahjoita::asetaTiedot(QString tilinumero, QString saaja, QString viite)
{
    ui->lineLahjTiliN->setText(tilinumero);
    ui->lineLahjSaaja->setText(saaja);
    ui->lineLahjViite->setText(viite);
}
