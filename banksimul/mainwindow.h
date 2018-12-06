#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "dll/rfiddll.h"
#include "dll/pincodedll.h"

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
    void on_pushButton_clicked();

public slots:
    void validatePIN(QString pin);

signals:

private:
    Ui::MainWindow *ui;
    RfidDLL *olioRfidDLL;
    PincodeDLL *olioPincodeDLL;

    QString pin="";
    QString userID="";
};

#endif // MAINWINDOW_H