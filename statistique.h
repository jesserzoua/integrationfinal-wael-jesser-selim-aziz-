#ifndef STATISTIQUE_H
#define STATISTIQUE_H

#include <QDialog>
#include"qcustomplot.h"
#include<QSqlQuery>
#include<QSqlQueryModel>

namespace Ui {
class statistique;
}

class statistique : public QDialog
{
    Q_OBJECT

public:
    explicit statistique(QWidget *parent = nullptr);
    ~statistique();
    void makePlot();


private:
    Ui::statistique *ui;
};

#endif // STATISTIQUE_H
