#include "statistique.h"
#include "ui_statistique.h"

statistique::statistique(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::statistique)
{
    ui->setupUi(this);
    makePlot();
}

statistique::~statistique()
{
    delete ui;
}
void statistique::makePlot()
{    QSqlQuery qry;

     int t11=0;
       int t21=0;
         int t31=0;


   qry.prepare("select * from gestion_participant where pays = 'Tunisie' ");
     if (qry.exec())
     {
         while (qry.next())
         {
            t11++;


       }
     }
     qry.prepare("select * from gestion_participant where pays = 'USA'  ");
       if (qry.exec())
       {
           while (qry.next())
           {
              t21++;


         }
       }
       qry.prepare("select * from gestion_participant where pays = 'Canada'  ");
         if (qry.exec())
         {
             while (qry.next())
             {
                t31++;


           }
         }


    // set dark background gradient:
    QLinearGradient gradient(0, 0, 0, 300);
    gradient.setColorAt(0, QColor(5, 100, 100));
    gradient.setColorAt(0.38, QColor(10, 150, 170));
    gradient.setColorAt(1, QColor(20, 20, 20));
    ui->customPlot->setBackground(QBrush(gradient));

    QCPBars *m1 = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
    QCPBars *m2 = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
     QCPBars *m3 = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
     m2->setAntialiased(false);
    m1->setAntialiased(false);
     m3->setAntialiased(false);
     m2->setStackingGap(1);
    m1->setStackingGap(1);
     m3->setStackingGap(1);
    // set names and colors:
    m1->setName("Tunisie");
    m1->setPen(QPen(QColor(40,100,10).lighter(170)));
    m1->setBrush(QColor(40,100,10));

    m2->setName("Usa");
    m2->setPen(QPen(QColor(244,180,26).lighter(150)));
    m2->setBrush(QColor(244,180,26));
     m3->setName("Canada");
      m3->setPen(QPen(QColor(20,61,89).lighter(170)));
       m3->setBrush(QColor(20,61,89));

    // stack bars on top of each other:
    m1->moveAbove(m2);
     m2->moveAbove(m3);



    // prepare x axis with country labels:
    QVector<double> ticks;
    QVector<QString> labels;
    ticks << 1 << 2 << 3   ;
    labels << "TUNISIE" << "USA" << "CANADA"   ;
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    ui->customPlot->xAxis->setTicker(textTicker);
    ui->customPlot->xAxis->setTickLabelRotation(60);
    ui->customPlot->xAxis->setSubTicks(false);
    ui->customPlot->xAxis->setTickLength(0, 4);
    ui->customPlot->xAxis->setRange(0, 8);
    ui->customPlot->xAxis->setBasePen(QPen(Qt::white));
    ui->customPlot->xAxis->setTickPen(QPen(Qt::white));
    ui->customPlot->xAxis->grid()->setVisible(true);
    ui->customPlot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    ui->customPlot->xAxis->setTickLabelColor(Qt::white);
    ui->customPlot->xAxis->setLabelColor(Qt::white);

    // prepare y axis:
    ui->customPlot->yAxis->setRange(0, 5);
    ui->customPlot->yAxis->setPadding(30); // a bit more space to the left border
    ui->customPlot->yAxis->setLabel("NOMBRE DE PARTICIPANTS");
    ui->customPlot->yAxis->setBasePen(QPen(Qt::white));
    ui->customPlot->yAxis->setTickPen(QPen(Qt::white));
    ui->customPlot->yAxis->setSubTickPen(QPen(Qt::white));
    ui->customPlot->yAxis->grid()->setSubGridVisible(true);
    ui->customPlot->yAxis->setTickLabelColor(Qt::white);
    ui->customPlot->yAxis->setLabelColor(Qt::white);
    ui->customPlot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    ui->customPlot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

    // Add data:
     int t0 = 0;
    QVector<double> m1data ;
    m1data  << t11 << t0    ;
    m1->setData(ticks, m1data);

     QVector<double> m2data ;
      m2data  << t0 << t21 << t0   ;
       m2->setData(ticks, m2data);

        QVector<double> m3data ;
         m3data  << t0 << t0 << t31  ;
          m3->setData(ticks, m3data);


    // setup legend:
    ui->customPlot->legend->setVisible(true);
    ui->customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    ui->customPlot->legend->setBrush(QColor(255, 255, 255, 100));
    ui->customPlot->legend->setBorderPen(Qt::NoPen);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    ui->customPlot->legend->setFont(legendFont);
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}
