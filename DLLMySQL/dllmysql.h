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
    float DLLMYSQLSHARED_EXPORT raiseMoney(int, int);
    double DLLMYSQLSHARED_EXPORT showBalance(int);
    QSqlTableModel *showTransactions(int);

};

#endif // DLLMYSQL_H
