#include "gestion_tickets.h"
#include<QObject>
#include<QDate>
#include<QtPrintSupport/QPrinter>
#include<QFileDialog>
#include <QSqlQuery>
#include <QtDebug>
#include<QString>
#include <QSqlQueryModel>
#include<QTextDocument>
Gestion_tickets::Gestion_tickets()
{
 ID=0 ; ID_EVENT=0; DATES_DES_TICKETS=QDate() ;TYPE="";PRIX=0;

}
Gestion_tickets::Gestion_tickets(int ID ,int ID_EVENT, QDate DATES_DES_TICKETS,QString TYPE,int PRIX)
{this->ID=ID; this->ID_EVENT=ID_EVENT;this->DATES_DES_TICKETS=DATES_DES_TICKETS;this->TYPE=TYPE;this->PRIX=PRIX;}
int Gestion_tickets:: getID(){return ID;}
int Gestion_tickets:: getID_EVENT(){return ID_EVENT ;}
QDate Gestion_tickets:: getDATES_DES_TICKETS() {return DATES_DES_TICKETS;}
QString Gestion_tickets::getTYPE(){return TYPE;}
int Gestion_tickets::getPRIX(){return PRIX;}
void Gestion_tickets:: setID(int ID){this->ID=ID;}
void Gestion_tickets:: setID_EVENT(int ID_EVENT ){this->ID_EVENT=ID_EVENT;}
void Gestion_tickets:: setDATES_DES_TICKETS(QDate DATES_DES_TICKETS){this->DATES_DES_TICKETS=DATES_DES_TICKETS;}
void Gestion_tickets:: setTYPE(QString TYPE){this->TYPE=TYPE;}
void Gestion_tickets:: setPRIX(int PRIX){this->PRIX=PRIX;}
bool Gestion_tickets:: ajouter()

{

   QSqlQuery query;
   QString ID_string= QString::number(ID);

   query.prepare("INSERT INTO Gestion_tickets (ID,ID_EVENT ,DATES_DES_TICKETS,TYPE,PRIX ) "
                 "VALUES (:ID, :ID_EVENT, :DATES_DES_TICKETS,:TYPE, :PRIX)");


   query.bindValue(":ID", ID );
   query.bindValue(":ID_EVENT", ID_EVENT );
   query.bindValue(":DATES_DES_TICKETS",DATES_DES_TICKETS);
 query.bindValue(":TYPE",TYPE);
  query.bindValue(":PRIX",PRIX);

   return query.exec();
}

QSqlQueryModel *Gestion_tickets  :: afficher()
{
    QSqlQueryModel *  model = new QSqlQueryModel ()    ;
        model->setQuery("SELECT * FROM Gestion_tickets");
        model->setHeaderData(0, Qt::Horizontal, QObject :: tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject :: tr("ID_EVENT"));
        model->setHeaderData(2, Qt::Horizontal, QObject :: tr("DATES_DES_TICKETS"));
        model->setHeaderData(3, Qt::Horizontal, QObject :: tr("TYPE"));
        model->setHeaderData(4, Qt::Horizontal, QObject :: tr("PRIX"));
return model ;
}
QSqlQueryModel *Gestion_tickets  ::afficherId()
{
    QSqlQueryModel *  model = new QSqlQueryModel ()    ;
    model->setQuery("SELECT id FROM Gestion_tickets");
    return model ;
}

bool Gestion_tickets :: supprimer(int ID)
{
    QSqlQuery query;

    query.prepare("Delete from Gestion_tickets where ID=:ID ") ;
    query.bindValue(":ID",ID);
    return query.exec() ;
}

bool Gestion_tickets :: modifier(int ID ,int ID_EVENT, QDate DATES_DES_TICKETS,QString TYPE,int PRIX)
{
     QSqlQuery query;
        query.prepare("UPDATE Gestion_tickets SET ID=:ID,ID_EVENT=:ID_EVENT,DATES_DES_TICKETS=:DATES_DES_TICKETS,TYPE=:TYPE,PRIX=:PRIX WHERE ID=:ID");
        query.bindValue(":ID", ID );
        query.bindValue(":ID_EVENT", ID_EVENT );
        query.bindValue(":DATES_DES_TICKETS",DATES_DES_TICKETS);
      query.bindValue(":TYPE",TYPE);
       query.bindValue(":PRIX",PRIX);
        return    query.exec();

}
QSqlQueryModel* Gestion_tickets::trier(QString crit)
{
    QSqlQuery *query=new QSqlQuery();
    QSqlQueryModel *model=new QSqlQueryModel();
    query->prepare("select * from Gestion_tickets order by "+crit+"");
    query->exec();
    model->setQuery(*query);
    return model;
}
QSqlQueryModel *Gestion_tickets ::rechercher(int ID)   //OK
{

    QSqlQueryModel *model=new QSqlQueryModel();
    QSqlQuery query;

    query.prepare("Select * from Gestion_tickets where ID=:ID");
    query.bindValue(":ID",ID);
    query.exec();
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    return model;}
