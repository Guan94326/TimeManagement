#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQueryModel>

void MainWindow::openTable()
{
    queryModel = new QSqlQueryModel(this);
    selectionModel = new QItemSelectionModel(queryModel, this);
    ui->tableView_show->setModel(queryModel);
    ui->tableView_show->setSelectionModel(selectionModel);

    //查询语句
    queryModel->setQuery("SELECT NAME, DATE_BEGIN, DATE_END FROM schedule;");

    //设置列宽
    int tableViewWidth = ui->tableView_show->width();
    //ui->tableView_show->horizontalHeader()->setMinimumSectionSize();
    ui->tableView_show->setColumnWidth(0, tableViewWidth / 3);
    ui->tableView_show->setColumnWidth(1, tableViewWidth / 3);
    ui->tableView_show->setColumnWidth(2, tableViewWidth / 3);
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

