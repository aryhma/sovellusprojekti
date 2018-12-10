#ifndef PINCODEDIALOG_H
#define PINCODEDIALOG_H

#include <QDialog>

namespace Ui {
class PincodeDialog;
}

class PincodeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PincodeDialog(QWidget *parent = nullptr);
    ~PincodeDialog();

private slots:
    void on_pushButton_clicked();

    void on_btn1_clicked();

    void on_btn2_clicked();

    void on_btn3_clicked();

    void on_btn4_clicked();

    void on_btn5_clicked();

    void on_btn6_clicked();

    void on_btn7_clicked();

    void on_btn8_clicked();

    void on_btn9_clicked();

signals:
    void receivedPIN(QString);

private:
    Ui::PincodeDialog *ui;
    QString pin="";
    QString prv="";
};

#endif // PINCODEDIALOG_H
