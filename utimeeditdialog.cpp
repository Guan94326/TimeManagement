#include "utimeeditdialog.h"
#include "ui_utimeeditdialog.h"

QDateTime uTimeEditDialog::getDateTime()
{
    dateTime = QDateTime(ui->dateEdit->date(), ui->timeEdit->time());
    return dateTime;
}

void uTimeEditDialog::setDateTime(const QDateTime &newDateTime)
{
    dateTime = newDateTime;
    ui->dateEdit->setDate(dateTime.date());
    ui->timeEdit->setTime(dateTime.time());
    ui->calendarWidget->setSelectedDate(dateTime.date());
    ui->lcdNumber_h->display(dateTime.time().hour());
    ui->lcdNumber_m->display(dateTime.time().minute());
    ui->dateEdit->setCalendarWidget(ui->calendarWidget);
}

uTimeEditDialog::uTimeEditDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::uTimeEditDialog)
{
    ui->setupUi(this);
}

uTimeEditDialog::~uTimeEditDialog()
{
    delete ui;
}

void uTimeEditDialog::on_dateEdit_dateChanged(const QDate &date)
{
    ui->calendarWidget->setSelectedDate(date);
}


void uTimeEditDialog::on_calendarWidget_selectionChanged()
{
    ui->dateEdit->setDate(ui->calendarWidget->selectedDate());
}


void uTimeEditDialog::on_timeEdit_timeChanged(const QTime &time)
{
    ui->lcdNumber_h->display(time.hour());
    ui->lcdNumber_m->display(time.minute());
}

