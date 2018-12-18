#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "signedindialog.h"
#include "dllmysql.h"
#include "rfiddll.h"
#include "pincodedll.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void login(QString);

    void on_btnSammuta_clicked();

public slots:
    void validatePIN(QString pin);

    int valitaTili () {return idTili;}

signals:

private:
    Ui::MainWindow *ui;
    RfidDLL *olioRfidDLL;
    PincodeDLL *olioPincodeDLL;
    DLLMySQL *olioMysqlDLL;
    SignedInDialog *olioSignedIn;

    QString pin="";
    QString userID="";
    int idTili;
};

#endif // MAINWINDOW_H
