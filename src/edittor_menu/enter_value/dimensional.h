#ifndef DIMENSIONAL_H
#define DIMENSIONAL_H

#include "../../classes/qvaluedialog.h"

namespace Ui {
class Dimensional;
}

class Dimensional : public QValueDialog
{
    Q_OBJECT

public:
    explicit Dimensional(QWidget *parent = nullptr);
    ~Dimensional();

private slots:
    void checker();

private:
    Ui::Dimensional *ui;
};

#endif // DIMENSIONAL_H
