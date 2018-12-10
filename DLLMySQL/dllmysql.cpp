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
    qDebug() << "alustetaan kanta yhteys";
    if (!createConnection()){
        qDebug() << "MYSQLDLL -> Tietokanta yhteys ei onnistu.. Pieleen menee.";
        //miten saadaan softa kaatumaan, jos kanta yhteys ei onnistu, joko taalla tai paaohjelmassa??
        return false;
    }else{
        qDebug() << "MYSQLDLL -> Tietokanta yhteys onnistui";
        return true;
    }
}

bool DLLMySQL::validateCard(QString cardId)
{
    qDebug() << "MYSQLDLL sain kortin:" << cardId;

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

bool DLLMySQL::validatePINCode(QString pin2, int tili)
{
    //QString tili2 = QString::number(tili);
    qDebug() << "MYSQLDLL sain pinnin: " << pin2 << " ja tili ideen :" << tili;

    QSqlTableModel *pin = new QSqlTableModel();
    pin->setTable("kortti");
    pin->setFilter(QString("idTili='%1' and korttiPin='%2'").arg(tili).arg(pin2));
    pin->select();

    int rivit = pin->rowCount();
    //idTili = pin->record(0).value("idTili").toInt();
    qDebug() << "DLLMySQL pin kyseselyn rivi maara: " << rivit;

    return rivit;
}

QString DLLMySQL::findName(int idTili)
{
    //mika tili tulee ja haetaan asiakasid
    qDebug() << "MYSQLDLL sain tiliID: " << idTili;

    QSqlTableModel *name = new QSqlTableModel();
    name->setTable("tili");
    name->setFilter(QString("idTili='%1'").arg(idTili));
    name->select();

    int idAsiakas = name->record(0).value("idAsiakas").toInt();
    qDebug() << "DLLMySQL kannasta haettu asiakasid: " << idAsiakas;

    QSqlTableModel *flname = new QSqlTableModel();
    flname->setTable("asiakas");
    flname->setFilter(QString("idAsiakas='%1'").arg(idAsiakas));
    flname->select();

    //int rivit = flname->rowCount();
    //qDebug() << "rivi maara: " << rivit;
    QString etunimi = flname->data(flname->index(0,1)).toString();
    QString sukunimi = flname->data(flname->index(0,2)).toString();
    //QString etunimi = flname->record(0).value("etunimi");
    qDebug() << "DLLMySQL etunimi:" << etunimi << "sukunimi:" << sukunimi;
    QString fullname = etunimi + " " + sukunimi;
    qDebug() << "DLLMySQL nimi:" << fullname;
    return fullname;
}
