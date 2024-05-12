#include "urecordeditdialog.h"
#include "ui_urecordeditdialog.h"
#include <QInputDialog>
#include <QSqlRecord>

QSqlRecord uRecordEditDialog::getRecord()
{
    record.setValue("NAME", ui->plainTextEdit_name->toPlainText());
    record.setValue("DATE_BEGIN", ui->dateTimeEdit_begindate->dateTime().toString("yyyy-MM-dd hh:mm"));
    record.setValue("DATE_END", ui->dateTimeEdit_enddate->dateTime().toString("yyyy-MM-dd hh:mm"));
    record.setValue("DETAIL", ui->plainTextEdit_detail->toPlainText());
    record.setValue("FINISHED", ui->radioButton_y->isChecked()?1:0);
    record.setValue("ID", uniqueID + 1);
    return record;
}

void uRecordEditDialog::setRecord(const QSqlRecord &newRecord, int cur_uniqueID)
{
    record = newRecord;
    uniqueID = cur_uniqueID;
    ui->plainTextEdit_name->setPlainText(record.value("NAME").toString());
    ui->dateTimeEdit_begindate->setDateTime(record.value("DATE_BEGIN").toDateTime());
    ui->dateTimeEdit_enddate->setDateTime(record.value("DATE_END").toDateTime());
    ui->plainTextEdit_detail->setPlainText(record.value("DETAIL").toString());
    int isNo = record.value("FINISHED").toBool();
    ui->radioButton_y->setChecked(isNo);
    ui->radioButton_n->setChecked(!isNo);
}

void uRecordEditDialog::setDeleteEnabled(bool is)
{
    ui->pushButton_delete->setEnabled(is);
}

uRecordEditDialog::uRecordEditDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::uRecordEditDialog)
{
    ui->setupUi(this);
}

uRecordEditDialog::~uRecordEditDialog()
{
    delete ui;
}

void uRecordEditDialog::on_pushButton_delete_clicked()
{
    int id = uniqueID + 1;
    emit recordDelete(id);
    ui->pushButton_cancel->click();
}

