#include "scalar_setter.h"
#include "ui_scalar_setter.h"
#include <QListWidgetItem>
#include <QSqlQuery>

Scalar_setter::Scalar_setter(const int id, QWidget *parent) :
    QValueDialog(parent),
    ui(new Ui::Scalar_setter)
{
    ui->setupUi(this);
    setData(id);

    QSqlQuery query;
    query.prepare("SELECT values_scalar.id,name,active FROM values_scalar "
                  "LEFT JOIN signs_scalar ON signs_scalar.id = values_scalar.sign_id "
                  "WHERE class_descriptions_id = ?");
    query.addBindValue(getId());
    query.exec();

    while(query.next())
    {
        auto *item = new QListWidgetItem(query.value("name").toString());
        QVariant v;
        v.setValue(query.value("id").toInt());
        item->setData(Qt::UserRole, v);

        if(query.value("active").toInt())
        {
            ui->listWidget_2->addItem(item);
            continue;
        }

        ui->listWidget->addItem(item);
    }
}

Scalar_setter::~Scalar_setter()
{
    delete ui;
}

void Scalar_setter::on_pushButton_2_clicked()
{
    this->close();
}

void Scalar_setter::updateActive(const int active, const int s_id)
{
    QSqlQuery query;
    query.prepare("UPDATE values_scalar SET active = ? WHERE class_descriptions_id = ? AND id = ?");
    query.addBindValue(active);
    query.addBindValue(getId());
    query.addBindValue(s_id);
    query.exec();
}

void Scalar_setter::on_pushButton_clicked()
{
    int size = ui->listWidget->count();

    for(int i = 0; i < size; i++)
    {
        updateActive(0, ui->listWidget->item(i)->data(Qt::UserRole).value<int>());
    }

    size = ui->listWidget_2->count();

    for(int i = 0; i < size; i++)
    {
        updateActive(1, ui->listWidget_2->item(i)->data(Qt::UserRole).value<int>());
    }

    this->accept();
}

void Scalar_setter::on_pushButton_3_clicked()
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

        delete ui->listWidget->takeItem(ui->listWidget->row(item));
    }
}

void Scalar_setter::on_pushButton_4_clicked()
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

        delete ui->listWidget_2->takeItem(ui->listWidget_2->row(item));
    }
}
