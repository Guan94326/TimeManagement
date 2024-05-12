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
    void setDeleteEnabled(bool is);

public:
    explicit uRecordEditDialog(QWidget *parent = nullptr);
    ~uRecordEditDialog();

    QSqlRecord getRecord();
    void setRecord(const QSqlRecord &newRecord, int cur_uniqueID);

signals:
    void recordDelete(int id);

private slots:
    void on_pushButton_delete_clicked();

    void on_pushButton_set_begin_clicked();

    void on_pushButton_set_end_clicked();

private:
    Ui::uRecordEditDialog *ui;
};

#endif // URECORDEDITDIALOG_H
