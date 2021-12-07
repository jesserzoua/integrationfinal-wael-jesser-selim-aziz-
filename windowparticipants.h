#ifndef WINDOWPARTICIPANTS_H
#define WINDOWPARTICIPANTS_H

#include <QDialog>
#include "gestion_participant.h"
#include "statistique.h"
namespace Ui {
class windowparticipants;
}

class windowparticipants : public QDialog
{
    Q_OBJECT

public:
    explicit windowparticipants(QWidget *parent = nullptr);
    ~windowparticipants();

private slots:
    //void on_pb_ajouter_clicked();

    void on_pushbotton_ajouter_clicked();


    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();



    void on_btn_Pdf_clicked();



    void on_imprimerListP_clicked();



    void on_btn_Stat_p_clicked();

    void on_pushButton_5_clicked();

private:
      Ui::windowparticipants *ui;
    GESTION_PARTICIPANT G;
    statistique *q;
private:

};

#endif // WINDOWPARTICIPANTS_H
