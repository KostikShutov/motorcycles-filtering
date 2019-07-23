#include "scalar.h"
#include "ui_scalar.h"
#include <QMessageBox>
#include "../edittor_item2.h"
#include <QRegExpValidator>

Scalar::Scalar(QWidget *parent) :
    QValueDialog(parent),
    ui(new Ui::Scalar)
{
    ui->setupUi(this);

    QRegExpValidator* val = new QRegExpValidator(QRegExp("[\\w ]{1,25}"), this);
    ui->lineEdit->setValidator(val);

    connect(ui->pushButton_4, SIGNAL(clicked()), SLOT(checker()));
}

Scalar::~Scalar()
{
    delete ui;
}

void Scalar::on_pushButton_2_clicked()
{
    //Сохранить
    if(!ui->listWidget->count())
    {
        QMessageBox::warning(this, "Предупреждение", "Введите хотя бы 1 значение");
        return;
    }

    int id = getId();
    setType(id, 1);

    QSqlQuery query;
    const int size = ui->listWidget->count();

    for(int i = 0; i < size; i++)
    {
        query.prepare("INSERT INTO signs_scalar (sign_id, name) VALUES (?, ?)");
        query.addBindValue(id);
        query.addBindValue(ui->listWidget->item(i)->text());
        query.exec();
    }

    this->accept();
}

void Scalar::on_pushButton_3_clicked()
{
    //Удалить
    QList<QListWidgetItem*> items = ui->listWidget->selectedItems();
    foreach(QListWidgetItem *item, items)
    {
        delete ui->listWidget->takeItem(ui->listWidget->row(item));
    }
}

void Scalar::checker()
{
    //Плюсик
    if(!ui->lineEdit->hasAcceptableInput())
    {
        QMessageBox::warning(this, "Предупреждение", "Название значения не может быть пустым");
        return;
    }

    QString name = ui->lineEdit->text();
    const int size = ui->listWidget->count();

    for(int i = 0; i < size; i++)
    {
        if(name == ui->listWidget->item(i)->text())
        {
            QMessageBox::warning(this, "Предупреждение", "Такое значение уже существует");
            return;
        }
    }

    ui->listWidget->addItem(name);
    ui->lineEdit->setText("");
}
