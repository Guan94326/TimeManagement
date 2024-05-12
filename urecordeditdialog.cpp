#include "urecordeditdialog.h"
#include "ui_urecordeditdialog.h"

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
