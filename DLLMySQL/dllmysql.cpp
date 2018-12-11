#include "dllmysql.h"

#include <QtSql>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>

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

    QSqlQuery haku;
    haku.prepare("select idTili from kortti where korttiTunniste=:tunniste");
    haku.bindValue(":tunniste", cardId);
    haku.exec();
    haku.next();
    int idTili = haku.value(0).toInt();
    qDebug() << "MYSQLDLL qsqlquery testi idTili:" << idTili << endl;


    /*QSqlTableModel *kortti = new QSqlTableModel();
    kortti->setTable("kortti");
    kortti->setFilter(QString("korttiTunniste='%1'").arg(cardId));
    kortti->select();*/
    //qDebug() << "MYSQLDLL sain: " << tulos << "recordia" << endl;

    //tuloksen debuggausta varten..
    /*QString id = kortti->data(kortti->index(0,0)).toString();
    QString tili = kortti->data(kortti->index(0,1)).toString();
    QString korttiN = kortti->data(kortti->index(0,2)).toString();
    qDebug() <<"idkortti: " << id <<" idTili: " << tili << " idKortti: " << korttiN;*/

    /*idTili = 0;
    idTili = kortti->record(0).value("idTili").toInt();*/
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

    QSqlQuery nimi;
    nimi.prepare("select etunimi,sukunimi from asiakas where idAsiakas in (select idAsiakas from tili where idTili=:tili)");
    nimi.bindValue(":tili", idTili);
    nimi.exec();
    nimi.next();
    QString etunimi = nimi.value(0).toString();
    QString sukunimi = nimi.value(1).toString();

    /*QSqlTableModel *name = new QSqlTableModel();
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
    QString sukunimi = flname->data(flname->index(0,2)).toString();*/
    //QString etunimi = flname->record(0).value("etunimi");
    qDebug() << "DLLMySQL etunimi:" << etunimi << "sukunimi:" << sukunimi;
    QString fullname = etunimi + " " + sukunimi;
    qDebug() << "DLLMySQL nimi:" << fullname;
    return fullname;
}

float DLLMySQL::showBalance(int idTili)
{
    //mika tili tulee ja haetaan asiakasid
    qDebug() << "MYSQLDLL showBalance sain tiliID: " << idTili;

    QSqlQuery saldo;
    saldo.prepare("select tiliSaldo from tili where idTili=:tili");
    saldo.bindValue(":tili", idTili);
    saldo.exec();
    saldo.first();
    float saldosi = saldo.value(0).toFloat();

    qDebug() << "DLLMySQL showBalance saldo on: " << saldosi;
    return saldosi;
}

QSqlTableModel* DLLMySQL::showTransactions(int idTili)
{
    qDebug() << "MYSQLDLL showTransactions sain tiliID: " << idTili;
    QSqlTableModel *tilitapahtumat = new QSqlTableModel;
    tilitapahtumat->setTable("tilitapahtumat");
    tilitapahtumat->setFilter(QString("idTili='%1' ORDER BY tilitapahtumatAika").arg(idTili));
    tilitapahtumat->select();
    tilitapahtumat->removeColumns(0,2); //poistetaan ekat 2 saraketta..
    tilitapahtumat->setHeaderData(0, Qt::Horizontal, QObject::tr("Tapahtuma")); //nimetaan sarakkeet nayttoa varten.
    tilitapahtumat->setHeaderData(1, Qt::Horizontal, QObject::tr("Summa"));
    tilitapahtumat->setHeaderData(2, Qt::Horizontal, QObject::tr("Paivamaara"));
    return tilitapahtumat;
}
