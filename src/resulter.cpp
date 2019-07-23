#include "resulter.h"
#include "ui_resulter.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>

Resulter::Resulter(QList<int> ides,
                   QList<int> types,
                   QList<QVariant> values,
                   QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Resulter)
{
    ui->setupUi(this);

    //Возможные классы
    ui->tableWidget->setColumnCount(1);
    QStringList horizontalHeader;
    horizontalHeader << "Классы";
    ui->tableWidget->setHorizontalHeaderLabels(horizontalHeader);

    QSet<int> result, tmp;
    int size = types.size();
    for(int i = 0; i < size; i++)
    {
        tmp = getSetById(ides[i], types[i], values[i]);

        if(i == 0)
            result = tmp;
        else
            result = result.intersect(tmp);

        tmp.clear();
    }

    size = result.size();
    ui->tableWidget->setRowCount(!size ? 1 : size);

    if(result.empty())
    {
        ui->tableWidget->setItem(0, 0, new QTableWidgetItem("Нет таких классов"));
    }
    else
    {
        int id, i = 0;
        QString result_string;
        foreach(id, result)
        {
            QSqlQuery query;
            query.prepare("SELECT name FROM classes WHERE id = ?");
            query.addBindValue(id);
            query.exec();
            query.next();
            ui->tableWidget->setItem(i, 0, new QTableWidgetItem(query.value("name").toString()));
            i++;
        }
    }

    ui->tableWidget->verticalHeader()->hide();
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //Неподходящие классы
    ui->tableWidget_2->setColumnCount(2);
    horizontalHeader.clear();
    horizontalHeader << "Классы" << "Причина";
    ui->tableWidget_2->setHorizontalHeaderLabels(horizontalHeader);

    ui->tableWidget_2->setRowCount(2);

    //Заполнение
    ui->tableWidget_2->setItem(0, 0, new QTableWidgetItem("Трицикл"));
    ui->tableWidget_2->setItem(0, 1, new QTableWidgetItem("Класс \"Трицикл\" не подходит, \
так как значения признака \"Доп багажные отсеки\" не соответствуют\
значениям этого признака для этого класса"));
    ui->tableWidget_2->setItem(1, 0, new QTableWidgetItem("Спорт_турист"));
    ui->tableWidget_2->setItem(1, 1, new QTableWidgetItem("Класс \"Спорт_турист\" не подходит, \
так как значения признака \"Доп багажные отсеки\" не соответствуют\
значениям этого признака для этого класса"));

    ui->tableWidget_2->verticalHeader()->hide();
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->tableWidget_2->verticalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableWidget_2->verticalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

Resulter::~Resulter()
{
    delete ui;
}

QSet<int> Resulter::getSetById(const int id, const int type, const QVariant value)
{
    QSqlQuery query;
    QSet<int> tmp;

    if(type == 1)
    {
        query.prepare("SELECT class_id FROM "
                      "(SELECT * FROM values_scalar "
                      "LEFT JOIN signs_scalar ON values_scalar.sign_id = signs_scalar.id WHERE active = 1 AND name = ?) AS A "
                      "LEFT JOIN class_descriptions ON A.class_descriptions_id = class_descriptions.id WHERE class_descriptions.sign_id = ?");
        query.addBindValue(value.toString());
        query.addBindValue(id);
        query.exec();

        while(query.next())
            tmp.insert(query.value("class_id").toInt());
    }
    else if(type == 2)
    {
        query.prepare("SELECT class_id FROM "
                      "(SELECT * FROM values_dimensional "
                      "LEFT JOIN signs_dimensional ON values_dimensional.signs_id = signs_dimensional.id WHERE active = 1 "
                      "AND values_dimensional.interval_start <= :val AND values_dimensional.interval_end >= :val) AS A "
                      "LEFT JOIN class_descriptions ON A.class_descriptions_id = class_descriptions.id WHERE class_descriptions.sign_id = :id");
        query.bindValue(":val", value.toInt());
        query.bindValue(":id", id);
        query.exec();

        while(query.next())
            tmp.insert(query.value("class_id").toInt());
    }
    else if(type == 3)
    {
        query.prepare("SELECT yes,no,name_yes,name_no,class_id FROM "
                      "(SELECT * FROM values_logical "
                      "LEFT JOIN signs_logical ON values_logical.signs_id = signs_logical.id WHERE yes = 1 OR no = 1) AS A "
                      "LEFT JOIN class_descriptions ON A.class_descriptions_id = class_descriptions.id WHERE class_descriptions.sign_id = ?");
        query.addBindValue(id);
        query.exec();

        while(query.next())
        {
            if((query.value("yes").toInt() && query.value("name_yes").toString() == value.toString())
                    || (query.value("no").toInt() && query.value("name_no").toString() == value.toString()))
                tmp.insert(query.value("class_id").toInt());
        }
    }

    return tmp;
}

void Resulter::on_pushButton_clicked()
{
    this->close();
}
