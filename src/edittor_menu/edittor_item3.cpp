#include "edittor_item3.h"
#include "ui_edittor_item3.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

Edittor_item3::Edittor_item3(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Edittor_item3)
{
    ui->setupUi(this);

    QSqlQuery query("SELECT * FROM classes");

    while (query.next())
    {
        QVariant v(query.value("id").toInt());
        ui->comboBox->addItem(query.value("name").toString(), v);
    }

    if(ui->comboBox->count())
        on_comboBox_activated("");
}

Edittor_item3::~Edittor_item3()
{
    delete ui;
}

void Edittor_item3::addTypeValue(const int c_d_id, const int s_id_old, const int type)
{
    QSqlQuery query;
    int s_id;

    switch(type)
    {
        case 1:
        {
            query.prepare("SELECT id FROM signs_scalar WHERE sign_id = ?");
            query.addBindValue(s_id_old);
            query.exec();
            QSqlQuery inserter;

            while(query.next())
            {
                s_id = query.value("id").toInt();
                inserter.prepare("INSERT INTO values_scalar (class_descriptions_id, sign_id) VALUES (?, ?)");
                inserter.addBindValue(c_d_id);
                inserter.addBindValue(s_id);
                inserter.exec();
            }
            break;
        }
        case 2:
        {
            query.prepare("SELECT id,interval_start,interval_end FROM signs_dimensional WHERE sign_id = ?");
            query.addBindValue(s_id_old);
            query.exec();
            query.next();
            s_id = query.value("id").toInt();
            int interval_start = query.value("interval_start").toInt();
            int interval_end = query.value("interval_end").toInt();
            query.prepare("INSERT INTO values_dimensional (class_descriptions_id, signs_id, interval_start, interval_end) "
                          "VALUES (?, ?, ?, ?)");
            query.addBindValue(c_d_id);
            query.addBindValue(s_id);
            query.addBindValue(interval_start);
            query.addBindValue(interval_end);
            query.exec();
            break;
        }
        case 3:
        {
            query.prepare("SELECT id FROM signs_logical WHERE sign_id = ?");
            query.addBindValue(s_id_old);
            query.exec();
            query.next();
            s_id = query.value("id").toInt();
            query.prepare("INSERT INTO values_logical (class_descriptions_id, signs_id) VALUES (?, ?)");
            query.addBindValue(c_d_id);
            query.addBindValue(s_id);
            query.exec();
            break;
        }
    }
}

void Edittor_item3::on_pushButton_clicked()
{
    // >
    QList<QListWidgetItem*> items = ui->listWidget->selectedItems();
    foreach(QListWidgetItem *item, items)
    {
        int sign_id = item->data(Qt::UserRole).value<int>();
        QString name = item->text();

        auto *item_new = new QListWidgetItem(name);
        QVariant v;
        v.setValue(sign_id);
        item_new->setData(Qt::UserRole, v);
        ui->listWidget_2->addItem(item_new);

        int class_id = ui->comboBox->currentData().toInt();
        QSqlQuery query;
        query.prepare("INSERT INTO class_descriptions (class_id, sign_id) VALUES (?, ?)");
        query.addBindValue(class_id);
        query.addBindValue(sign_id);
        query.exec();
        query.prepare("SELECT type, (SELECT id FROM class_descriptions WHERE sign_id = :sign_id AND class_id = :class_id) "
                      "AS class_descriptions_id FROM signs WHERE id = :sign_id");
        query.bindValue(":sign_id", sign_id);
        query.bindValue(":class_id", class_id);
        query.exec();
        query.next();

        addTypeValue(query.value("class_descriptions_id").toInt(),
                     sign_id,
                     query.value("type").toInt());

        delete ui->listWidget->takeItem(ui->listWidget->row(item));
    }
}

void Edittor_item3::on_pushButton_2_clicked()
{
    // <
    QList<QListWidgetItem*> items = ui->listWidget_2->selectedItems();
    foreach(QListWidgetItem *item, items)
    {
        int sign_id = item->data(Qt::UserRole).value<int>();
        QString name = item->text();

        auto *item_new = new QListWidgetItem(name);
        QVariant v;
        v.setValue(sign_id);
        item_new->setData(Qt::UserRole, v);
        ui->listWidget->addItem(item_new);

        QSqlQuery query;
        query.prepare("DELETE FROM class_descriptions WHERE class_id = ? AND sign_id = ?");
        query.addBindValue(ui->comboBox->currentData().toInt());
        query.addBindValue(sign_id);
        query.exec();

        delete ui->listWidget_2->takeItem(ui->listWidget_2->row(item));
    }
}

void Edittor_item3::on_pushButton_3_clicked()
{
    //Закрыть
    this->close();
}

void Edittor_item3::on_comboBox_activated(const QString &arg1)
{
    //Переключатель comboBox
    int class_id = ui->comboBox->currentData().value<int>();
    QString query_string =
        "SELECT sign_id AS id, name, type FROM class_descriptions "
        "LEFT JOIN signs ON class_descriptions.sign_id = signs.id WHERE class_id = ?";
    QSqlQuery query;
    query.prepare(query_string);
    query.addBindValue(class_id);
    query.exec();

    ui->listWidget_2->clear();
    while (query.next())
    {
        auto *item = new QListWidgetItem(query.value("name").toString());
        QVariant v;
        v.setValue(query.value("id").toInt());
        item->setData(Qt::UserRole, v);
        ui->listWidget_2->addItem(item);
    }

    query.prepare("SELECT * FROM signs WHERE type != 0 EXCEPT " + query_string);
    query.addBindValue(class_id);
    query.exec();

    ui->listWidget->clear();
    while (query.next())
    {
        auto *item = new QListWidgetItem(query.value("name").toString());
        QVariant v;
        v.setValue(query.value("id").toInt());
        item->setData(Qt::UserRole, v);
        ui->listWidget->addItem(item);
    }
}
