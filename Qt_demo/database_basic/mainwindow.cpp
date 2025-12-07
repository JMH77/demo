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

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initDB()
{

}
