#include "dllmysql.h"

#include <QtSql>
#include <QSqlQuery>
#include <QSqlQueryModel>

#include "connection.h"

#include <QDebug>

using namespace std;

DLLMySQL::DLLMySQL()
{
}

bool DLLMySQL::mysqlconnection()
{
    qDebug() << "alustetaan kanta yhteys" << endl;
    if (!createConnection()){
        qDebug() << "MYSQLDLL -> Tietokanta yhteys ei onnistu.. Pieleen menee." << endl;
        //miten saadaan softa kaatumaan, jos kanta yhteys ei onnistu, joko taalla tai paaohjelmassa??
        return false;
    }else{
        qDebug() << "MYSQLDLL -> Tietokanta yhteys onnistui" << endl;
        return true;
    }
}

bool DLLMySQL::validateCard(QString cardId)
{
    qDebug() << "MYSQLDLL sain kortin:" << cardId << endl;

    /*QSqlQuery haku;
    haku.prepare("select idTili from kortti where korttiTunniste=(:tunniste)");
    haku.bindValue(":tunniste", param1);
    int idTili=0;
    idTili = haku.exec();
    qDebug() << "MYSQLDLL idTili:" << idTili << endl;*/


    QSqlTableModel *kortti = new QSqlTableModel();
    kortti->setTable("kortti");
    kortti->setFilter(QString("korttiTunniste='%1'").arg(cardId));
    kortti->select();
    //qDebug() << "MYSQLDLL sain: " << tulos << "recordia" << endl;

    //tuloksen debuggausta varten..
    /*QString id = kortti->data(kortti->index(0,0)).toString();
    QString tili = kortti->data(kortti->index(0,1)).toString();
    QString korttiN = kortti->data(kortti->index(0,2)).toString();
    qDebug() <<"idkortti: " << id <<" idTili: " << tili << " idKortti: " << korttiN;*/

    int idTili = 0;
    idTili = kortti->record(0).value("idTili").toInt();
    //qDebug() << "tili id inttina: " << idTili << endl;

    return idTili;

}

