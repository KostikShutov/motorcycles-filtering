#ifndef LOGICAL_H
#define LOGICAL_H

#include "../../classes/qvaluedialog.h"

namespace Ui {
class Logical;
}

class Logical : public QValueDialog
{
    Q_OBJECT

public:
    explicit Logical(QWidget *parent = nullptr);
    ~Logical();

private slots:
    void checker();

private:
    Ui::Logical *ui;
};

#endif // LOGICAL_H
