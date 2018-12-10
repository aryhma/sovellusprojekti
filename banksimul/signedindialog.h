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

private:
    Ui::SignedInDialog *ui;

    DLLMySQL *olio2MysqlDLL;

    QString Kayttaja = "Default";
};

#endif // SIGNEDINDIALOG_H
