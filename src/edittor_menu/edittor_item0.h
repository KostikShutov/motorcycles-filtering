#ifndef EDITTOR_ITEM0_H
#define EDITTOR_ITEM0_H

#include <QDialog>

namespace Ui {
class Edittor_item0;
}

class Edittor_item0 : public QDialog
{
    Q_OBJECT

public:
    explicit Edittor_item0(QWidget *parent = nullptr);
    ~Edittor_item0();

private slots:
    void on_pushButton_clicked();

    void checker();

    void on_pushButton_3_clicked();

private:
    Ui::Edittor_item0 *ui;
};

#endif // EDITTOR_ITEM0_H
