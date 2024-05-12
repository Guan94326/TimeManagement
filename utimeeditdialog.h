#ifndef UTIMEEDITDIALOG_H
#define UTIMEEDITDIALOG_H

#include <QDialog>
#include <QDateTime>

namespace Ui {
class uTimeEditDialog;
}

class uTimeEditDialog : public QDialog
{
    Q_OBJECT

private:
    QDateTime dateTime;

public:
    explicit uTimeEditDialog(QWidget *parent = nullptr);
    ~uTimeEditDialog();

    QDateTime getDateTime();
    void setDateTime(const QDateTime &newDateTime);

private slots:
    void on_dateEdit_dateChanged(const QDate &date);

    void on_calendarWidget_selectionChanged();

    void on_timeEdit_timeChanged(const QTime &time);

private:
    Ui::uTimeEditDialog *ui;
};

#endif // UTIMEEDITDIALOG_H
