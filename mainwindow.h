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
    enum tableViewColumnIndex {
        NAME = 0, DATE_BEGIN, DATE_END, DETAIL, FINISHED, ID
    };
    int uniqueID = 0;
    int nameWidth = 480;

private:
    QSqlDatabase db;
    QSqlQueryModel *queryModelUnfished;
    QSqlQueryModel *queryModelFished;
    QSqlQueryModel *queryModelAll;
    QItemSelectionModel *selectionModelUnfinished;
    QItemSelectionModel *selectionModelFinished;
    QItemSelectionModel *selectionModelAll;

private:
    void openInitialFile(); //打开初始
    void newDatabaseFile(QString fileName); //新建数据库文件
    void openTable(); //打开表格
    void updateRecord(int id); //修改特定id的数据
    void deleteRecord(int id); //删除特定id的数据

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void sizeChanged();

private slots:
    void on_action_open_new_database_triggered();

    void on_checkBox_u_name_clicked(bool checked);

    void on_checkBox_u_begin_clicked(bool checked);

    void on_checkBox_u_end_clicked(bool checked);

    void on_checkBox_name_clicked(bool checked);

    void on_checkBox_begin_clicked(bool checked);

    void on_checkBox_end_clicked(bool checked);

    void on_tableView_show_unfinished_doubleClicked(const QModelIndex &index);

    void on_tableView_show_finished_doubleClicked(const QModelIndex &index);

    void on_action_add_triggered();

private slots:
    void on_record_delete(int id);

    void on_tableView_show_unfinished_iconSizeChanged(const QSize &size);

    void on_pushButton_u_begin_clicked();

    void on_pushButton_u_end_clicked();

    void on_pushButton_begin_clicked();

    void on_pushButton_end_clicked();

private:
    Ui::MainWindow *ui;

    // QWidget interface
protected:
    virtual void resizeEvent(QResizeEvent *event) override;
};
#endif // MAINWINDOW_H
