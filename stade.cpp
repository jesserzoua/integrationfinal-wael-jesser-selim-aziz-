#include "stade.h"
#include <QString>
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>

Stade::Stade()
{
  nom = " "; type = " ";
  id = 0; capacite = 0;
}
Stade::Stade(QString nom,QString type,int id,int capacite)
{
 this->id=id; this->type=type; this->capacite=capacite; this->nom=nom;
}
int Stade::getid(){return id;}
int Stade::getcapacite(){return capacite;}
QString Stade::getnom(){return nom;}
QString Stade::gettype(){return type;}
void Stade::setid(int id){this->id=id;}
void Stade::setcapacite(int capacite){this->capacite=capacite;}
void Stade::setnom(QString nom){this->nom=nom;}
void Stade::settype(QString type){this->type=type;}

bool Stade::ajouter()
{
    QSqlQuery query;
QString id_string= QString::number(id);
         query.prepare("INSERT INTO STADE (NOM, ID, CAPACITE, TYPE) "
                       "VALUES (:nom, :id, :capacite, :type)");
         query.bindValue(":nom", nom);
         query.bindValue(":id",id);
         query.bindValue(":capacite", capacite);
         query.bindValue(":type", type);
         return query.exec();


}
bool Stade::supprimer(int id)
{
    QSqlQuery query;
QString id_string= QString::number(id);
         query.prepare(" Delete from STADE where id =:id");
         query.bindValue(0, id);

         return query.exec();

}
QSqlQueryModel* Stade::afficher()
{
   QSqlQueryModel* model=new QSqlQueryModel();
         model->setQuery("SELECT* FROM STADE");
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("id"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("capacite"));
         model->setHeaderData(3, Qt::Horizontal, QObject::tr("type"));
         return model;
}


bool Stade :: modifier(int id)
{
     QSqlQuery query;



        QString res= QString::number(id);
        query.prepare("UPDATE Stade SET nom=:nom,id=:id,capacite=:capacite ,type=:type WHERE id=:id");
        query.bindValue(":nom", nom);
        query.bindValue(":capacite", capacite);
        query.bindValue(":id", id);
        query.bindValue(":type", type);



           return    query.exec();

}

QSqlQueryModel * Stade::Find_Stade()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT NOM, ID, CAPACITE, TYPE FROM STADE");

    query.exec();
    model->setQuery(query);
    return model;
}

QSqlQueryModel * Stade::recherche_stade(QString search)
{

    QSqlQueryModel * model= new QSqlQueryModel();
    QString qry="select * from STADE where nom like '%"+search+"%' or id like '%"+search+"%' or capacite like '%"+search+"%' or type like '%"+search+"%' ";
    qDebug()<<qry;
    model->setQuery(qry);
    return model;
}

QSqlQueryModel * Stade::triID()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM STADE ORDER BY id");
    return model;

}
QSqlQueryModel * Stade::triNOM()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM STADE ORDER BY nom");
    return model;

}

QSqlQueryModel * Stade::tricapacite()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM STADE ORDER BY capacite");
    return model;

}

void Stade::stat(QCustomPlot *customPlot)
{
    QSqlQuery query,query1;
    // set dark background gradient:
    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0, QColor(90, 90, 90));
    gradient.setColorAt(0.38, QColor(105, 105, 105));
    gradient.setColorAt(1, QColor(70, 70, 70));
    customPlot->clearPlottables();
    customPlot->clearGraphs();
    customPlot->replot();

    customPlot->setBackground(QBrush(gradient));


    QCPBars *fossil = new QCPBars(customPlot->xAxis, customPlot->yAxis);

    fossil->setAntialiased(false);

    fossil->setStackingGap(1);
    // set names and colors:
    fossil->setName("statistique des capacites");
    fossil->setPen(QPen(QColor(111, 9, 176).lighter(170)));
    fossil->setBrush(QColor(111, 9, 176));

    QVector<double> ticks;
    QVector<QString> labels;
    query.prepare("SELECT COUNT(DISTINCT id) FROM STADE where capacite between 0 and 10");
    query.exec();
    int un;
    while(query.next())
    {
        un=query.value(0).toInt();
        qDebug()<<un;
    }
    query.prepare("SELECT COUNT(DISTINCT id) FROM STADE where capacite between 10 and 100");
    query.exec();
    int deux;
    while(query.next())
    {
        deux=query.value(0).toInt();
    }

    query.prepare("SELECT COUNT(DISTINCT id) FROM STADE where capacite between 100 and 8000");
    query.exec();
    int trois;
    while(query.next())
    {
        trois=query.value(0).toInt();
    }





    ticks << 1 << 2 << 3 ;
    labels << "[0,10]" << "[11,100]" << "[101,8000]" ;
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    customPlot->xAxis->setTicker(textTicker);
    customPlot->xAxis->setTickLabelRotation(60);
    customPlot->xAxis->setSubTicks(false);
    customPlot->xAxis->setTickLength(0, 4);
    customPlot->xAxis->setRange(0, 8);
    customPlot->xAxis->setBasePen(QPen(Qt::white));
    customPlot->xAxis->setTickPen(QPen(Qt::white));
    customPlot->xAxis->grid()->setVisible(true);
    customPlot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    customPlot->xAxis->setTickLabelColor(Qt::white);
    customPlot->xAxis->setLabelColor(Qt::green);

    // prepare y axis:
    customPlot->yAxis->setRange(0, 20);
    customPlot->yAxis->setPadding(5); // a bit more space to the left border
    customPlot->yAxis->setLabel("Nombre de STADE");
    customPlot->yAxis->setBasePen(QPen(Qt::white));
    customPlot->yAxis->setTickPen(QPen(Qt::white));
    customPlot->yAxis->setSubTickPen(QPen(Qt::white));
    customPlot->yAxis->grid()->setSubGridVisible(true);
    customPlot->yAxis->setTickLabelColor(Qt::white);
    customPlot->yAxis->setLabelColor(Qt::white);
    customPlot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    customPlot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

    // Add data:
    QVector<double> fossilData, nuclearData, regenData;
    fossilData  << un << deux << trois;
   // nuclearData << 0.08*10.5 << 0.12*5.5 << 0.12*5.5 << 0.40*5.8 << 0.09*5.2 << 0.00*4.2 << 0.07*11.2;
    regenData   << 0.06*10.5 << 0.05*5.5 << 0.04*5.5 << 0.06*5.8 << 0.02*5.2 << 0.07*4.2 << 0.25*11.2;
    fossil->setData(ticks, fossilData);
  //  nuclear->setData(ticks, nuclearData);
 //   regen->setData(ticks, regenData);

    // setup legend:
    customPlot->legend->setVisible(true);
    customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    customPlot->legend->setBrush(QColor(255, 255, 255, 100));
    customPlot->legend->setBorderPen(Qt::NoPen);
    QFont legendFont = QFont();
    legendFont.setPointSize(10);
    customPlot->legend->setFont(legendFont);
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

}
