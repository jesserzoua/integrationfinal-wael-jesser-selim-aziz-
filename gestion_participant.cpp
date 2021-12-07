#include "gestion_participant.h"
#include <QSqlQuery>
#include <QtDebug>
#include<QString>
#include <QSqlQueryModel>
#include<QObject>
#include<QFileDialog>
#include<QTextDocument>

GESTION_PARTICIPANT::GESTION_PARTICIPANT()
{
ID=0; NOM=" ";PAYS=" ";CIN=0;
}
GESTION_PARTICIPANT::GESTION_PARTICIPANT(QString NOM,int ID,QString PAYS,int CIN)
{this->ID=ID; this->NOM=NOM; this->PAYS=PAYS; this->CIN=CIN; }
int GESTION_PARTICIPANT:: getID(){return ID;}
QString GESTION_PARTICIPANT:: getNOM(){return NOM;}
QString GESTION_PARTICIPANT:: getPAYS(){return PAYS;};
int GESTION_PARTICIPANT:: getCIN(){return CIN;}
void GESTION_PARTICIPANT::setID(int ID){this->ID=ID;}
void GESTION_PARTICIPANT:: setNOM(QString NOM){this->NOM=NOM;}
void GESTION_PARTICIPANT::setPAYS(QString PAYS){this->PAYS=PAYS;
                                                   }
void GESTION_PARTICIPANT::setCIN(int CIN){this->CIN=CIN;}
bool GESTION_PARTICIPANT::ajouter()
{

   QSqlQuery query;
   QString ID_string= QString::number(ID);

   query.prepare("INSERT INTO GESTION_PARTICIPANT (NOM,ID , PAYS,CIN) "
                 "VALUES (:NOM, :ID, :PAYS, :CIN)");

   query.bindValue(":NOM", NOM );
   query.bindValue(":ID", ID );
   query.bindValue(":PAYS", PAYS);
   query.bindValue(":CIN", CIN );



   return query.exec();
}

QSqlQueryModel * GESTION_PARTICIPANT :: afficher()
{
    QSqlQueryModel *  model = new QSqlQueryModel ()    ;
        model->setQuery("SELECT * FROM GESTION_PARTICIPANT");
        model->setHeaderData(0, Qt::Horizontal, QObject :: tr("NOM"));
        model->setHeaderData(1, Qt::Horizontal, QObject :: tr("ID"));
        model->setHeaderData(2, Qt::Horizontal, QObject :: tr("PAYS"));
         model->setHeaderData(3, Qt::Horizontal, QObject :: tr("CIN"));

return model ;
}
bool GESTION_PARTICIPANT :: supprimer(int ID)
{
    QSqlQuery query;

    query.prepare("Delete from GESTION_PARTICIPANT where ID=:ID ") ;
    query.bindValue(":ID",ID);
    return query.exec() ;


}
bool GESTION_PARTICIPANT:: modifier (QString NOM,int ID,QString PAYS,int CIN)
{
     QSqlQuery query;
        query.prepare("UPDATE GESTION_PARTICIPANT SET ID=:ID,NOM=:NOM,PAYS=:PAYS,CIN=:CIN WHERE ID=:ID");
        query.bindValue(":NOM", NOM );
        query.bindValue(":ID", ID );
        query.bindValue(":PAYS",PAYS);
        query.bindValue(":CIN", CIN );
        return    query.exec();

}

QSqlQueryModel* GESTION_PARTICIPANT::trier(QString crit)
{
    QSqlQuery *query=new QSqlQuery();
    QSqlQueryModel *model=new QSqlQueryModel();
    query->prepare("select * from GESTION_PARTICIPANT order by "+crit+"");
    query->exec();
    model->setQuery(*query);
    return model;
}
QSqlQueryModel *GESTION_PARTICIPANT ::rechercher(int ID)   //OK
{

    QSqlQueryModel *model=new QSqlQueryModel();
    QSqlQuery query;

    query.prepare("Select * from GESTION_PARTICIPANT where ID=:ID");
    query.bindValue(":ID",ID);
    query.exec();
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("NOM"));
    return model;
}
QSqlQueryModel *GESTION_PARTICIPANT::afficherId(){
    QSqlQueryModel *  model = new QSqlQueryModel ()    ;
        model->setQuery("SELECT id FROM GESTION_PARTICIPANT");
     return model ;

}

