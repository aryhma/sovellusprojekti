#ifndef SIGNEDINDIALOG_H
#define SIGNEDINDIALOG_H

#include <QDialog>
#include <dllmysql.h>
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

private slots:
    void on_btnUlos_clicked();

    void on_btnSaldo_clicked();

    void on_btnTapahtumat_clicked();

private:
    Ui::SignedInDialog *ui;

    DLLMySQL *olio2MysqlDLL;
    int idTili;

    QString Kayttaja = "Default";
};

#endif // SIGNEDINDIALOG_H
