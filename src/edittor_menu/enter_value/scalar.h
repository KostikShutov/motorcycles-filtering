#ifndef SCALAR_H
#define SCALAR_H

#include "../../classes/qvaluedialog.h"

namespace Ui {
class Scalar;
}

class Scalar : public QValueDialog
{
    Q_OBJECT

public:
    explicit Scalar(QWidget *parent = nullptr);
    ~Scalar();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void checker();

private:
    Ui::Scalar *ui;
};

#endif // SCALAR_H
