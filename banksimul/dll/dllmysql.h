#ifndef DLLMYSQL_H
#define DLLMYSQL_H

#include "dllmysql_global.h"

class DLLMYSQLSHARED_EXPORT DLLMySQL
{

public:
    DLLMySQL();
    bool DLLMYSQLSHARED_EXPORT validateCard(QString cardId);
    void DLLMYSQLSHARED_EXPORT validatePIN(QString);
    bool DLLMYSQLSHARED_EXPORT mysqlconnection();

};

#endif // DLLMYSQL_H
