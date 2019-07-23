#ifndef RESULTER_H
#define RESULTER_H

#include <QDialog>

namespace Ui {
class Resulter;
}

class Resulter : public QDialog
{
    Q_OBJECT

private:
    QSet<int> getSetById(const int id, const int type, const QVariant value);

public:
    explicit Resulter(QWidget *parent = nullptr);
    Resulter(QList<int> _ides,
             QList<int> _types,
             QList<QVariant> _values,
             QWidget *parent = nullptr);
    ~Resulter();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Resulter *ui;
};

#endif // RESULTER_H
