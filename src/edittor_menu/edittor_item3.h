#ifndef EDITTOR_ITEM3_H
#define EDITTOR_ITEM3_H

#include <QDialog>

namespace Ui {
class Edittor_item3;
}

class Edittor_item3 : public QDialog
{
    Q_OBJECT

private:
    void addTypeValue(const int c_d_id, const int s_id_old, const int type);

public:
    explicit Edittor_item3(QWidget *parent = nullptr);
    ~Edittor_item3();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_comboBox_activated(const QString &arg1);

private:
    Ui::Edittor_item3 *ui;
};

#endif // EDITTOR_ITEM3_H
