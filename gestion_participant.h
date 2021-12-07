#ifndef GESTION_PARTICIPANT_H
#define GESTION_PARTICIPANT_H
#include<QString>
#include<QSqlQueryModel>
#include<QSqlQuery>



class GESTION_PARTICIPANT
{
public:

    GESTION_PARTICIPANT();
    GESTION_PARTICIPANT(QString,int,QString,int);
    int getID();
    int getCIN();
    QString getNOM();
    QString getPAYS();
    void setCIN(int);
    void setID(int);
    void setNOM(QString);
    void setPAYS(QString);
    bool ajouter();
    QSqlQueryModel *afficher();
    QSqlQueryModel *afficherId();
    bool supprimer(int);
    bool modifier(QString,int,QString,int);
    QSqlQueryModel* trier(QString ) ;
    QSqlQueryModel *rechercher(int ID);





private:
    int ID,CIN;
    QString NOM,PAYS;
};

#endif // GESTION_PARTICIPANT_H
