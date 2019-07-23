#ifndef QVALUEDIALOG_H
#define QVALUEDIALOG_H

#include <QDialog>
#include <QSqlQuery>
#include <QVariant>

namespace Ui {
class QValueDialog;
}

class QValueDialog : public QDialog
{
public:
    explicit QValueDialog(QWidget *parent = nullptr);
    explicit QValueDialog(const int id = 0, QWidget *parent = nullptr);
    ~QValueDialog();
    void setData(const int id);
    int getId();
    void setType(const int id, const int type);

public:
    int sign_id;
};

#endif // QVALUEDIALOG_H
