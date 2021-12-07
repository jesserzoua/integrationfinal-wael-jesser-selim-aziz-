#ifndef STADE_H
#define STADE_H
#include <QString>
#include <QSqlQueryModel>
#include "qcustomplot.h"

class Stade
{
public:
    Stade();
    Stade(QString,QString,int,int);
    int getid();
    int getcapacite();
    QString getnom();
    QString gettype();
    void setid(int);
    void setcapacite(int);
    void setnom(QString);
    void settype(QString);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifier(int id);
    QSqlQueryModel* Find_Stade();
    QSqlQueryModel* recherche_stade(QString search);
    QSqlQueryModel* triID();
     QSqlQueryModel* triNOM();
      QSqlQueryModel* tricapacite();
      void stat(QCustomPlot *customPlot);
private:
    QString nom,type;
    int id;
    int capacite;

};

#endif // STADE_H
