#include "windowticket.h"
#include "ui_windowticket.h"
#include "gestion_tickets.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QIntValidator>
#include <QtDebug>
#include<QObject>
#include <QSqlQueryModel>
#include <QRegExpValidator>
#include<QCheckBox>
#include<QSystemTrayIcon>
#include <QPdfWriter>
#include <QPainter>
#include <QDesktopServices>
#include <QUrl>
#include <statmans.h>
#include "window.h"
windowticket::windowticket(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::windowticket)
{
    ui->setupUi(this);
    ui->tab_tickets->setModel(G.afficher());
    ui->le_id->setValidator( new QIntValidator(0, 9999, this));
    ui->supprimer_ticket_combo->setModel(G.afficherId());
}

windowticket::~windowticket()
{
    delete ui;
}


void windowticket::on_pushbotton_ajouter_clicked()
{

}


void windowticket::on_pushButton_clicked()
{
    if(ui->t_type_ajout->currentIndex()==0){
        QMessageBox::critical(nullptr, QObject::tr("Not Ok"),
             QObject::tr("Choisir Type.\n"
                         "Click Cancel to exit."), QMessageBox::Cancel);
    }
else{
    int ID=ui->le_id->text().toInt();
    int ID_EVENT =ui->le_nombre->text().toInt();
    QDate DATES_DES_TICKETS=ui->dateEdit->date();
    QString TYPE=ui->t_type_ajout->currentText();
    int PRIX=ui->le_nombre_3->text().toInt();
    Gestion_tickets G(ID,ID_EVENT,DATES_DES_TICKETS,TYPE,PRIX);
    bool test=G.ajouter();

    if(test)
      {          ui->tab_tickets->setModel(G.afficher())    ;
                ui->supprimer_ticket_combo->setModel(G.afficherId());
          QMessageBox::information(nullptr, QObject::tr("Ok"),
               QObject::tr("Ajout effectué.\n"
                           "Click Cancel to exit."), QMessageBox::Cancel);


      }
      else
      {
          QMessageBox::critical(nullptr, QObject::tr("Not Ok"),
               QObject::tr("Ajout non effectué.\n"
                           "Click Cancel to exit."), QMessageBox::Cancel);}}
}

void windowticket::on_dateEdit_userDateChanged(const QDate &date)
{

}

void windowticket::on_pushButton_2_clicked()


    {

       // Client C1;
      // C1.set_id(ui->Id_supp->text().toInt())    ;

    int ID=ui->supprimer_ticket_combo->currentText().toInt()  ;
       bool test =G.supprimer(ID)    ;
       if(test)
       {
           ui->tab_tickets->setModel(G.afficher())    ;
           ui->supprimer_ticket_combo->setModel(G.afficherId());
           QMessageBox::information(nullptr, QObject::tr("Ok"),
                QObject::tr("Suppression effectué.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
      ui->tab_tickets->setModel(G.afficher())    ;
       }
       else
       {
           QMessageBox::information(nullptr, QObject::tr("Not Ok"),
                QObject::tr("Suppression non effectué.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);


       }
       // }
       // else
       // {
       //     QMessageBox::warning(this, "Echec", "identifiant non existant !");


       // }

    }

void windowticket::on_pushButton_3_clicked()
{
    if (ui->t_type_modifier->currentIndex()==0){
        QMessageBox::critical(nullptr, QObject::tr("non effectué"),
                    QObject::tr("Choisir Type !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else{
    int ID=ui->lineEdit_2->text().toInt();
    int  ID_EVENT=ui->lineEdit_3->text().toInt();
    QDate DATES_DES_TICKETS=ui->dateEdit_2->date();
    QString TYPE=ui->t_type_modifier->currentText();
    int PRIX=ui->le_nombre_4->text().toInt();
    Gestion_tickets G(ID,ID_EVENT,DATES_DES_TICKETS,TYPE,PRIX);


    bool test=G.modifier(ID,ID_EVENT,DATES_DES_TICKETS,TYPE,PRIX);
    if(test)
    {

        ui->tab_tickets->setModel(G.afficher());//refresh
        ui->supprimer_ticket_combo->setModel(G.afficherId());
               QMessageBox::information(nullptr, QObject::tr("effectué"),
                    QObject::tr(" Modifié.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
               ui->lineEdit_2->clear();
               ui->lineEdit_3->clear();
               ui->dateEdit_2->clear();

               ui->le_nombre_4->clear();
   }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("non effectué"),
                    QObject::tr("non modifié !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        ui->dateEdit_2->clear();

        ui->le_nombre_4->clear();

 }
    ui->tab_tickets->setModel(G.afficher());//refresh

}
}

void windowticket::on_pushButton_4_clicked()

{
        if (ui->checkBox->isChecked())
        {
            ui->tab_tickets->setModel(G.trier("PRIX"));
            QSystemTrayIcon * notifyIcon = new QSystemTrayIcon;
                        notifyIcon-> show ();
                        notifyIcon-> showMessage ( " GESTION TICKET" , " PRIX Trié " , QSystemTrayIcon :: Information, 15000 );

        }
    }


void windowticket::on_pushButton_5_clicked()
{
    {

        int ID=ui->le_nombre_6->text().toInt();
           ui->tab_tickets->setModel(G.rechercher(ID));
    }
}

void windowticket::on_chat_btn_t_clicked()
{
    ChatMainWindow *s = new ChatMainWindow;
    s->show();
}

void windowticket::on_pdf_btn_t_clicked()
{

    QPdfWriter pdf("C:/Users/wael-/Desktop/Tickets/PdfTicket.pdf");

                      QPainter painter(&pdf);
                     int i = 4000;
                          painter.setPen(Qt::blue);
                          painter.setFont(QFont("Arial", 30));
                          painter.drawText(2300,1200,"Liste Des Tickets");
                          painter.setPen(Qt::black);
                          painter.setFont(QFont("Arial", 50));

                          painter.drawRect(1500,200,7300,2600);

                          painter.drawRect(0,3000,9600,500);
                          painter.setFont(QFont("Arial", 9));
                          painter.drawText(300,3300,"ID");
                          painter.drawText(2300,3300,"EVENT");
                          painter.drawText(4300,3300,"TYPE");
                          painter.drawText(6300,3300,"PRIX");



                          QSqlQuery query;
                          query.prepare("select id,id_event,type,prix from gestion_tickets");
                          query.exec();
                          while (query.next())
                          {
                              painter.drawText(300,i,query.value(0).toString());
                              painter.drawText(2300,i,query.value(1).toString());
                              painter.drawText(4300,i,query.value(2).toString());
                              painter.drawText(6300,i,query.value(3).toString());



                             i = i +500;
                          }
                          int reponse = QMessageBox::question(this, "Génerer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);
                              if (reponse == QMessageBox::Yes)
                              {
                                  QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/wael-/Desktop/Tickets/PdfTicket.pdf"));

                                  painter.end();
                              }
                              if (reponse == QMessageBox::No)
                              {
                                   painter.end();
                              }
}

void windowticket::on_pushButton_6_clicked()
{
  statmans *hh = new statmans();
  hh->exec();
}

void windowticket::on_pushButton_7_clicked()
{
    this->hide();
    Window *menu = new Window();
    menu->show();
}
