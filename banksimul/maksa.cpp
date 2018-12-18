#include "maksa.h"
#include "ui_maksa.h"
#include <QMessageBox>

Maksa::Maksa(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Maksa)
{
    ui->setupUi(this);
    olio4mysql = new DLLMySQL;

    connect(olio4mysql, SIGNAL(lahetaSumma(double)), this, SLOT(asetaSumma(double)));
    connect(olio4mysql, SIGNAL(sendTili(QString)), this, SLOT(asetaTili(QString)));
    connect(olio4mysql, SIGNAL(sendSaaja(QString)), this, SLOT(asetaSaaja(QString)));
    connect(olio4mysql, SIGNAL(sendViite(QString)), this, SLOT(asetaViite(QString)));
}

Maksa::~Maksa()
{
    delete ui;
    delete olio4mysql;
}

void Maksa::on_btnPeruuta_clicked()
{
    this->close();
}

void Maksa::on_btnHaeTiedot_clicked()
{
    if(laskujenMaara==0)
    {
        ui->lblMaksamatta->setText("Ei maksamattomia laskuja!");
    }
        else
        {
            laskuID = olio4mysql->getInvoiceId(idTili);
            olio4mysql->getInvoiceDetails(laskuID);
            asetaTiedot(tilinumero,saaja,viite,summa);
            ui->lblMaksamatta->setText("Laskuja maksamatta "+ QString::number(laskujenMaara)+ " kpl");
        }
}


void Maksa::on_btnMaksa_clicked()
{
    if (summa>0)
    {
        bool testi = olio4mysql->payInvoice(laskuID,idTili,summa);

            if (testi==true)
            {
                QMessageBox onnistui;
                double saldo = olio4mysql->showBalance(idTili);
                QString teksti = QString("Laskun maksu onnistui.\n\n"
                                         "Tilille jai rahaa: %1 €").arg(saldo);
                onnistui.setText(teksti);
                onnistui.exec();
            }
                else
                {
                    QMessageBox eionnistu;
                    double saldo = olio4mysql->showBalance(idTili);
                    QString teksti = QString("Laskun maksu ei onnistu, tililla ei ole katetta.\n\n"
                                             "Tilillä on rahaa: %1 €").arg(saldo);
                    eionnistu.setText(teksti);
                    eionnistu.exec();
                }

        tyhjenna();
        laskujenMaara = olio4mysql->invoiceCount(idTili);
        ui->lblMaksamatta->setText("Laskuja maksamatta "+ QString::number(laskujenMaara)+ " kpl");
    }
}

void Maksa::asetaTiedot(QString tilinumero, QString saaja, QString viite, double summa)
{
    ui->lineLaskuSaajaTiliN->setText(tilinumero);
    ui->lineLaskuSaaja->setText(saaja);
    ui->lineLaskuViite->setText(viite);
    ui->lineLaskuSumma->setText(QString("%1").arg(summa));
}

void Maksa::tyhjenna()
{
    ui->lineLaskuSaajaTiliN->setText("");
    ui->lineLaskuSaaja->setText("");
    ui->lineLaskuViite->setText("");
    ui->lineLaskuSumma->setText("");
}
