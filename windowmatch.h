#ifndef WINDOWMATCH_H
#define WINDOWMATCH_H

#include <QMainWindow>
#include "match.h"

#include <QMainWindow>
#include <QMessageBox>

#include<QComboBox>

#include <iostream>

#include<QDate>

#include <QNetworkAccessManager>

#include <QUrlQuery>

#include <QNetworkReply>

#include <QJsonValue>

#include <QJsonValueRef>

#include <QJsonDocument>

#include <QJsonObject>

#include <QJsonArray>

#include <QString>

#include <QDebug>

#include <QtCore>

#include <QtGui>

#include <QDialog>

#include <QModelIndex>

#include <QGridLayout>

#include <QApplication>

#include <QIntValidator>

#include <QDateTime>

#include <QMediaPlayer>

#include <QRadioButton>

namespace Ui {
class WindowMatch;
}

class WindowMatch : public QMainWindow
{
    Q_OBJECT

public:
    explicit WindowMatch(QWidget *parent = nullptr);
    ~WindowMatch();

private slots:
    void on_ajouter_clicked();

    void on_supprimer_clicked();

    void on_recherche_clicked();

    void on_pdf_clicked();

    void on_imprimer_clicked();

    void on_triID_clicked();

    void on_triIDSTADE_clicked();

    void on_sms_clicked();

    void on_modifier_clicked();

private:
    Ui::WindowMatch *ui;
    Match tmpmatchs;

};

#endif // WINDOWMATCH_H
