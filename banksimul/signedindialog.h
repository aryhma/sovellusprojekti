#ifndef SIGNEDINDIALOG_H
#define SIGNEDINDIALOG_H

#include <QDialog>

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

    QString Kayttaja = "";
};

#endif // SIGNEDINDIALOG_H
