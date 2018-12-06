#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include "dll/rfiddll.h"
#include "dll/pincodedll.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton->setEnabled(false);

    qDebug() << "UI initialising, loading DLL";
    olioRfidDLL = new RfidDLL;
    olioRfidDLL->initialiseSerialPort();
    connect(olioRfidDLL, SIGNAL(userLoginSignal(QString)), this, SLOT(login(QString)));
    qDebug() << "DLL loaded, waiting for user logon";

    // this to test the user login without actual rf reader
    connect(ui->pushButton_sim, SIGNAL (clicked()), olioRfidDLL, SLOT(simulateUserLoggedIn()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete olioRfidDLL;
}

void MainWindow::on_pushButton_clicked()
{
    qDebug() << "Checking PIN, loading pincodeDLL";

    olioPincodeDLL = new PincodeDLL;
    olioPincodeDLL->getPIN(this);
    connect(olioPincodeDLL, SIGNAL(validatePIN(QString)), this, SLOT(validatePIN(QString)));
}

void MainWindow::validatePIN(QString pin)
{
    qDebug() << "validating PIN" << pin;

    if (!userID.isEmpty() && !pin.isEmpty())
    {
        qDebug() << "PIN ok, welcome" << pin;
        ui->label_PIN->setText(pin);
        QMessageBox msgBox;
        msgBox.setText("Welcome");
        msgBox.exec();
    }
}

void MainWindow::login(QString id)
{
    qDebug() << "User logged in: " << id;
    ui->label->setText(id);
    ui->pushButton->setEnabled(true);
    userID = id;
}

