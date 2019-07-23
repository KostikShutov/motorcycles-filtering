#include "src/mainwindow.h"
#include <QApplication>
#include <QtSql/QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("motorcycles.db");

    if(!db.open())
    {
        QMessageBox::warning(nullptr, "Предупреждение", "Нет подключения к базе данных");
        return 0;
    }

    QSqlQuery query("PRAGMA foreign_keys = ON");

    MainWindow window;
    window.show();

    return app.exec();
}
