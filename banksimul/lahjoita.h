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

private:
    Ui::Lahjoita *ui;

    double saldo=0.0;
    int lahjoitusSumma=0;
};

#endif // LAHJOITA_H
