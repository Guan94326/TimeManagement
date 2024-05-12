#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include "urecordeditdialog.h"
#include <QSqlQuery>


void MainWindow::openTable()
{
    //初始化
    queryModelUnfished = new QSqlQueryModel(this);
    selectionModelUnfinished = new QItemSelectionModel(queryModelUnfished, this);
    ui->tableView_show_unfinished->setModel(queryModelUnfished);
    ui->tableView_show_unfinished->setSelectionModel(selectionModelUnfinished);
    queryModelFished = new QSqlQueryModel(this);
    selectionModelFinished = new QItemSelectionModel(queryModelFished, this);
    ui->tableView_show_finished->setModel(queryModelFished);
    ui->tableView_show_finished->setSelectionModel(selectionModelFinished);
    queryModelAll = new QSqlQueryModel(this);
    selectionModelAll = new QItemSelectionModel(queryModelAll, this);

    //设置不可编辑和行选择
    ui->tableView_show_finished->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView_show_unfinished->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView_show_finished->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_show_unfinished->setSelectionBehavior(QAbstractItemView::SelectRows);

    //查询语句
    queryModelUnfished->setQuery("SELECT NAME, DATE_BEGIN, DATE_END, DETAIL, FINISHED, ID FROM schedule WHERE FINISHED = 0;");
    queryModelFished->setQuery("SELECT NAME, DATE_BEGIN, DATE_END, DETAIL, FINISHED, ID FROM schedule WHERE FINISHED = 1;");
    queryModelAll->setQuery("SELECT NAME, DATE_BEGIN, DATE_END, DETAIL, FINISHED, ID FROM schedule;");

    //隐藏数据
    ui->tableView_show_unfinished->setColumnHidden(DETAIL, true);
    ui->tableView_show_unfinished->setColumnHidden(FINISHED, true);
    ui->tableView_show_unfinished->setColumnHidden(ID, true);
    ui->tableView_show_finished->setColumnHidden(DETAIL, true);
    ui->tableView_show_finished->setColumnHidden(FINISHED, true);
    ui->tableView_show_finished->setColumnHidden(ID, true);

    //设置列宽
    int nameWidth = ui->tableView_show_unfinished->width() - 400;
    ui->tableView_show_unfinished->setColumnWidth(NAME, nameWidth);
    ui->tableView_show_unfinished->setColumnWidth(DATE_BEGIN, 180);
    ui->tableView_show_unfinished->setColumnWidth(DATE_END, 180);
    ui->tableView_show_finished->setColumnWidth(NAME, nameWidth);
    ui->tableView_show_finished->setColumnWidth(DATE_BEGIN, 180);
    ui->tableView_show_finished->setColumnWidth(DATE_END, 180);

    //设置组件为可用状态
    ui->checkBox_u_begin->setEnabled(true);
    ui->checkBox_u_end->setEnabled(true);
    ui->checkBox_u_name->setEnabled(true);
    ui->checkBox_begin->setEnabled(true);
    ui->checkBox_end->setEnabled(true);
    ui->checkBox_name->setEnabled(true);
    ui->action_add->setEnabled(true);

    //设置表头
    QSqlRecord headerRecord_u = queryModelUnfished->record();
    queryModelUnfished->setHeaderData(headerRecord_u.indexOf("NAME"), Qt::Horizontal,
                                      "事件名称");
    queryModelUnfished->setHeaderData(headerRecord_u.indexOf("DATE_BEGIN"), Qt::Horizontal,
                                      "开始时间");
    queryModelUnfished->setHeaderData(headerRecord_u.indexOf("DATE_END"), Qt::Horizontal,
                                      "结束时间");
    QSqlRecord headerRecord = queryModelFished->record();
    queryModelFished->setHeaderData(headerRecord.indexOf("NAME"), Qt::Horizontal,
                                       "事件名称");
    queryModelFished->setHeaderData(headerRecord.indexOf("DATE_BEGIN"), Qt::Horizontal,
                                      "开始时间");
    queryModelFished->setHeaderData(headerRecord.indexOf("DATE_END"), Qt::Horizontal,
                                      "结束时间");

    //保证主键唯一
    uniqueID = queryModelAll->rowCount();
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_open_new_database_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "选择一个数据库文件",
                                                    databasePath, "sqlite数据库(*.db)");
    if (fileName.isEmpty()) return;

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(fileName);
    db.open();

    if (!db.isOpen()) {
        QMessageBox::critical(this, "错误", "数据库文件打开失败，请重试！");
    }
    else {
        openTable();
    }

}


void MainWindow::on_checkBox_u_name_clicked(bool checked)
{
    ui->tableView_show_unfinished->setColumnHidden(0, !checked);
}


void MainWindow::on_checkBox_u_begin_clicked(bool checked)
{
    ui->tableView_show_unfinished->setColumnHidden(1, !checked);
}


void MainWindow::on_checkBox_u_end_clicked(bool checked)
{
    ui->tableView_show_unfinished->setColumnHidden(2, !checked);
}


void MainWindow::on_checkBox_name_clicked(bool checked)
{
    ui->tableView_show_finished->setColumnHidden(0, !checked);
}


void MainWindow::on_checkBox_begin_clicked(bool checked)
{
    ui->tableView_show_finished->setColumnHidden(1, !checked);
}


void MainWindow::on_checkBox_end_clicked(bool checked)
{
    ui->tableView_show_finished->setColumnHidden(2, !checked);
}


void MainWindow::on_tableView_show_unfinished_doubleClicked(const QModelIndex &index)
{
    QSqlRecord editRecord = queryModelUnfished->record(index.row());
    qDebug() << editRecord;
}


void MainWindow::on_tableView_show_finished_doubleClicked(const QModelIndex &index)
{
    QSqlRecord editRecord = queryModelFished->record(index.row());
    qDebug() << editRecord;
}


void MainWindow::on_action_add_triggered()
{
    QSqlQuery query;
    query.exec("SELECT * FROM schedule;");
    QSqlRecord record = query.record();
    uRecordEditDialog *dialog = new uRecordEditDialog(this);
    dialog->setRecord(record, uniqueID);
    if (dialog->exec() == QDialog::Accepted) {
        //sqlite命令插入
        QSqlRecord curRecord = dialog->getRecord();
        query.prepare("INSERT INTO schedule(NAME, DATE_BEGIN, DATE_END, DETAIL, FINISHED, ID) "
                      "VALUES(:NAME, :DATE_BEGIN, :DATE_END, :DETAIL, :FINISHED, :ID);");
        query.bindValue(":NAME", curRecord.value("NAME"));
        query.bindValue(":DATE_BEGIN", curRecord.value("DATE_BEGIN"));
        query.bindValue(":DATE_END", curRecord.value("DATE_END"));
        query.bindValue(":DETAIL", curRecord.value("DETAIL"));
        query.bindValue(":FINISHED", curRecord.value("FINISHED"));
        query.bindValue(":ID", curRecord.value("ID"));

        if (!query.exec()) {
            QMessageBox::critical(this, "错误", "插入数据失败，请重试！");
        }
        else {
            queryModelUnfished->setQuery("SELECT NAME, DATE_BEGIN, DATE_END, DETAIL, FINISHED, ID FROM schedule WHERE FINISHED = 0;");
            queryModelFished->setQuery("SELECT NAME, DATE_BEGIN, DATE_END, DETAIL, FINISHED, ID FROM schedule WHERE FINISHED = 1;");
            queryModelAll->setQuery("SELECT NAME, DATE_BEGIN, DATE_END, DETAIL, FINISHED, ID FROM schedule;");
            uniqueID = queryModelAll->rowCount();
        }
    }
    delete dialog;
}

