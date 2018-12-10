#ifndef DLLMYSQL_H
#define DLLMYSQL_H

#include "dllmysql_global.h"

class DLLMYSQLSHARED_EXPORT DLLMySQL
{

public:
    DLLMySQL();
    bool DLLMYSQLSHARED_EXPORT validateCard(QString cardId);
    bool DLLMYSQLSHARED_EXPORT validatePINCode(QString , int);
    bool DLLMYSQLSHARED_EXPORT mysqlconnection();
};

#endif // DLLMYSQL_H
