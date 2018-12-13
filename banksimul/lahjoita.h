#ifndef LAHJOITA_H
#define LAHJOITA_H

#include <QDialog>

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

private slots:
    void on_btnBack_clicked();

    void on_btnAmnesty_clicked();

    void on_btnWWF_clicked();

    void on_btnPunainenRisti_clicked();

    void on_btnKummitRy_clicked();

    void on_sBoxLahjSumma_valueChanged();

    void asetaTiedot(QString tilinumero, QString saaja, QString viite);

private:
    Ui::Lahjoita *ui;

    double saldo=0.0;
    int lahjoitusSumma=0;
    int idTili;
    int lahjoituskohdeID=0;
};

#endif // LAHJOITA_H
