#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>

class QSqlQueryModel;
class QItemSelectionModel;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QString databasePath = "D:\\project\\QT\\TimeManagement"; //数据库路径
    QSqlDatabase db;
    QSqlQueryModel *queryModelUnfished;
    QSqlQueryModel *queryModelFished;
    QItemSelectionModel *selectionModelUnfinished;
    QItemSelectionModel *selectionModelFinished;

private:
    void openTable(); //打开表格

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_action_open_new_database_triggered();

    void on_checkBox_u_name_clicked(bool checked);

    void on_checkBox_u_begin_clicked(bool checked);

    void on_checkBox_u_end_clicked(bool checked);

    void on_checkBox_name_clicked(bool checked);

    void on_checkBox_begin_clicked(bool checked);

    void on_checkBox_end_clicked(bool checked);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
