#include "lahjoita.h"
#include "ui_lahjoita.h"
#include <QMessageBox>
#include "dllmysql.h"


Lahjoita::Lahjoita(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Lahjoita)
{
    ui->setupUi(this);
    olio5mysql = new DLLMySQL;
    connect(olio5mysql, SIGNAL(sendTili(QString)), this, SLOT(asetaTili(QString)));
    connect(olio5mysql, SIGNAL(sendSaaja(QString)), this, SLOT(asetaSaaja(QString)));
    connect(olio5mysql, SIGNAL(sendViite(QString)), this, SLOT(asetaViite(QString)));
}

Lahjoita::~Lahjoita()
{
    delete ui;
    delete olio5mysql;
}

void Lahjoita::on_btnBack_clicked()
{
    this->close();
}

void Lahjoita::on_btnAmnesty_clicked()
{
    haeTiedot(1);
    asetaTiedot(tilinumero,saaja,viite);
}

void Lahjoita::on_btnWWF_clicked()
{
    haeTiedot(2);
    asetaTiedot(tilinumero,saaja,viite);
}

void Lahjoita::on_btnPunainenRisti_clicked()
{
    haeTiedot(3);
    asetaTiedot(tilinumero,saaja,viite);
}

void Lahjoita::on_btnKummitRy_clicked()
{
    haeTiedot(4);
    asetaTiedot(tilinumero,saaja,viite);
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

void Lahjoita::haeTiedot(int id)
{  
    olio5mysql->getDonateInfo(id);
}

void Lahjoita::on_btnLahjoita_clicked()
{
    bool x = olio5mysql->payDonation(lahjoituskohdeID,idTili,lahjoitusSumma);

    if (x == true)
    {
        QMessageBox onnistui;
        double saldo = olio5mysql->showBalance(idTili);
        QString teksti = QString("Lahjoitus onnistui.\n"
                                 "Tilille jai rahaa: %1 €\n\n"
                                 "Kiitos lahjoituksesta.").arg(saldo);
        onnistui.setText(teksti);
        onnistui.exec();
        this->close();
    }

        else
        {
            double saldo = olio5mysql->showBalance(idTili);
            QMessageBox eionnistu;
            QString teksti = QString("Lahjoitus epäonnistui, tililla ei ole katetta.\n"
                                     "Tilin saldo on: %1 €").arg(saldo);
            eionnistu.setText(teksti);
            eionnistu.exec();
        }
}
