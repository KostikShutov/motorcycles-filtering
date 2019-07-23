#include "dimensional.h"
#include "ui_dimensional.h"
#include <QMessageBox>
#include <QRegExpValidator>

Dimensional::Dimensional(QWidget *parent) :
    QValueDialog(parent),
    ui(new Ui::Dimensional)
{
    ui->setupUi(this);

    QRegExpValidator* val1 = new QRegExpValidator(QRegExp("[\\w ]{1,25}"), this);
    ui->lineEdit->setValidator(val1);

    QRegExpValidator* val2 = new QRegExpValidator(QRegExp("[+-]?\\d{1,10}"), this);
    ui->lineEdit_2->setValidator(val2);
    ui->lineEdit_3->setValidator(val2);

    connect(ui->pushButton, SIGNAL(clicked()), SLOT(checker()));
}

Dimensional::~Dimensional()
{
    delete ui;
}

void Dimensional::checker()
{
    if(!ui->lineEdit->hasAcceptableInput())
    {
        QMessageBox::warning(this, "Предупреждение", "Единица измерения не может быть пустой");
        return;
    }

    bool access1 = ui->lineEdit_2->hasAcceptableInput();
    bool access2 = ui->lineEdit_3->hasAcceptableInput();

    if(!access1 || !access2)
    {
        QMessageBox::warning(this, "Предупреждение", "Значением должно быть число или оно пусто");
        return;
    }

    int num1 = ui->lineEdit_2->text().toInt();
    int num2 = ui->lineEdit_3->text().toInt();

    if(num1 >= num2)
    {
        QMessageBox::warning(this, "Предупреждение", "Начальное значение должно быть меньше конечного");
        return;
    }

    int id = getId();
    setType(id, 2);

    QSqlQuery query;
    query.prepare("INSERT INTO signs_dimensional (sign_id, interval_start, interval_end, unit) VALUES (?, ?, ?, ?)");
    query.addBindValue(id);
    query.addBindValue(num1);
    query.addBindValue(num2);
    query.addBindValue(ui->lineEdit->text());
    query.exec();

    this->accept();
}
