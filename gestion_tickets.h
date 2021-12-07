#ifndef GESTION_TICKETS_H
#define GESTION_TICKETS_H
#include<QSqlQueryModel>
#include<QSqlQuery>
#include<QDate>
#include<QString>


class Gestion_tickets
{
public:
    Gestion_tickets();
    Gestion_tickets(int,int,QDate,QString,int);
    int getID();
    int getID_EVENT();
    QDate getDATES_DES_TICKETS();
    QString getTYPE();
    int getPRIX();
    void setID(int);
    void setID_EVENT(int);
    void setDATES_DES_TICKETS(QDate);
    void setTYPE(QString);
    void setPRIX(int);
    bool ajouter();
    QSqlQueryModel *afficher();
    QSqlQueryModel *afficherId();
    bool supprimer(int);
    bool modifier(int,int,QDate,QString,int )    ;
    QSqlQueryModel* trier(QString crit) ;
  QSqlQueryModel *rechercher(int ID);
private:
    int ID ,ID_EVENT,PRIX ;
    QString TYPE;
QDate DATES_DES_TICKETS;



};

#endif // GESTION_TICKETS_H



