#ifndef SCALAR_SETTER_H
#define SCALAR_SETTER_H

#include "../../classes/qvaluedialog.h"

namespace Ui {
class Scalar_setter;
}

class Scalar_setter : public QValueDialog
{
    Q_OBJECT

private:
    void updateActive(const int active, const int s_id);

public:
    explicit Scalar_setter(QWidget *parent = nullptr);
    explicit Scalar_setter(const int id = 0, QWidget *parent = nullptr);
    ~Scalar_setter();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::Scalar_setter *ui;
};

#endif // SCALAR_SETTER_H
