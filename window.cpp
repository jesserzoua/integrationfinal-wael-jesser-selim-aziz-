#include "window.h"
#include "ui_window.h"

Window::Window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Window)
{
    ui->setupUi(this);
}

Window::~Window()
{
    delete ui;
}


void Window::on_stade_clicked()
{
    stade = new  MainWindow(this);
    stade ->show();
}


void Window::on_match_clicked()
{
    match = new  WindowMatch(this);
    match ->show();
}


void Window::on_participant_clicked()
{
   windowparticipants p ;
   this->hide();
   p.exec();
}

void Window::on_tickets_clicked()
{
    ticket = new  windowticket(this);
    ticket ->show();
}
