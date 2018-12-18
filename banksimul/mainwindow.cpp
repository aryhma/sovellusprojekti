#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QLibrary>
#include "rfiddll.h"
#include "pincodedll.h"
#include "dllmysql.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    olioPincodeDLL = new PincodeDLL;

    qDebug() << "UI initialising, loading DLL";

    try {
        olioRfidDLL = new RfidDLL;
        olioRfidDLL->initialiseSerialPort();
        connect(olioRfidDLL, SIGNAL(userLoginSignal(QString)), this, SLOT(login(QString)));
    } catch( std::bad_alloc& e ) {
        QMessageBox msgBox;
        msgBox.setText("Welcome");
        msgBox.exec();
      qDebug() << "1";
    } catch(std::exception& e) {
        QMessageBox msgBox;
        msgBox.setText(e.what());
        msgBox.exec();
      qDebug() << e.what();
    }

    qDebug() << "DLL loaded, waiting for user logon";

    //Kanta login testi
    olioMysqlDLL = new DLLMySQL;
    if (olioMysqlDLL->mysqlconnection()==false)
    {
        QMessageBox msgBox;
        msgBox.setText("Tietokanta yhteys epaonnistui!!");
        msgBox.exec();
    }

    // this to test the user login without actual rf reader
    connect(ui->pushButton_sim, SIGNAL (clicked()), olioRfidDLL, SLOT(simulateUserLoggedIn()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete olioRfidDLL;
    delete olioSignedIn;
    delete olioMysqlDLL;
}

void MainWindow::validatePIN(QString pin)
{
    qDebug() << "validating PIN" << pin;

    int hyvaksytty = olioMysqlDLL->validatePINCode(pin,idTili);

    if (hyvaksytty==1)
    {
       qDebug() << "PIN ok, welcome" << pin;
       olioSignedIn = new SignedInDialog;
       olioSignedIn->alustaTiedot(olioMysqlDLL->findName(idTili), idTili);
       olioSignedIn->show();

    }
        else
        {
            qDebug() << "PIN vaarin" << pin;
            QMessageBox msgBox;
            msgBox.setText("PINNI EI KELPAA !!!");
            msgBox.exec();
        }

}

void MainWindow::login(QString id)
{
    qDebug() << "User logged in: " << id;
    ui->label->setText(id);

    userID = id;

    //lahetetaan kortti id kantaan ja saadaan sielta tili id takaisin.
    idTili = olioMysqlDLL->validateCard(id);
    qDebug() << "MainWindow idTili: " << idTili; //taman perusteella voidaan paatella onko kortti hyvaksytty. 0 ei ole yli nolla on.

    olioPincodeDLL->getPIN(this);
    connect(olioPincodeDLL, SIGNAL(validatePIN(QString)), this, SLOT(validatePIN(QString)));
}


void MainWindow::on_btnSammuta_clicked()
{
    this->close();
}
