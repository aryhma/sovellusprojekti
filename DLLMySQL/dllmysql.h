#ifndef DLLMYSQL_H
#define DLLMYSQL_H

#include "QSqlTableModel"

#include "dllmysql_global.h"

class DLLMYSQLSHARED_EXPORT DLLMySQL
{

public:
    DLLMySQL();
    int DLLMYSQLSHARED_EXPORT validateCard(QString cardId);
    int DLLMYSQLSHARED_EXPORT validatePINCode(QString , int);
    bool DLLMYSQLSHARED_EXPORT mysqlconnection();
    QString DLLMYSQLSHARED_EXPORT findName(int);
    double DLLMYSQLSHARED_EXPORT raiseMoney(int, int);
    double DLLMYSQLSHARED_EXPORT showBalance(int);
    QSqlTableModel *showTransactions(int);
    int DLLMYSQLSHARED_EXPORT invoiceCount(int);
    int DLLMYSQLSHARED_EXPORT getInvoiceId(int);
    QString DLLMYSQLSHARED_EXPORT getInvoiceDetails(int,int);
    double DLLMYSQLSHARED_EXPORT getInvoiceDetailsD(int);
    bool DLLMYSQLSHARED_EXPORT payInvoice(int,int,double);
    QString DLLMYSQLSHARED_EXPORT getDonateInfo(int,int);
    bool DLLMYSQLSHARED_EXPORT payDonation(int,int,int); //mita, milta,paljonko
};

#endif // DLLMYSQL_H
