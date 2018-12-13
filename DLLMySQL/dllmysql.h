#ifndef DLLMYSQL_H
#define DLLMYSQL_H

#include "QSqlTableModel"

#include "dllmysql_global.h"

class DLLMYSQLSHARED_EXPORT DLLMySQL
{

public:
    DLLMySQL();
    bool DLLMYSQLSHARED_EXPORT validateCard(QString cardId);
    bool DLLMYSQLSHARED_EXPORT validatePINCode(QString , int);
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
};

#endif // DLLMYSQL_H
