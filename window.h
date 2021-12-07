#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include "mainwindow.h"
#include "windowmatch.h"
#include "windowparticipants.h"
#include "windowticket.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Window; }
QT_END_NAMESPACE

class Window : public QMainWindow
{
    Q_OBJECT

public:
    Window(QWidget *parent = nullptr);
    ~Window();

private slots:
    void on_stade_clicked();

    void on_match_clicked();
    
    void on_participant_clicked();

    void on_tickets_clicked();

private:
    Ui::Window *ui;
    MainWindow *stade;
    WindowMatch *match;
    windowticket *ticket;
};
#endif // WINDOW_H


