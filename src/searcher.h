#ifndef SEARCHER_H
#define SEARCHER_H

#include <QMainWindow>

namespace Ui {
class Searcher;
}

class Searcher : public QMainWindow
{
    Q_OBJECT

private:
    QStringList getTypeValues(int id, int type, int &min, int &max);

public:
    explicit Searcher(QWidget *parent = nullptr);
    ~Searcher();

signals:
    void firstWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Searcher *ui;
    int count;
};

#endif // SEARCHER_H
