#include "urecordeditdialog.h"
#include "ui_urecordeditdialog.h"
#include <QInputDialog>


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
