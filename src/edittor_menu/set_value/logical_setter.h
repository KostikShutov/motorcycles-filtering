#ifndef LOGICAL_SETTER_H
#define LOGICAL_SETTER_H

#include "../../classes/qvaluedialog.h"

namespace Ui {
class Logical_setter;
}

class Logical_setter : public QValueDialog
{
    Q_OBJECT

public:
    explicit Logical_setter(QWidget *parent = nullptr);
    explicit Logical_setter(const int id = 0, QWidget *parent = nullptr);
    ~Logical_setter();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Logical_setter *ui;
};

#endif // LOGICAL_SETTER_H
