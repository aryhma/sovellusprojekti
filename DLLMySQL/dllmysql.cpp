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

double DLLMySQL::raiseMoney(int idTili, int nosto)
{
    //mika tili tulee ja nosto summa
    qDebug() << "MYSQLDLL raiseMoney tiliID: " << idTili << " nostosumma: " << nosto;

    //ensin pitaa tarkistaa onko tililla katetta..
    QSqlQuery saldo;
    saldo.prepare("select tiliSaldo from tili where idTili=:tili");
    saldo.bindValue(":tili", idTili);
    saldo.exec();
    saldo.first();
    double saldosi = saldo.value(0).toDouble();
    qDebug() << "DLLMySQL raiseMoney saldo kannasta ennen paivitysta on: " << saldosi;

    if (saldosi >= nosto)
    {
        qDebug() << "DLLMySQL raiseMoney, tehdaan kanta insert ja update";
        QSqlQuery insert1;
        insert1.prepare("INSERT INTO tilitapahtumat (idTili,tilitapahtumatLaji,tilitapahtumatSumma,tilitapahtumatAika) "
                        "VALUES (:tili, 'otto',:sum,now())");
        insert1.bindValue(":tili", idTili);
        insert1.bindValue(":sum", nosto);
        insert1.exec();

        QSqlQuery update;
        update.prepare("update tili set tiliSaldo=tiliSaldo-:sum where idTili=:tili");
        update.bindValue(":tili", idTili);
        update.bindValue(":sum", nosto);
        update.exec();

        QSqlQuery saldo2;
        saldo2.prepare("select tiliSaldo from tili where idTili=:tili");
        saldo2.bindValue(":tili", idTili);
        saldo2.exec();
        saldo2.first();
        saldosi = saldo2.value(0).toDouble();

    }else
    {
       saldosi=-1;
    }

    qDebug() << "MYSQLDLL raiseMoney palautus  saldo: " << saldosi;
    return saldosi;
}

double DLLMySQL::showBalance(int idTili)
{
    //mika tili tulee ja haetaan asiakasid
    qDebug() << "MYSQLDLL showBalance sain tiliID: " << idTili;

    QSqlQuery saldo;
    saldo.prepare("select tiliSaldo from tili where idTili=:tili");
    saldo.bindValue(":tili", idTili);
    saldo.exec();
    saldo.first();
    double saldosi = saldo.value(0).toDouble();

    qDebug() << "DLLMySQL showBalance saldo on: " << saldosi;
    return saldosi;
}

QSqlTableModel* DLLMySQL::showTransactions(int idTili)
{
    qDebug() << "MYSQLDLL showTransactions sain tiliID: " << idTili;
    QSqlTableModel *tilitapahtumat = new QSqlTableModel;
    tilitapahtumat->setTable("tilitapahtumat");
    tilitapahtumat->setFilter(QString("idTili='%1' ORDER BY tilitapahtumatAika DESC limit 9").arg(idTili));
    tilitapahtumat->select();
    tilitapahtumat->removeColumns(0,2); //poistetaan ekat 2 saraketta..
    tilitapahtumat->setHeaderData(0, Qt::Horizontal, QObject::tr("Tapahtuma")); //nimetaan sarakkeet nayttoa varten.
    tilitapahtumat->setHeaderData(1, Qt::Horizontal, QObject::tr("Summa"));
    tilitapahtumat->setHeaderData(2, Qt::Horizontal, QObject::tr("Paivamaara"));
    return tilitapahtumat;
}
