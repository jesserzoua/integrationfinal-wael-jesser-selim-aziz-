#ifndef STATMANS_H
#define STATMANS_H

#include <QDialog>

#include"qcustomplot.h"

#include<QSqlQuery>
#include<QSqlQueryModel>
namespace Ui {
class statmans;
}

class statmans : public QDialog
{
    Q_OBJECT

public:
    explicit statmans(QWidget *parent = nullptr);
    ~statmans();
    void makePlot();

private:
    Ui::statmans *ui;
};

#endif // STATMANS_H
