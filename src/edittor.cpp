#include "edittor.h"
#include "ui_edittor.h"
#include "edittor_menu/edittor_item0.h"
#include "edittor_menu/edittor_item1.h"
#include "edittor_menu/edittor_item2.h"
#include "edittor_menu/edittor_item3.h"
#include "edittor_menu/edittor_item4.h"
#include "edittor_menu/edittor_item5.h"

Edittor::Edittor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Edittor)
{
    ui->setupUi(this);

    ui->listWidget->addItem("Редактирование классов");
    ui->listWidget->addItem("Редактирование признаков");
    ui->listWidget->addItem("Возможные значения признаков");
    ui->listWidget->addItem("Признаковое описание классов");
    ui->listWidget->addItem("Значения признаков для классов");
    ui->listWidget->addItem("Проверка целостности базы знаний");
}

Edittor::~Edittor()
{
    delete ui;
}

void Edittor::on_pushButton_clicked()
{
    auto currentItem = ui->listWidget->currentItem();

    QDialog *window;

    if(currentItem == ui->listWidget->item(0))
        window = new Edittor_item0;
    else if(currentItem == ui->listWidget->item(1))
        window = new Edittor_item1;
    else if(currentItem == ui->listWidget->item(2))
        window = new Edittor_item2;
    else if(currentItem == ui->listWidget->item(3))
        window = new Edittor_item3;
    else if(currentItem == ui->listWidget->item(4))
        window = new Edittor_item4;
    else if(currentItem == ui->listWidget->item(5))
        window = new Edittor_item5;

    window->setModal(true);
    window->exec();

    delete window;
}

void Edittor::on_pushButton_2_clicked()
{
    this->close();
    emit firstWindow();
}
