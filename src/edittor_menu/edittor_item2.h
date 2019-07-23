#ifndef EDITTOR_ITEM2_H
#define EDITTOR_ITEM2_H

#include <QDialog>

namespace Ui {
class Edittor_item2;
}

class Edittor_item2 : public QDialog
{
    Q_OBJECT

public:
    explicit Edittor_item2(QWidget *parent = nullptr);
    ~Edittor_item2();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::Edittor_item2 *ui;
};

#endif // EDITTOR_ITEM2_H
