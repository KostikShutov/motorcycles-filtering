#ifndef EDITTOR_ITEM1_H
#define EDITTOR_ITEM1_H

#include <QDialog>

namespace Ui {
class Edittor_item1;
}

class Edittor_item1 : public QDialog
{
    Q_OBJECT

public:
    explicit Edittor_item1(QWidget *parent = nullptr);
    ~Edittor_item1();

private slots:
    void on_pushButton_clicked();

    void checker();

    void on_pushButton_3_clicked();

private:
    Ui::Edittor_item1 *ui;
};

#endif // EDITTOR_ITEM1_H
