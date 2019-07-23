#include "qvaluedialog.h"

QValueDialog::QValueDialog(QWidget *parent) :
    QDialog(parent){}

QValueDialog::QValueDialog(const int id, QWidget *parent) :
    QDialog(parent), sign_id(id){}

QValueDialog::~QValueDialog(){}

void QValueDialog::setData(const int id)
{
    sign_id = id;
}

int QValueDialog::getId()
{
    return sign_id;
}


void QValueDialog::setType(const int id, const int type)
{
    QVariant var1(type), var2(id);
    QSqlQuery query;
    query.prepare("UPDATE signs SET type = ? WHERE id = ?");
    query.addBindValue(var1);
    query.addBindValue(var2);
    query.exec();
}
