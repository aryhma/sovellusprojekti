#ifndef DLLMYSQL_H
#define DLLMYSQL_H

#include "QSqlTableModel"
#include <QObject>

#include "dllmysql_global.h"

class DLLMYSQLSHARED_EXPORT DLLMySQL: public QObject
{
    Q_OBJECT
public:
    DLLMySQL();
    int DLLMYSQLSHARED_EXPORT validateCard(QString cardId);
    int DLLMYSQLSHARED_EXPORT validatePINCode(QString , int);
    bool DLLMYSQLSHARED_EXPORT mysqlconnection();
    QString DLLMYSQLSHARED_EXPORT findName(int);
    double DLLMYSQLSHARED_EXPORT raiseMoney(int, int);
    double DLLMYSQLSHARED_EXPORT showBalance(int);
    QSqlTableModel *showTransactions(int, int);
    int DLLMYSQLSHARED_EXPORT invoiceCount(int);
    int DLLMYSQLSHARED_EXPORT getInvoiceId(int);
    void DLLMYSQLSHARED_EXPORT getInvoiceDetails(int);
    //double DLLMYSQLSHARED_EXPORT getInvoiceDetailsD(int);
    bool DLLMYSQLSHARED_EXPORT payInvoice(int,int,double);
    void DLLMYSQLSHARED_EXPORT getDonateInfo(int);
    bool DLLMYSQLSHARED_EXPORT payDonation(int,int,int); //mita, milta,paljonko

signals:
    void DLLMYSQLSHARED_EXPORT sendTili(QString);
    void DLLMYSQLSHARED_EXPORT sendSaaja(QString);
    void DLLMYSQLSHARED_EXPORT sendViite(QString);
    void DLLMYSQLSHARED_EXPORT lahetaSumma(double);

    //void DLLMYSQLSHARED_EXPORT sendDonateInfo(QString,QString,QString);
    //void DLLMYSQLSHARED_EXPORT lahetatiedot(QString,QString,QString);

private:
    //QString arvo1 = "";
};

#endif // DLLMYSQL_H
