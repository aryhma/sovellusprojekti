#ifndef LAHJOITA_H
#define LAHJOITA_H

#include <QDialog>
#include "dllmysql.h"

namespace Ui {
class Lahjoita;
}

class Lahjoita : public QDialog
{
    Q_OBJECT

public:
    explicit Lahjoita(QWidget *parent = nullptr);
    ~Lahjoita();

    void asetaSaldo(double s){saldo=s;}
    void asetaTili(int i){idTili = i;}

public  slots:
    void asetaTiedot(QString tilinumero, QString saaja, QString viite);
    void asetaTili(QString a){tilinumero=a;}
    void asetaViite(QString a){viite=a;}
    void asetaSaaja(QString a){saaja=a;}

private slots:
    void on_btnBack_clicked();

    void on_btnAmnesty_clicked();

    void on_btnWWF_clicked();

    void on_btnPunainenRisti_clicked();

    void on_btnKummitRy_clicked();

    void on_sBoxLahjSumma_valueChanged();

    //void asetaTiedot(QString tilinumero, QString saaja, QString viite);

    void haeTiedot(int);

    void on_btnLahjoita_clicked();

private:
    Ui::Lahjoita *ui;

    DLLMySQL *olio5mysql;

    QString tilinumero ="";
    QString saaja = "";
    QString viite = "";
    double saldo=0.0;
    int lahjoitusSumma=0;
    int idTili;
    int lahjoituskohdeID=0;
};

#endif // LAHJOITA_H
