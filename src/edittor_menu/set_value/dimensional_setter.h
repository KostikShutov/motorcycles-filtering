#ifndef DIMENSIONAL_SETTER_H
#define DIMENSIONAL_SETTER_H

#include "../../classes/qvaluedialog.h"

namespace Ui {
class Dimensional_setter;
}

class Dimensional_setter : public QValueDialog
{
    Q_OBJECT

public:
    explicit Dimensional_setter(QWidget *parent = nullptr);
    explicit Dimensional_setter(const int id = 0, QWidget *parent = nullptr);
    ~Dimensional_setter();

private slots:
    void on_pushButton_2_clicked();

    void checker();

private:
    Ui::Dimensional_setter *ui;
    QVariant min, max;
};

#endif // DIMENSIONAL_SETTER_H
