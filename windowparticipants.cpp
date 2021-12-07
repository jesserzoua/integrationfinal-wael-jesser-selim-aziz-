#include "windowparticipants.h"
#include "ui_windowparticipants.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QIntValidator>
#include <QtDebug>
#include<QObject>
#include <QSqlQueryModel>
#include <QRegExpValidator>
#include<QSystemTrayIcon>
#include<QCheckBox>
#include <QPdfWriter>
#include <QPainter>
#include <QUrl>
#include <QDesktopServices>
#include "window.h"
windowparticipants::windowparticipants(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::windowparticipants)
{
    ui->setupUi(this);
    ui->tab_participant->setModel(G.afficher());
    ui->le_id->setValidator( new QIntValidator(0, 9999, this));
    ui->combo_id_p->setModel(G.afficherId());
    ui->combo_modifier_id->setModel(G.afficherId());

}

windowparticipants::~windowparticipants()
{
    delete ui;
}

void windowparticipants::on_pushbotton_ajouter_clicked()
{
    if(ui->combo_Pays->currentIndex()==0){

        QMessageBox::critical(nullptr, QObject::tr("Ajout"),
             QObject::tr("Choisir Pays!!.\n"
                         "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else{
    int ID=ui->le_id->text().toInt();
    QString NOM=ui->le_nom->text();
    QString PAYS=ui->combo_Pays->currentText();
    int CIN=ui->le_cin->text().toInt();
    GESTION_PARTICIPANT G(NOM,ID,PAYS,CIN);
    bool test=G.ajouter();

    if(test)
      {          ui->tab_participant->setModel(G.afficher())    ;
                 ui->combo_id_p->setModel(G.afficherId());
                 ui->combo_modifier_id->setModel(G.afficherId());


          QMessageBox::information(nullptr, QObject::tr("Ok"),
               QObject::tr("Ajout effectué.\n"
                           "Click Cancel to exit."), QMessageBox::Cancel);


      }
      else
      {
          QMessageBox::critical(nullptr, QObject::tr("Not Ok"),
               QObject::tr("Ajout non effectué ID deja existe.\n"
                           "Click Cancel to exit."), QMessageBox::Cancel);} }
}

void windowparticipants::on_pushButton_clicked()

    {



    int ID=ui->combo_modifier_id->currentText().toInt()  ;
       bool test =G.supprimer(ID)    ;
       if(test)
       {
           ui->tab_participant->setModel(G.afficher())    ;
           ui->combo_id_p->setModel(G.afficherId());
           ui->combo_modifier_id->setModel(G.afficherId());

           QMessageBox::information(nullptr, QObject::tr("Ok"),
                QObject::tr("Suppression effectué.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
      ui->tab_participant->setModel(G.afficher())    ;
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



void windowparticipants::on_pushButton_2_clicked()
{
    if(ui->pays_modifier->currentIndex()==0){

        QMessageBox::critical(nullptr, QObject::tr("Ajout"),
             QObject::tr("Choisir Pays!!.\n"
                         "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else{
    QString NOM=ui->lineEdit_2->text();
    int ID=ui->lineEdit_3->text().toInt();
    QString PAYS=ui->pays_modifier->currentText();
    int CIN=ui->lineEdit_5->text().toInt();
    GESTION_PARTICIPANT G(NOM,ID,PAYS,CIN);


    bool test=G.modifier(NOM,ID,PAYS,CIN);
    if(test)
    {

        ui->tab_participant->setModel(G.afficher());

               QMessageBox::information(nullptr, QObject::tr("effectué"),
                    QObject::tr(" Modifié.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
               ui->lineEdit_2->clear();
               ui->lineEdit_3->clear();
               //ui->lineEdit_4->clear();
                ui->lineEdit_5->clear();

   }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("non effectué"),
                    QObject::tr("non modifié !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        //ui->lineEdit_4->clear();
         ui->lineEdit_5->clear();


 }
    ui->tab_participant->setModel(G.afficher());
}

}

void windowparticipants::on_pushButton_3_clicked()
{
    if (ui->checkBox->isChecked())
          {
              ui->tab_participant->setModel(G.trier("ID"));
              QSystemTrayIcon * notifyIcon = new QSystemTrayIcon;
                          notifyIcon-> show ();
                          notifyIcon-> showMessage ( " GESTION_PARTICIPANT " , " ID Trié " , QSystemTrayIcon :: Information, 15000 );

          }
}

void windowparticipants::on_pushButton_4_clicked()

    {

            int ID=ui->le_nom_2->text().toInt();
               ui->tab_participant->setModel(G.rechercher(ID));
        }




void windowparticipants::on_btn_Pdf_clicked()
{
    QString name = "Participant"+ui->combo_id_p->currentText()+".pdf";
    QPdfWriter pdf("C:/Users/jasse/Desktop/PDF/"+name);

                      QPainter painter(&pdf);
                     int i = 4000;
                          painter.setPen(Qt::blue);
                          painter.setFont(QFont("Arial", 30));
                          painter.drawText(2300,1200,"Participant #"+ui->combo_id_p->currentText());
                          painter.setPen(Qt::black);
                          painter.setFont(QFont("Arial", 50));
                          painter.drawRect(1500,200,7300,2600);
                          painter.drawRect(0,3000,9600,500);
                          painter.setFont(QFont("Arial", 9));
                          painter.drawText(300,3300,"ID");
                          painter.drawText(2300,3300,"CIN");
                          painter.drawText(4300,3300,"NOM");
                          painter.drawText(6300,3300,"PAYS");



                          QSqlQuery query;
                          query.prepare("select ID , cin , nom , pays from gestion_participant where id = :id");
                          query.bindValue(":id",ui->combo_id_p->currentText().toInt());
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
                                  QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/jasse/Desktop/PDF/"+name));

                                  painter.end();
                              }
                              if (reponse == QMessageBox::No)
                              {
                                   painter.end();
                              }
}



void windowparticipants::on_imprimerListP_clicked()
{
    QPdfWriter pdf("C:/Users/jasse/Desktop/PDF/ListParticipants.pdf");

                      QPainter painter(&pdf);
                     int i = 4000;
                          painter.setPen(Qt::blue);
                          painter.setFont(QFont("Arial", 30));
                          painter.drawText(2300,1200,"List des Participant ");
                          painter.setPen(Qt::black);
                          painter.setFont(QFont("Arial", 50));
                          painter.drawRect(1500,200,7300,2600);
                          painter.drawRect(0,3000,9600,500);
                          painter.setFont(QFont("Arial", 9));
                          painter.drawText(300,3300,"ID");
                          painter.drawText(2300,3300,"CIN");
                          painter.drawText(4300,3300,"NOM");
                          painter.drawText(6300,3300,"PAYS");



                          QSqlQuery query;
                          query.prepare("select ID , cin , nom , pays from gestion_participant");

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
                                  QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/jasse/Desktop/PDF/ListParticipants.pdf"));

                                  painter.end();
                              }
                              if (reponse == QMessageBox::No)
                              {
                                   painter.end();
                              }
}



void windowparticipants::on_btn_Stat_p_clicked()
{
    statistique *g =new statistique();
    g->exec();
}

void windowparticipants::on_pushButton_5_clicked()
{
    this->hide();
    Window *menu = new Window();
    menu->show();

}
