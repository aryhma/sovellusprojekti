#ifndef SALDO_H
#define SALDO_H

#include <QDialog>

namespace Ui {
class Saldo;
}

class Saldo : public QDialog
{
    Q_OBJECT

public:
    explicit Saldo(QWidget *parent = nullptr);
    ~Saldo();

private slots:

    void asetaKayttaja(QString kayt);
    void naytaSaldo(double arvo);
    void on_btnTakaisin_clicked();

private:
    Ui::Saldo *ui;
};

#endif // SALDO_H
