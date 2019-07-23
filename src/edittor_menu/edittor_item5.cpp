#include "edittor_item5.h"
#include "ui_edittor_item5.h"
#include <QStandardItemModel>
#include <QSqlQuery>

Edittor_item5::Edittor_item5(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Edittor_item5)
{
    ui->setupUi(this);

    int i = 0;
    QStringList horizontalHeader;
    QStandardItem *item;

    //tableView
    QStandardItemModel *model = new QStandardItemModel;

    horizontalHeader << "Класс" << "Результат проверки";
    model->setHorizontalHeaderLabels(horizontalHeader);

    QSqlQuery query("SELECT * FROM classes");
    int isValid;

    while (query.next())
    {
        item = new QStandardItem(query.value("name").toString());
        model->setItem(i, 0, item);

        isValid = isClassValid(query.value("id").toInt());

        QString text;
        QString pic;

        if(isValid == -1)
        {
            text = "Признаки отсутствуют";
            pic = ":/img/ques.png";
        }
        else if(isValid == 0)
        {
            text = "Заполнен не полностью";
            pic = ":/img/no.png";
        }
        else if(isValid == 1)
        {
            text = "Проверка пройдена";
            pic = ":/img/yes.png";
        }

        item = new QStandardItem(text);
        model->setItem(i, 1, item);
        QPixmap icon(pic);
        QModelIndex index = model->index(i, 1);
        model->setData(index, icon, Qt::DecorationRole);

        i++;
    }

    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->verticalHeader()->hide();
    ui->tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //tableView_2
    model = new QStandardItemModel;

    horizontalHeader.clear();
    horizontalHeader << "Признак" << "Результат проверки";
    model->setHorizontalHeaderLabels(horizontalHeader);

    query.exec("SELECT name, type FROM signs");

    i = 0;
    while (query.next())
    {
        item = new QStandardItem(query.value("name").toString());
        model->setItem(i, 0, item);

        isValid = query.value("type").toInt();
        item = new QStandardItem(isValid ? QString("Проверка пройдена") : QString("Значения отсутствуют"));
        model->setItem(i, 1, item);
        QPixmap icon(isValid ? QString(":/img/yes.png") : QString(":/img/no.png"));
        QModelIndex index = model->index(i, 1);
        model->setData(index, icon, Qt::DecorationRole);

        i++;
    }

    ui->tableView_2->setModel(model);
    ui->tableView_2->resizeColumnsToContents();
    ui->tableView_2->verticalHeader()->hide();
    ui->tableView_2->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableView_2->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->tableView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

Edittor_item5::~Edittor_item5()
{
    delete ui;
}
#include <QDebug>
int Edittor_item5::isClassValid(const int id)
{
    QSqlQuery query;
    query.prepare(""
        "SELECT active FROM class_descriptions "
        "LEFT JOIN values_dimensional ON values_dimensional.class_descriptions_id = class_descriptions.id "
        "WHERE class_id = :id AND active IS NOT NULL "
        "UNION "
        "SELECT (yes + no) AS active FROM class_descriptions "
        "LEFT JOIN values_logical ON values_logical.class_descriptions_id = class_descriptions.id "
        "WHERE class_id = :id AND active IS NOT NULL "
        "UNION "     
        "SELECT SUM(active) AS active FROM class_descriptions "
        "LEFT JOIN values_scalar ON values_scalar.class_descriptions_id = class_descriptions.id "
        "WHERE class_id = :id AND class_descriptions_id IS NOT NULL "
        "GROUP BY class_descriptions_id");
    query.bindValue(":id", id);
    query.exec();

    int initialPos = query.at();
    query.last();
    int count = query.at() + 1;
    query.seek(initialPos);

    qDebug() << count;
    if(count <= 0)
        return -1;

    while(query.next())
    {
        if(!query.value("active").toInt())
            return 0;
    }

    return 1;
}

void Edittor_item5::on_pushButton_clicked()
{
    this->close();
}
