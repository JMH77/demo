#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "databasemanager.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,m_dbmanager(new databasemanager)
{
    ui->setupUi(this);
    m_dbmanager->initDatabase();
    m_dbmanager->createTable();

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_insertbtn_clicked()
{
    // 1. 获取用户输入
    QString name = ui->name->text();
    QString ageStr = ui->age->text();
    
    // 2. 检查输入是否有效
    if (name.isEmpty()) {
        qDebug() << "姓名不能为空！";
        return;
    }
    
    // 3. 字符串转整数
    bool ok;
    int age = ageStr.toInt(&ok);
    if (!ok || age < 0) {
        qDebug() << "年龄输入不合法！";
        return;
    }
    
    // 4. 插入数据
    m_dbmanager->insertData(name, age);
}

