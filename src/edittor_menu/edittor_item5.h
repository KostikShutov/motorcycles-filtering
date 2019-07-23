#ifndef EDITTOR_ITEM5_H
#define EDITTOR_ITEM5_H

#include <QDialog>

namespace Ui {
class Edittor_item5;
}

class Edittor_item5 : public QDialog
{
    Q_OBJECT

private:
    int isClassValid(const int id);

public:
    explicit Edittor_item5(QWidget *parent = nullptr);
    ~Edittor_item5();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Edittor_item5 *ui;
};

#endif // EDITTOR_ITEM5_H
