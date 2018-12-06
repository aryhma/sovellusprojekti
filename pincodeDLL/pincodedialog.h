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

signals:
    void receivedPIN(QString);

private:
    Ui::PincodeDialog *ui;
    QString pin="";
};

#endif // PINCODEDIALOG_H
