#include "logical.h"
#include "ui_logical.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QRegExpValidator>

Logical::Logical(QWidget *parent) :
    QValueDialog(parent),
    ui(new Ui::Logical)
{
    ui->setupUi(this);

    QRegExpValidator* val = new QRegExpValidator(QRegExp("[\\w ]{1,10}"), this);
    ui->lineEdit->setValidator(val);
    ui->lineEdit_2->setValidator(val);

    connect(ui->pushButton, SIGNAL(clicked()), SLOT(checker()));
}

Logical::~Logical()
{
    delete ui;
}

void Logical::checker()
{
    bool access1 = ui->lineEdit->hasAcceptableInput();
    bool access2 = ui->lineEdit_2->hasAcceptableInput();

    if(!access1 || !access2)
    {
        QMessageBox::warning(this, "Предупреждение", "Название значения не может быть пустым");
        return;
    }

    int id = getId();
    setType(id, 3);

    QString text1 = ui->lineEdit->text();
    QString text2 = ui->lineEdit_2->text();

    if(text1 == text2)
    {
        QMessageBox::warning(this, "Предупреждение", "Значения не могут совпадать");
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO signs_logical (sign_id, name_yes, name_no) VALUES (?, ?, ?)");
    query.addBindValue(id);
    query.addBindValue(text1);
    query.addBindValue(text2);
    query.exec();

    this->accept();
}
