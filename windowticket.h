#ifndef WINDOWTICKET_H
#define WINDOWTICKET_H

#include <QDialog>
#include "gestion_tickets.h"
#include "chat.h"
#include "statmans.h"
namespace Ui {
class windowticket;
}

class windowticket : public QMainWindow
{
    Q_OBJECT

public:
    explicit windowticket(QWidget *parent = nullptr);
    ~windowticket();
private slots:
    //void on_pb_ajouter_clicked();

    void on_pushbotton_ajouter_clicked();


    void on_pushButton_clicked();

    void on_dateEdit_userDateChanged(const QDate &date);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

//    void on_le_nombre_6_editingFinished();

    void on_pushButton_5_clicked();



    void on_chat_btn_t_clicked();

    void on_pdf_btn_t_clicked();

    void on_pushButton_6_clicked();



    void on_pushButton_7_clicked();

private:
    Ui::windowticket *ui;
    Gestion_tickets G;
    ChatMainWindow *s;
    statmans *ss ;
};

#endif // WINDOWTICKETS_H
