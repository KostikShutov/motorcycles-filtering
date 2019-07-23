#include "searcher.h"
#include "ui_searcher.h"
#include "edittor_menu/edittor_item4.h"
#include "resulter.h"
#include <QSqlQuery>
#include <QComboBox>
#include <QLineEdit>
#include <QMessageBox>

Searcher::Searcher(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Searcher)
{
    ui->setupUi(this);

    ui->tableWidget->setColumnCount(3);

    QStringList horizontalHeader;
    horizontalHeader << "Признак" << "Тип" << "Значение";
    ui->tableWidget->setHorizontalHeaderLabels(horizontalHeader);

    QSqlQuery query("SELECT * FROM signs WHERE type != 0");
    int i = 0, type, id, min, max;

    int initialPos = query.at();
    query.last();
    count = query.at() + 1;
    ui->tableWidget->setRowCount(count);
    query.seek(initialPos);
    QString interval = "";

    while (query.next())
    {
        type = query.value("type").toInt();
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(Edittor_item4::getTypeName(type)));
        id = query.value("id").toInt();
        ui->tableWidget->item(i, 1)->setData(Qt::UserRole, id);

        if(type == 2)
        {
            auto *lineEdit = new QLineEdit();
            getTypeValues(id, type, min, max);
            QValidator *val = new QIntValidator(min, max, this);
            lineEdit->setValidator(val);
            ui->tableWidget->setCellWidget(i, 2, lineEdit);
            interval = " - [" + QString::number(min) + "; " + QString::number(max) + ']';
        }
        else
        {
            auto *comboBox = new QComboBox();
            comboBox->addItems(getTypeValues(id, type, min, max));
            ui->tableWidget->setCellWidget(i, 2, comboBox);
        }

        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(query.value("name").toString() + interval));
        interval = "";

        i++;
    }

    ui->tableWidget->verticalHeader()->hide();
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

Searcher::~Searcher()
{
    delete ui;
}

QStringList Searcher::getTypeValues(int id, int type, int &min, int &max)
{
    QSqlQuery query;
    QStringList result;

    switch(type)
    {
        case 1:
        {
            query.prepare("SELECT name FROM signs_scalar WHERE sign_id = ?");
            query.addBindValue(id);
            query.exec();

            result.append("");
            while(query.next())
            {
                result.append(query.value("name").toString());
            }

            break;
        }
        case 2:
        {
            query.prepare("SELECT interval_start,interval_end FROM signs_dimensional WHERE sign_id = ?");
            query.addBindValue(id);
            query.exec();
            query.next();

            min = query.value("interval_start").toInt();
            max = query.value("interval_end").toInt();

            break;
        }
        case 3:
        {
            query.prepare("SELECT name_yes,name_no FROM signs_logical WHERE sign_id = ?");
            query.addBindValue(id);
            query.exec();
            query.next();

            result.append("");
            result.append(query.value("name_yes").toString());
            result.append(query.value("name_no").toString());

            break;
        }
    }

    return result;
}

void Searcher::on_pushButton_clicked()
{
    this->close();
    emit firstWindow();
}

void Searcher::on_pushButton_2_clicked()
{
    QString type_string;
    int type;
    QLineEdit *p1;
    QComboBox *p2;
    QString value;
    QList<int> types, ides;
    QList<QVariant> values;

    for(int i = 0; i < count; i++)
    {
        type_string = ui->tableWidget->item(i, 1)->text();

        if(type_string == "Размерный")
        {
            p1 = qobject_cast<QLineEdit*>(ui->tableWidget->cellWidget(i, 2));
            value = p1->text();

            if(value == "")
                continue;

            if(!p1->hasAcceptableInput())
            {
                QMessageBox::warning(this, "Предупреждение", "Значением должно быть число или оно вышло за границы интервала");
                return;
            }

            type = 2;
        }
        else
        {
            p2 = qobject_cast<QComboBox*>(ui->tableWidget->cellWidget(i, 2));
            value = p2->currentText();

            if(value == "")
                continue;

            if(type_string == "Скалярный")
                type = 1;
            else if(type_string == "Логический")
                type = 3;
        }

        types.push_back(type);
        values.push_back(value);
        ides.push_back(ui->tableWidget->item(i, 1)->data(Qt::UserRole).toInt());
    }

    if(!types.size())
    {
        QMessageBox::warning(this, "Предупреждение", "Необходимо ввести хотя бы 1 признак");
        return;
    }

    Resulter *window = new Resulter(ides, types, values);
    window->setModal(true);
    window->exec();

    delete window;
}
