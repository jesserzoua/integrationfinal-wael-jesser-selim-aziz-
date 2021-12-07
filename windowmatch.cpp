#include "windowmatch.h"
#include "ui_windowmatch.h"
#include "match.h"
#include <QMessageBox>
#include <iostream>

#include <QMessageBox>

#include  <QDebug>

#include <QRadioButton>

#include<QtPrintSupport/QPrinter>

#include<QPdfWriter>

#include <QPainter>

#include<QFileDialog>

#include<QTextDocument>

#include <QTextEdit>

#include <QtSql/QSqlQueryModel>

#include<QtPrintSupport/QPrinter>

#include <QVector2D>

#include <QVector>

#include <QSqlQuery>

#include<QDesktopServices>

#include <QMessageBox>

#include<QUrl>

#include <QPixmap>

#include <QTabWidget>

#include <QValidator>

#include <QPrintDialog>

#include<QtSql/QSqlQuery>

#include<QVariant>

#include<QMediaPlayer>
#include<QSystemTrayIcon>

WindowMatch::WindowMatch(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WindowMatch)
{
    ui->setupUi(this);
    ui->tableView->setModel(tmpmatchs.afficher());

}

WindowMatch::~WindowMatch()
{
    delete ui;
}


void WindowMatch::on_ajouter_clicked()
{
    int id = ui->lineEdit_id->text().toInt();
        int idstade= ui->lineEdit_idstade->text().toInt();
        QString dates= ui->lineEdit_date->text();
        QString sport= ui->lineEdit_sport->text();
        int nbrp= ui->lineEdit_nbrp->text().toInt();


    Match m(id,idstade,dates,sport,nbrp);
    bool test=m.ajouter();


    if(test)
    {
        ui->tableView->setModel(tmpmatchs.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                   QObject::tr("ajout effectue\n"
                               "click cancel te exit."), QMessageBox::Cancel);
    }
    else

        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                   QObject::tr("ajout non effectue\n"
                               "click cancel te exit."), QMessageBox::Cancel);

}

void WindowMatch::on_supprimer_clicked()
{
    QString id = ui->lineEdit_ids->text();
       bool test=tmpmatchs.supprimer(id);
       if(test)
       {



           ui->tableView->setModel(tmpmatchs.afficher());//refresh
           QMessageBox::information(nullptr, QObject::tr("Supprimer un match"),
                       QObject::tr("match supprimé.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);

       }
       else
           QMessageBox::critical(nullptr, QObject::tr("Supprimer un match"),
                       QObject::tr("Erreur !.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);

}

void WindowMatch::on_recherche_clicked()
{
    QMediaPlayer * bulletsound = new QMediaPlayer();
    bulletsound->setMedia(QUrl::fromLocalFile("C:/Users/User/Downloads/nc.mp3"));

       if (bulletsound->state() == QMediaPlayer::PlayingState){
            bulletsound->setPosition(0);
        }
        else if (bulletsound->state() == QMediaPlayer::StoppedState){
            bulletsound->play();
        }
        QString rech =ui->lineEdit_rech->text();
       ui->tableView->setModel(tmpmatchs.rechercher(rech));
}

void WindowMatch::on_pdf_clicked()
{
    QString strStream;
                     QTextStream out(&strStream);

                     const int rowCount = ui->tableView->model()->rowCount();
                     const int columnCount = ui->tableView->model()->columnCount();

                     out <<  "<html>\n"
                         "<head>\n"
                         "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                         <<  QString("<title>%1</title>\n").arg("strTitle")
                         <<  "</head>\n"
                         "<body bgcolor=#ffffff link=#5000A0>\n"

                        //     "<align='right'> " << datefich << "</align>"
                         "<center> <H1>Liste des commandes </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

                     // headers
                     out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
                     for (int column = 0; column < columnCount; column++)
                         if (!ui->tableView->isColumnHidden(column))
                             out << QString("<th>%1</th>").arg(ui->tableView->model()->headerData(column, Qt::Horizontal).toString());
                     out << "</tr></thead>\n";

                     // data table
                     for (int row = 0; row < rowCount; row++) {
                         out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                         for (int column = 0; column < columnCount; column++) {
                             if (!ui->tableView->isColumnHidden(column)) {
                                 QString data = ui->tableView->model()->data(ui->tableView->model()->index(row, column)).toString().simplified();
                                 out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                             }
                         }
                         out << "</tr>\n";
                     }
                     out <<  "</table> </center>\n"
                         "</body>\n"
                         "</html>\n";

               QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en PDF", QString(), "*.pdf");
                 if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

                QPrinter printer (QPrinter::PrinterResolution);
                 printer.setOutputFormat(QPrinter::PdfFormat);
                printer.setPaperSize(QPrinter::A4);
               printer.setOutputFileName(fileName);

                QTextDocument doc;
                 doc.setHtml(strStream);
                 doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
                 doc.print(&printer);

}

void WindowMatch::on_imprimer_clicked()
{
    QPrinter printer;

        printer.setPrinterName("desiered printer name");

      QPrintDialog dialog(&printer,this);

        if(dialog.exec()== QDialog::Rejected)

            return;
}

void WindowMatch::on_triID_clicked()
{
     ui->tableView->setModel(tmpmatchs.triID());
}

void WindowMatch::on_triIDSTADE_clicked()
{
    ui->tableView->setModel(tmpmatchs.triIDSTADE());

}

void WindowMatch::on_sms_clicked()
{
    QNetworkAccessManager * manager = new QNetworkAccessManager(this);

    QUrl url("https://AC1562be4d86f0ae4888b59fac36a8a511:248ff73cdfbfc354aff54ab40182702c@api.twilio.com/2010-04-01/Accounts/AC1562be4d86f0ae4888b59fac36a8a511/Messages.json");
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");


    QUrlQuery params;
    params.addQueryItem("From", "+18449841195");
    params.addQueryItem("To",ui->lineEdit->text() );//"+21690101450"
    params.addQueryItem("Body", ui->textEdit->toPlainText());
   // params.addQueryItem("Body", "test");

    // etc

    connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(replyFinished(QNetworkReply*)));

    manager->post(request, params.query().toUtf8());

}

void WindowMatch::on_modifier_clicked()
{
    int id = ui->lineEdit_idm->text().toInt();
        int idstade = ui->lineEdit_idstadem->text().toInt();
        QString date= ui->lineEdit_datem->text();
        QString sport= ui->lineEdit_sportm->text();

        int nbrp = ui->lineEdit_nbrpm->text().toInt();


        Match m;
        bool test=m.modifier(id,idstade,date,sport,nbrp);

        if(test)
        {




            QMessageBox::information(nullptr, QObject::tr("modifie un match"),
                              QObject::tr("match modifiée.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
            ui->tableView->setModel(tmpmatchs.afficher());
        }
        else
            QMessageBox::critical(nullptr, QObject::tr("non modifie"),
                        QObject::tr("Erreur !.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
            ui->tableView->setModel(tmpmatchs.afficher());
}
