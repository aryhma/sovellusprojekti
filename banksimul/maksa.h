#ifndef MAKSA_H
#define MAKSA_H

#include <QDialog>

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

private slots:
    void on_btnPeruuta_clicked();

    void on_btnHaeTiedot_clicked();

    void asetaTiedot(QString tilinumero, QString saaja, QString viite, double summa);

    void tyhjenna();

    void on_btnMaksa_clicked();

private:
    Ui::Maksa *ui;

    double saldo=0.0;
    int laskujenMaara= 5;
    double laskunSumma=0;
    int idTili;
    int laskuID=0;
};

#endif // MAKSA_H
