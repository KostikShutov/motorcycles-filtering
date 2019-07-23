#ifndef EDITTOR_ITEM4_H
#define EDITTOR_ITEM4_H

#include <QDialog>

namespace Ui {
class Edittor_item4;
}

class Edittor_item4 : public QDialog
{
    Q_OBJECT

private:
    QString getTypeValues(int id, int type);

public:
    explicit Edittor_item4(QWidget *parent = nullptr);
    ~Edittor_item4();
    static QString getTypeName(int type);

private slots:
    void checker(const QModelIndex &index);

    void on_pushButton_clicked();

    void on_comboBox_activated(const QString &arg1);

private:
    Ui::Edittor_item4 *ui;
};

#endif // EDITTOR_ITEM4_H
