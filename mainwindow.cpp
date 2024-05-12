#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QSqlRecord>

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

    //设置不可编辑和行选择
    ui->tableView_show_finished->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView_show_unfinished->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView_show_finished->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_show_unfinished->setSelectionBehavior(QAbstractItemView::SelectRows);

    //查询语句
    queryModelUnfished->setQuery("SELECT NAME, DATE_BEGIN, DATE_END FROM schedule WHERE FINISHED = 'N';");
    queryModelFished->setQuery("SELECT NAME, DATE_BEGIN, DATE_END FROM schedule WHERE FINISHED = 'Y';");

    //设置列宽
    int nameWidth = ui->tableView_show_unfinished->width() - 500;
    ui->tableView_show_unfinished->setColumnWidth(0, nameWidth);
    ui->tableView_show_unfinished->setColumnWidth(1, 240);
    ui->tableView_show_unfinished->setColumnWidth(2, 240);
    ui->tableView_show_finished->setColumnWidth(0, nameWidth);
    ui->tableView_show_finished->setColumnWidth(1, 240);
    ui->tableView_show_finished->setColumnWidth(2, 240);

    //设置组件为可用状态
    ui->checkBox_u_begin->setEnabled(true);
    ui->checkBox_u_end->setEnabled(true);
    ui->checkBox_u_name->setEnabled(true);
    ui->checkBox_begin->setEnabled(true);
    ui->checkBox_end->setEnabled(true);
    ui->checkBox_name->setEnabled(true);

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

