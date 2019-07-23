#include "logical_setter.h"
#include "ui_logical_setter.h"
#include <QSqlQuery>

Logical_setter::Logical_setter(const int id, QWidget *parent) :
    QValueDialog(parent),
    ui(new Ui::Logical_setter)
{
    ui->setupUi(this);
    setData(id);

    QSqlQuery query;
    query.prepare("SELECT yes,no,name_yes,name_no FROM values_logical "
                  "LEFT JOIN signs_logical ON signs_logical.id = values_logical.signs_id "
                  "WHERE class_descriptions_id = ?");
    query.addBindValue(getId());
    query.exec();
    query.next();

    int yes = query.value("yes").toInt();
    int no = query.value("no").toInt();
    ui->checkBox->setChecked(yes);
    ui->checkBox_2->setChecked(no);

    QString name_yes = query.value("name_yes").toString();
    QString name_no = query.value("name_no").toString();
    ui->checkBox->setText(name_yes);
    ui->checkBox_2->setText(name_no);
}

Logical_setter::~Logical_setter()
{
    delete ui;
}

void Logical_setter::on_pushButton_clicked()
{
    this->close();
}

void Logical_setter::on_pushButton_2_clicked()
{
    int checker1 = ui->checkBox->isChecked();
    int checker2 = ui->checkBox_2->isChecked();

    QSqlQuery query;
    query.prepare("UPDATE values_logical SET yes = ?, no = ? WHERE class_descriptions_id = ?");
    query.addBindValue(checker1);
    query.addBindValue(checker2);
    query.addBindValue(getId());
    query.exec();

    this->accept();
}
