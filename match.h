#ifndef MATCH_H
#define MATCH_H
#include <QString>

#include <QSqlQuery>
#include <QSqlQueryModel>
#include<QDate>

class Match
{public:
    Match(){};
   Match(int,int,QString,QString,int);
    int get_id();
    int get_idstade();
    QString get_dates();
    QString get_sport();
    int get_nbrp();
    void setid(int);
    void setidstade(int);
    void setdates(QString);
    void setsport(QString);
    void setnbrp(int);


    bool ajouter();
    QSqlQueryModel * afficher();
     bool supprimer(QString);
     bool modifier(int,int,QString,QString,int);

    QSqlQueryModel * rechercher(QString);
        QSqlQueryModel * triID();
        QSqlQueryModel * triIDSTADE();


private:
        int id,idstade,nbrp;
    QString dates,sport;


};


#endif // MATCH_H
