#include "edittor_item2.h"
#include "ui_edittor_item2.h"
#include <QSqlQuery>
#include <QListWidgetItem>
#include "enter_value/logical.h"
#include "enter_value/dimensional.h"
#include "enter_value/scalar.h"
#include <QDebug>

Edittor_item2::Edittor_item2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Edittor_item2)
{
    ui->setupUi(this);

    QSqlQuery query("SELECT * FROM signs");

    while (query.next())
    {
        if(!query.value("type").toInt())
        {
            QVariant v(query.value("id").toInt());
            ui->comboBox->addItem(query.value("name").toString(), v);
        }
    }
}

Edittor_item2::~Edittor_item2()
{
    delete ui;
}

void Edittor_item2::on_pushButton_2_clicked()
{
    this->close();
}

void Edittor_item2::on_pushButton_clicked()
{
    QValueDialog *dialog;

    if(ui->radioButton->isChecked())
        dialog = new Scalar;
    else if(ui->radioButton_2->isChecked())
        dialog = new Dimensional;
    else if(ui->radioButton_3->isChecked())
        dialog = new Logical;
    else
        return;

    dialog->setModal(true);
    dialog->setData(ui->comboBox->currentData().value<int>());
    if(dialog->exec())
    {
        ui->comboBox->removeItem(ui->comboBox->currentIndex());
    }

    delete dialog;
}
