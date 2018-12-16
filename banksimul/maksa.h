#ifndef MAKSA_H
#define MAKSA_H

#include <QDialog>
#include "dllmysql.h"

namespace Ui {
class Maksa;
}

class Maksa : public QDialog
{
    Q_OBJECT

public:
    explicit Maksa(QWidget *parent = nullptr);
    ~Maksa();

    void asetaSaldo(double s){saldo=s;}
    void asetaTili(int i){idTili = i;}
    void asetaLaskujenMaara(int m){laskujenMaara=m;}

public slots:


private slots:
    void on_btnPeruuta_clicked();

    void on_btnHaeTiedot_clicked();

    void asetaTiedot(QString tilinumero, QString saaja, QString viite, double summa);

    void tyhjenna();

    void on_btnMaksa_clicked();

    void asetaSumma(double i){summa=i;}
    void asetaTili(QString a){tilinumero=a;}
    void asetaViite(QString a){viite=a;}
    void asetaSaaja(QString a){saaja=a;}

private:
    Ui::Maksa *ui;

    DLLMySQL *olio4mysql;

    QString tilinumero;
    QString saaja;
    QString viite;

    double saldo=0.0;
    int laskujenMaara=0;
    double laskunSumma=0;
    int idTili;
    int laskuID=0;
    double summa = 0;
};

#endif // MAKSA_H
