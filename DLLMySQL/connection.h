#ifndef CONNECTION_H
#define CONNECTION_H

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

static bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("mysli.oamk.fi");
    db.setDatabaseName("opisk_t7muto00");
    db.setUserName("t7muto00");
    db.setPassword("9tBrprWya6LLEYgE");

    if (!db.open())
    {
        return false;
    }

    return true;
}

#endif // CONNECTION_H
