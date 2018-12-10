#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QLibrary>
//#include "dll/rfiddll.h"
//#include "dll/pincodedll.h"
//#include "dll/dllmysql.h"
#include "rfiddll.h"
#include "pincodedll.h"
#include "dllmysql.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   // ui->pushButton->setEnabled(false);

//    QLibrary library("rfiddll.dll");
//    library.load();

//    if (library.isLoaded()) {
//        qDebug() << "success";

//        // Resolves symbol to
//        // void the_function_name()
//        typedef void (*FunctionPrototype)();
//        auto function1 = (FunctionPrototype)library.resolve("initialiseSerialPort");
//        if (function1) function1();
//        connect(library, SIGNAL(userLoginSignal(QString)), this, SLOT(login(QString)));
//    }

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
    connect(ui->pushButton_sim, SIGNAL (clicked()), this, SLOT(on_pushButton_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete olioRfidDLL;
    delete olioSignedIn;
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

    int hyvaksytty = olioMysqlDLL->validatePINCode(pin,idTili);
    if (hyvaksytty==1){
        qDebug() << "PIN ok, welcome" << pin;
        olioSignedIn = new SignedInDialog(this);
        olioSignedIn->show();

    }else
    {
        qDebug() << "PIN vaarin" << pin;
        QMessageBox msgBox;
        msgBox.setText("PINNI EI KELPAA !!!");
        msgBox.exec();
    }



    /*if (!userID.isEmpty() && !pin.isEmpty())
    {
        qDebug() << "PIN ok, welcome" << pin;
        ui->label_PIN->setText(pin);
        QMessageBox msgBox;
        msgBox.setText("Welcome");
        msgBox.exec();
    }*/
}

void MainWindow::login(QString id)
{
    qDebug() << "User logged in: " << id;
    ui->label->setText(id);
   // ui->pushButton->setEnabled(true);
    userID = id;

    //lahetetaan kortti id kantaan ja saadaan sielta tili id takaisin.
    idTili = olioMysqlDLL->validateCard(id);
    qDebug() << "MainWindow idTili: " << idTili << endl; //taman perusteella voidaan paatella onko kortti hyvaksytty. 0 ei ole yli nolla on.
}

