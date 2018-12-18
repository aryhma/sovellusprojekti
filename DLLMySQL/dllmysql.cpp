#include "dllmysql.h"

#include <QtSql>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>

#include "connection.h"

#include <QDebug>

using namespace std;

DLLMySQL::DLLMySQL(){};

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

int DLLMySQL::validateCard(QString cardId)
{
    qDebug() << "MYSQLDLL sain kortin:" << cardId;

    QSqlQuery haku;
    haku.prepare("select idTili from kortti where korttiTunniste=:tunniste");
    haku.bindValue(":tunniste", cardId);
    haku.exec();
    haku.next();

    int idTili = haku.value(0).toInt();
    qDebug() << "MYSQLDLL qsqlquery idTili:" << idTili << endl;

    return idTili;

}

int DLLMySQL::validatePINCode(QString pin2, int tili)
{
    qDebug() << "MYSQLDLL sain pinnin: " << pin2 << " ja tili ideen :" << tili;

    QSqlTableModel *pin = new QSqlTableModel();
    pin->setTable("kortti");
    pin->setFilter(QString("idTili='%1' and korttiPin='%2'").arg(tili).arg(pin2));
    pin->select();

    int rivit = pin->rowCount();
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

    }
        else
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

QSqlTableModel* DLLMySQL::showTransactions(int idTili, int tapahtumiaKpl) // tapahtumiaKpl rajaamaan tapahtumien lukumäärää
{
    qDebug() << "MYSQLDLL showTransactions sain tiliID: " << idTili;
    QSqlTableModel *tilitapahtumat = new QSqlTableModel;
    tilitapahtumat->setTable("tilitapahtumat");
    tilitapahtumat->setFilter(QString("idTili='%1' ORDER BY tilitapahtumatAika DESC LIMIT %2").arg(idTili).arg(tapahtumiaKpl));
    tilitapahtumat->select();
    tilitapahtumat->removeColumns(0,2); //poistetaan ekat 2 saraketta..
    tilitapahtumat->setHeaderData(0, Qt::Horizontal, QObject::tr("Tapahtuma")); //nimetaan sarakkeet nayttoa varten.
    tilitapahtumat->setHeaderData(1, Qt::Horizontal, QObject::tr("Summa"));
    tilitapahtumat->setHeaderData(2, Qt::Horizontal, QObject::tr("Paivamaara"));

    return tilitapahtumat;
}

int DLLMySQL::invoiceCount(int idTili)
{
    //mika tili tulee ja haetaan asiakasid
    qDebug() << "MYSQLDLL nextInvoice sain tiliID: " << idTili;

    QSqlQuery invoice;
    invoice.prepare("select idLasku from laskut where maksettu=0 and idTili=:tili");
    invoice.bindValue(":tili", idTili);
    invoice.exec();
    int montako = invoice.size();

    qDebug() << "DLLMySQL nextInvoice laskuja oli: " << montako;

    return montako;
}

int DLLMySQL::getInvoiceId(int idTili)
{
    //mika tili tulee ja haetaan asiakasid
    qDebug() << "MYSQLDLL getInvoiceId sain tiliID: " << idTili;

    QSqlQuery invoiceID;
    invoiceID.prepare("select idLasku from laskut where maksettu=0 and idTili=:tili");
    invoiceID.bindValue(":tili", idTili);
    invoiceID.exec();
    invoiceID.next();
    int idee = invoiceID.value(0).toInt();

    qDebug() << "DLLMySQL getInvoiceId idee oli: " << idee;

    return idee;
}

void DLLMySQL::getInvoiceDetails(int lasku)
{
    //mika tili tulee ja haetaan asiakasid
    qDebug() << "MYSQLDLL getInvoiceDetails sain laskun ideen: " << lasku;

    QSqlQuery invoice;
    invoice.prepare("select tiliNumero,saaja,viite,summa from laskut where idLasku=:id order by idLasku");
    invoice.bindValue(":id", lasku);
    invoice.exec();
    invoice.first();

    QString tili = invoice.value(0).toString();
    QString saaja = invoice.value(1).toString();
    QString viite = invoice.value(2).toString();
    double summa = invoice.value(3).toDouble();

    emit sendTili(tili);
    emit sendSaaja(saaja);
    emit sendViite(viite);
    emit lahetaSumma(summa);

    qDebug() << "DLLMySQL getInvoiceDetails:" << tili << "," << saaja << "," << viite << "," << summa;
}

bool DLLMySQL::payInvoice(int lasku,int idTili, double summa)
{
    //mika lasku numero tulee
    qDebug() << "MYSQLDLL payInvoice laskuid:" << lasku << "idTili:" << idTili << "ja summan : " << summa;

    //ensin pitaa tarkistaa onko tililla katetta..
    QSqlQuery saldo;
    saldo.prepare("select tiliSaldo from tili where idTili=:tili");
    saldo.bindValue(":tili", idTili);
    saldo.exec();
    saldo.first();

    double saldosi = saldo.value(0).toDouble();
    qDebug() << "DLLMySQL raiseMoney saldo kannasta ennen paivitysta on: " << saldosi;

    if (saldosi >= summa)
    {
        qDebug() << "DLLMySQL payInvoice, tehdaan kanta updatet";
        QSqlQuery insert1;
        insert1.prepare("INSERT INTO tilitapahtumat (idTili,tilitapahtumatLaji,tilitapahtumatSumma,tilitapahtumatAika) "
                        "VALUES (:tili, 'lasku',:sum,now())");
        insert1.bindValue(":tili", idTili);
        insert1.bindValue(":sum", summa);
        insert1.exec();

        QSqlQuery update;
        update.prepare("update tili set tiliSaldo=tiliSaldo-:sum where idTili=:tili");
        update.bindValue(":tili", idTili);
        update.bindValue(":sum", summa);
        update.exec();

        QSqlQuery update2;
        update2.prepare("update laskut set maksettu=1 where idLasku=:id");
        update2.bindValue(":id", lasku);
        update2.exec();

        return true;

    }
        else
        {
           return false;
        }
}

void DLLMySQL::getDonateInfo(int id)
{
    //mika tili tulee ja haetaan asiakasid
    qDebug() << "MYSQLDLL getDonateInfo lahjoitus idee: " << id;

    QSqlQuery donate;
    donate.prepare("select tiliNumero,saaja,viite from lahjoituskohteet where idKohde=:id");
    donate.bindValue(":id", id);
    donate.exec();
    donate.first();

    QString tili = donate.value(0).toString();
    QString saaja = donate.value(1).toString();
    QString viite = donate.value(2).toString();

    emit sendTili(tili);
    emit sendSaaja(saaja);
    emit sendViite(viite);

    qDebug() << "DLLMySQL getDonateInfo arvot oli: " << tili << "," << saaja << "," << viite;
}

bool DLLMySQL::payDonation(int id,int idTili, int summa)
{
    //mika lasku numero tulee
    qDebug() << "MYSQLDLL payDonation id:" << id << "idTili:" << idTili << "summan : " << summa;

    //ensin pitaa tarkistaa onko tililla katetta..
    QSqlQuery saldo;
    saldo.prepare("select tiliSaldo from tili where idTili=:tili");
    saldo.bindValue(":tili", idTili);
    saldo.exec();
    saldo.first();

    double saldosi = saldo.value(0).toDouble();
    qDebug() << "DLLMySQL payDonation saldo kannasta ennen paivitysta on: " << saldosi;

    if (saldosi >= summa)
    {
        qDebug() << "DLLMySQL payInvoice, tehdaan kanta updatet";
        QSqlQuery insert1;
        insert1.prepare("INSERT INTO tilitapahtumat (idTili,tilitapahtumatLaji,tilitapahtumatSumma,tilitapahtumatAika) "
                        "VALUES (:tili, 'lahjoitus',:sum,now())");
        insert1.bindValue(":tili", idTili);
        insert1.bindValue(":sum", summa);
        insert1.exec();

        QSqlQuery update;
        update.prepare("update tili set tiliSaldo=tiliSaldo-:sum where idTili=:tili");
        update.bindValue(":tili", idTili);
        update.bindValue(":sum", summa);
        update.exec();

        return true;

    }
        else
        {
           return false;
        }

}
