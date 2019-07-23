#include "edittor_item0.h"
#include "ui_edittor_item0.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QList>

Edittor_item0::Edittor_item0(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Edittor_item0)
{
    ui->setupUi(this);

    QSqlQuery query("SELECT name FROM classes");

    while (query.next())
        ui->listWidget->addItem(query.value("name").toString());

    QRegExpValidator* val = new QRegExpValidator(QRegExp("[\\w ]{1,25}"), this);
    ui->lineEdit->setValidator(val);

    connect(ui->pushButton_4, SIGNAL(clicked()), SLOT(checker()));
}

Edittor_item0::~Edittor_item0()
{
    delete ui;
}

void Edittor_item0::on_pushButton_clicked()
{
    this->close();
}

void Edittor_item0::checker()
{
    if(!ui->lineEdit->hasAcceptableInput())
    {
        QMessageBox::warning(this, "Предупреждение", "Название класса не может быть пустым");
        return;
    }

    QString name = ui->lineEdit->text();
    QSqlQuery query;
    query.prepare("INSERT INTO classes (name) VALUES (?)");
    query.addBindValue(name);

    if(!query.exec())
    {
        QMessageBox::warning(this, "Предупреждение", "Такой класс уже существует");
        return;
    }

    ui->listWidget->addItem(name);
    ui->lineEdit->setText("");
}

void Edittor_item0::on_pushButton_3_clicked()
{
    QList<QListWidgetItem*> items = ui->listWidget->selectedItems();
    foreach(QListWidgetItem *item, items)
    {
        QSqlQuery query;
        query.prepare("DELETE FROM classes WHERE name = ?");
        query.addBindValue(item->text());
        query.exec();

        delete ui->listWidget->takeItem(ui->listWidget->row(item));
    }
}
