#include "maksa.h"
#include "ui_maksa.h"

Maksa::Maksa(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Maksa)
{
    ui->setupUi(this);
}

Maksa::~Maksa()
{
    delete ui;
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
       static QString testitili = "fi23334323";
       static QString testisaaja = "Matti Meikalainen";
       static QString testiviite = "3332 2222 33333";
       static double testisumma = 324.55;

        asetaTiedot(testitili,testisaaja,testiviite,testisumma);
        ui->lblMaksamatta->setText("Laskuja maksamatta "+ QString::number(laskujenMaara)+ " kpl");
    }
}


void Maksa::on_btnMaksa_clicked()
{
    tyhjenna();
    laskujenMaara--;
    ui->lblMaksamatta->setText("Laskuja maksamatta "+ QString::number(laskujenMaara)+ " kpl");
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
