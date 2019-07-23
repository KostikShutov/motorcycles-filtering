#include "edittor_item4.h"
#include "ui_edittor_item4.h"
#include "set_value/dimensional_setter.h"
#include "set_value/scalar_setter.h"
#include "set_value/logical_setter.h"
#include <QSqlQuery>
#include <QStandardItemModel>

Edittor_item4::Edittor_item4(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Edittor_item4)
{
    ui->setupUi(this);

    QSqlQuery query("SELECT * FROM classes");

    while (query.next())
    {
        QVariant v(query.value("id").toInt());
        ui->comboBox->addItem(query.value("name").toString(), v);
    }

    connect(ui->tableView, SIGNAL(clicked(const QModelIndex &)), this, SLOT(checker(const QModelIndex &)));

    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    if(ui->comboBox->count())
        on_comboBox_activated("");
}

Edittor_item4::~Edittor_item4()
{
    delete ui;
}

void Edittor_item4::checker(const QModelIndex &index)
{
    int row = index.row();
    int column = index.column();

    if(column != 2)
        return;

    QString type = ui->tableView->model()->index(row, 1).data().toString();
    QMap<int, QVariant> map = ui->tableView->model()->itemData(index);
    int id = map[257].toInt();
    QValueDialog *dialog;

    if(type == "Скалярный")
        dialog = new Scalar_setter(id);
    else if(type == "Размерный")
        dialog = new Dimensional_setter(id);
    else if(type == "Логический")
        dialog = new Logical_setter(id);

    dialog->setModal(true);

    if(dialog->exec())
    {
        on_comboBox_activated("");
    }

    delete dialog;
}

QString Edittor_item4::getTypeName(int type)
{
    switch(type)
    {
        case 1: return "Скалярный";
        case 2: return "Размерный";
        case 3: return "Логический";
    }

    return "Ошибка";
}

QString Edittor_item4::getTypeValues(int id, int type)
{
    switch(type)
    {
        case 1:
        {
            QString result = "";
            QSqlQuery query;
            query.prepare("SELECT name,active FROM values_scalar "
                          "LEFT JOIN signs_scalar ON signs_scalar.id = values_scalar.sign_id "
                          "WHERE class_descriptions_id = ?");
            query.addBindValue(id);
            query.exec();

            bool flag = true;
            while(query.next())
            {
                if(!query.value("active").toInt())
                    continue;
                QString name = query.value("name").toString();
                if(flag)
                {
                    result += name;
                    flag = false;
                }
                else
                    result += '\n' + name;
            }

            if(result == "")
                break;

            return result;
        }
        case 2:
        {
            QSqlQuery query;
            query.prepare("SELECT active,values_dimensional.interval_start,values_dimensional.interval_end,unit FROM values_dimensional "
                          "LEFT JOIN signs_dimensional ON signs_dimensional.id = values_dimensional.signs_id "
                          "WHERE class_descriptions_id = ?");
            query.addBindValue(id);
            query.exec();

            if(query.next())
            {
                if(!query.value("active").toInt())
                    break;
                QString interval_start = query.value("interval_start").toString();
                QString interval_end = query.value("interval_end").toString();
                QString unit = query.value("unit").toString();

                return '[' + interval_start + "; " +interval_end + "] " + unit;
            }
            break;
        }
        case 3:
        {
            QSqlQuery query;
            query.prepare("SELECT yes,no,name_yes,name_no FROM values_logical "
                          "LEFT JOIN signs_logical ON signs_logical.id = values_logical.signs_id "
                          "WHERE class_descriptions_id = ?");
            query.addBindValue(id);
            query.exec();

            if(query.next())
            {
                int yes = query.value("yes").toInt();
                int no = query.value("no").toInt();
                QString name_yes = query.value("name_yes").toString();
                QString name_no = query.value("name_no").toString();

                if(yes && no)
                    return name_yes + '\n' + name_no;
                if(yes)
                    return name_yes;
                if(no)
                    return name_no;
            }
            break;
        }
    }

    return "Ввести значение";
}

void Edittor_item4::on_pushButton_clicked()
{
    this->close();
}

void Edittor_item4::on_comboBox_activated(const QString &arg1)
{
    delete ui->tableView->model();
    int class_id = ui->comboBox->currentData().value<int>();
    QStandardItem *item;
    QStandardItemModel *model = new QStandardItemModel;

    QStringList horizontalHeader;
    horizontalHeader << "Признак" << "Тип" << "Значение";
    model->setHorizontalHeaderLabels(horizontalHeader);

    QSqlQuery query;
    query.prepare("SELECT class_descriptions.id,name,type FROM class_descriptions "
                  "LEFT JOIN signs ON class_descriptions.sign_id = signs.id WHERE class_id = ?");
    query.addBindValue(class_id);
    query.exec();

    int i = 0;
    while (query.next())
    {
        item = new QStandardItem(query.value("name").toString());
        model->setItem(i, 0, item);

        int type = query.value("type").toInt();
        item = new QStandardItem(getTypeName(type));
        item->setData(type);
        model->setItem(i, 1, item);

        int id = query.value("id").toInt();
        item = new QStandardItem(getTypeValues(id, type));
        item->setData(id);
        model->setItem(i, 2, item);

        i++;
    }

    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->verticalHeader()->hide();
    ui->tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->tableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
}
