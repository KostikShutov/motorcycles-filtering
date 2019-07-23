#include "dimensional_setter.h"
#include "ui_dimensional_setter.h"
#include <QSqlQuery>
#include <QRegExpValidator>
#include <QMessageBox>

Dimensional_setter::Dimensional_setter(const int id, QWidget *parent) :
    QValueDialog(parent),
    ui(new Ui::Dimensional_setter)
{
    ui->setupUi(this);
    setData(id);

    QSqlQuery query;
    query.prepare("SELECT active,signs_dimensional.interval_start AS min,signs_dimensional.interval_end AS max,"
                  "values_dimensional.interval_start AS v_s,values_dimensional.interval_end AS v_e FROM values_dimensional "
                  "LEFT JOIN signs_dimensional ON signs_dimensional.id = values_dimensional.signs_id "
                  "WHERE class_descriptions_id = ?");
    query.addBindValue(getId());
    query.exec();
    query.next();

    min = query.value("min");
    max = query.value("max");
    ui->label_5->setText(min.toString());
    ui->label_7->setText(max.toString());

    int isChecked = query.value("active").toInt();
    ui->checkBox->setChecked(isChecked);

    ui->lineEdit->setText(query.value("v_s").toString());
    ui->lineEdit_2->setText(query.value("v_e").toString());

    QRegExpValidator* val = new QRegExpValidator(QRegExp("[+-]?\\d{1,10}"), this);
    ui->lineEdit->setValidator(val);
    ui->lineEdit_2->setValidator(val);

    connect(ui->pushButton, SIGNAL(clicked()), SLOT(checker()));
}

Dimensional_setter::~Dimensional_setter()
{
    delete ui;
}

void Dimensional_setter::checker()
{
    bool access1 = ui->lineEdit->hasAcceptableInput();
    bool access2 = ui->lineEdit_2->hasAcceptableInput();

    if(!access1 || !access2)
    {
        QMessageBox::warning(this, "Предупреждение", "Значением должно быть число или оно пусто");
        return;
    }

    int num1 = ui->lineEdit->text().toInt();
    int num2 = ui->lineEdit_2->text().toInt();

    if(num1 < min.toInt() || num2 > max.toInt())
    {
        QMessageBox::warning(this, "Предупреждение", "Введенные значения не входят в интервал");
        return;
    }

    if(num1 >= num2)
    {
        QMessageBox::warning(this, "Предупреждение", "Начальное значение должно быть меньше конечного");
        return;
    }

    QSqlQuery query;
    query.prepare("UPDATE values_dimensional SET interval_start = ?, interval_end = ?, active = ? WHERE class_descriptions_id = ?");
    query.addBindValue(num1);
    query.addBindValue(num2);
    query.addBindValue(ui->checkBox->isChecked());
    query.addBindValue(getId());
    query.exec();

    this->accept();
}

void Dimensional_setter::on_pushButton_2_clicked()
{
    this->close();
}
