#ifndef URECORDEDITDIALOG_H
#define URECORDEDITDIALOG_H

#include <QDialog>
#include <QSqlRecord>

namespace Ui {
class uRecordEditDialog;
}

class uRecordEditDialog : public QDialog
{
    Q_OBJECT

private:
    QSqlRecord record;

public:
    explicit uRecordEditDialog(QWidget *parent = nullptr);
    ~uRecordEditDialog();

private:
    Ui::uRecordEditDialog *ui;
};

#endif // URECORDEDITDIALOG_H
