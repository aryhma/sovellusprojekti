#ifndef SALDO_H
#define SALDO_H

#include <QDialog>
#include <dllmysql.h>

namespace Ui {
class Saldo;
}

class Saldo : public QDialog
{
    Q_OBJECT

public:
    explicit Saldo(QWidget *parent = nullptr);
    ~Saldo();

    void asetaTiliId(int arvo){tiliId = arvo;}

private slots:

    void asetaKayttaja(QString kayt);
    void naytaSaldo(double arvo);
    void naytaTapahtumat(int tiliid);
    void on_btnTakaisin_clicked();

private:
    Ui::Saldo *ui;
    DLLMySQL *olioSaldoMysqlDLL;
    int tiliId = 0;
};

#endif // SALDO_H
