#include "connection.h"
#include <QSqlDatabase>

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("test.bd");
db.setUserName("jasser");//inserer nom de l'utilisateur
db.setPassword("jasser");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}

