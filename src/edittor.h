#ifndef EDITTOR_H
#define EDITTOR_H

#include <QMainWindow>

namespace Ui {
class Edittor;
}

class Edittor : public QMainWindow
{
    Q_OBJECT

public:
    explicit Edittor(QWidget *parent = nullptr);
    ~Edittor();

signals:
    void firstWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Edittor *ui;
};

#endif // EDITTOR_H
