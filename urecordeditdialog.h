#ifndef URECORDEDITDIALOG_H
#define URECORDEDITDIALOG_H

#include <QDialog>

namespace Ui {
class uRecordEditDialog;
}

class uRecordEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit uRecordEditDialog(QWidget *parent = nullptr);
    ~uRecordEditDialog();

private:
    Ui::uRecordEditDialog *ui;
};

#endif // URECORDEDITDIALOG_H
