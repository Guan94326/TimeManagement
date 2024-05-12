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
    int uniqueID = 0;

public:
    explicit uRecordEditDialog(QWidget *parent = nullptr);
    ~uRecordEditDialog();

    QSqlRecord getRecord();
    void setRecord(const QSqlRecord &newRecord, int cur_uniqueID);

private:
    Ui::uRecordEditDialog *ui;
};

#endif // URECORDEDITDIALOG_H
