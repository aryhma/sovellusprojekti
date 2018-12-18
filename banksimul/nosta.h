#ifndef NOSTA_H
#define NOSTA_H

#include <QDialog>
#include <dllmysql.h>

namespace Ui {
class Nosta;
}

class Nosta : public QDialog
{
    Q_OBJECT

public:
    explicit Nosta(QWidget *parent = nullptr);
    ~Nosta();

public slots:
    void asetaSaldo(double s){saldo=s;}

    void asetaTili(int t){idTili=t;}

private slots:

    void vaihdaTeksti(int i);

    void on_btn20_clicked();

    void on_btn40_clicked();

    void on_btn60_clicked();

    void on_btn80_clicked();

    void on_btn100_clicked();

    void on_btnPeruuta_clicked();

    void on_btnnosta_clicked();

    void on_spinBoxSumma_valueChanged();

private:
    Ui::Nosta *ui;

    DLLMySQL *olio3MysqlDLL;

    int nostoSumma = 0;
    double saldo = 0.0;
    int idTili;
    double saldoP = 0.0; //palautuva saldo kannasta.
};

#endif // NOSTA_H
