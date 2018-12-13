#ifndef SIGNEDINDIALOG_H
#define SIGNEDINDIALOG_H

#include <QDialog>
#include <dllmysql.h>
#include "saldo.h"
#include "nosta.h"
#include "lahjoita.h"
#include "maksa.h"
//#include <dll/dllmysql.h>

namespace Ui {
class SignedInDialog;
}

class SignedInDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SignedInDialog(QWidget *parent = nullptr);
    ~SignedInDialog();

    void alustaTiedot(QString kayt, int id) {Kayttaja = kayt; idTili=id; asetaOtsikko();}
    void asetaOtsikko();
    void showTable();

signals:
    void sendBalance(double);
    void lahetaKayttaja(QString);

private slots:

    void on_btnUlos_clicked();

    void on_btnSaldo_clicked();

    void on_btnTapahtumat_clicked();

    void on_btnNosta_clicked();

    void on_btnLahjoita_clicked();

    void on_btnMaksa_clicked();

    void tableClose();

private:
    Ui::SignedInDialog *ui;
    Saldo *olioSaldo;
    DLLMySQL *olio2MysqlDLL;
    Nosta *olioNosta;
    Lahjoita *olioLahjoita;
    Maksa *olioMaksa;
    QPushButton *btnPoistu;
    QWidget *tableWindow;
    int idTili;

    QString Kayttaja = "Default";
};

#endif // SIGNEDINDIALOG_H
