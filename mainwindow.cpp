#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stade.h"
#include <QApplication>
#include <QMessageBox>
#include <QTableView>
#include <qmessagebox.h>
#include <QIntValidator>
#include <QSqlQuery>
#include <QScrollBar>
#include <qfiledialog.h>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QTextDocument>
#include <QTextStream>
#include <QDate>
#include <QComboBox>
#include <arduino_bouton.h>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_id ->setValidator(new QIntValidator(0, 9999999, this));
    ui->tab_Stade->setModel(S1.afficher());

    int ret=A.connect_arduino(); // lancer la connexion à arduino
        switch(ret){
        case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
            break;
        case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
           break;
        case(-1):qDebug() << "arduino is not available";
        }
         QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
         //le slot update_label suite à la reception du signal readyRead (reception des données).
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_label()
{
    data=A.read_from_arduino();

    if(data=="1")

        ui->lineEdit->setText("moteur  activé"); // si les données reçues de arduino via la liaison série sont égales à 1
    // alors afficher ON

    else if (data=="0")

        ui->lineEdit->setText("moteur désactivée");   // si les données reçues de arduino via la liaison série sont égales à 0
     //alors afficher OF
}



void MainWindow::on_Button_Ajouter_clicked()
{
    QString nom =ui->le_nom->text();
    QString type =ui->le_type->text();
    int id =ui->le_id->text().toInt();
    int capacite =ui->la_capacite->text().toInt();
    Stade S(nom,type,id,capacite);
    bool test=S.ajouter();


    if(test)
    {
        ui->tab_Stade->setModel(S1.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                   QObject::tr("ajout effectue\n"
                               "click cancel te exit."), QMessageBox::Cancel);
    }
    else

        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                   QObject::tr("ajout non effectue\n"
                               "click cancel te exit."), QMessageBox::Cancel);

}

void MainWindow::on_ButtonSupprimer_clicked()
{
    Stade S2; S2.setid(ui->le_id_sup->text().toInt());
    bool test=S2.supprimer(S2.getid());
    QMessageBox msgBox;

    if(test)
    {
        ui->tab_Stade->setModel(S1.afficher());
        msgBox.setText("suppression avec succes");
    }
    else
    msgBox.setText("echec de suppression");
    msgBox.exec();

}

void MainWindow::on_Button_Modification_clicked()
{
    int id = ui->le_id_2->text().toInt();
    QString type= ui->le_type_2->text();
     QString nom= ui->le_nom_2->text();
     int capacite = ui->la_capacite_2->text().toInt();

    Stade c(nom,type,id,capacite);
    bool test=c.modifier(id);
    if(test)
    {

        ui->tab_Stade->setModel(c.afficher());//refresh

               QMessageBox::information(nullptr, QObject::tr("effectué"),
                    QObject::tr(" Modifié.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
               ui->le_id_2->clear();
               ui->le_type_2->clear();
               ui->le_nom_2->clear();
               ui->la_capacite_2->clear();
   }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("non effectué"),
                    QObject::tr("non modifié !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        ui->le_id_2->clear();
        ui->le_type_2->clear();
        ui->le_nom_2->clear();
        ui->la_capacite_2->clear();



    }

}



/*void MainWindow::on_le_id_cursorPositionChanged(int arg1, int arg2)
{

}

void MainWindow::on_label_linkActivated(const QString &link)
{

}*/

void MainWindow::on_Excel_clicked()
{
    Stade S;
           QSqlQueryModel * model=new QSqlQueryModel();
           model=S.Find_Stade();
           QString textData= "nom             id                    capacite      type \n";
           int rows=model->rowCount();
           int columns=model->columnCount();
           for (int i = 0; i < rows; i++)
           {
               for (int j = 0; j < columns; j++)
               {
                   textData += model->data(model->index(i,j)).toString();
                   textData +=" ; ";
               }
               textData += "\n";
           }
           QString fileName = QFileDialog::getSaveFileName(this, "Export Excel", QString(), "*.csv");
           if (!fileName.isEmpty())
               if (QFileInfo(fileName).suffix().isEmpty())
                   fileName.append(".csv");
           QFile csvfile(fileName);
           if(csvfile.open(QIODevice::WriteOnly|QIODevice::Truncate))
           {
               QTextStream out(&csvfile);
               out<<textData;
           }
           csvfile.close();
}

void MainWindow::on_Imprimer_clicked()
{
    QString strStream;
                QTextStream out(&strStream);

                const int rowCount = ui->tab_Stade->model()->rowCount();
                const int columnCount = ui->tab_Stade->model()->columnCount();
                QString TT = QDate::currentDate().toString("yyyy/MM/dd");
                out <<"<html>\n"
                      "<head>\n"
                       "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                    << "<title> LISTE DES STADES<title>\n "
                    << "</head>\n"
                    "<body bgcolor=#ffffff link=#5000A0>\n"
                    "<h1 style=\"text-align: center;\"><strong> ***LISTE DES STADES *** "+TT+"</strong></h1>"
                    "<table style=\"text-align: center; font-size: 20px;\" border=1>\n "
                      "</br> </br>";
                // headers
                out << "<thead><tr bgcolor=#d6e5ff>";
                for (int column = 0; column < columnCount; column++)
                    if (!ui->tab_Stade->isColumnHidden(column))
                        out << QString("<th>%1</th>").arg(ui->tab_Stade->model()->headerData(column, Qt::Horizontal).toString());
                out << "</tr></thead>\n";

                // data table
                for (int row = 0; row < rowCount; row++) {
                    out << "<tr>";
                    for (int column = 0; column < columnCount; column++) {
                        if (!ui->tab_Stade->isColumnHidden(column)) {
                            QString data =ui->tab_Stade->model()->data(ui->tab_Stade->model()->index(row, column)).toString().simplified();
                            out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                        }
                    }
                    out << "</tr>\n";
                }
                out <<  "</table>\n"
                    "</body>\n"
                    "</html>\n";

                QTextDocument *document = new QTextDocument();
                document->setHtml(strStream);

                QPrinter printer;

                QPrintDialog *test = new QPrintDialog(&printer, NULL);
                if (test->exec() == QDialog::Accepted) {
                    document->print(&printer);
                }

                delete document;
}

void MainWindow::on_Rechercher_textChanged(const QString &arg1)
{
        Stade S;
        ui->tab_Stade->setModel(S.recherche_stade(ui->Rechercher->text()));

}

void MainWindow::on_TriID_clicked()
{

        ui->tab_Stade->setModel(S1.triID());


}


void MainWindow::on_TriNom_clicked()

    {
        ui->tab_Stade->setModel(S1.triNOM());
    }


void MainWindow::on_tricapacite_clicked()
{
    ui->tab_Stade->setModel(S1.tricapacite());

}

void MainWindow::on_Stat_clicked()
{
    ui->STADE->setCurrentIndex(3);
    Stade S;


    S.stat(ui->widget);
}

void MainWindow::on_toit_man_clicked()
{
     A.write_to_arduino("0");
}
