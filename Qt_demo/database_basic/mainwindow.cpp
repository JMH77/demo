#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "databasemanager.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,m_db(new databasemanager)
{
    ui->setupUi(this);
    m_db->initDatabase();

}

MainWindow::~MainWindow()
{
    delete ui;
}
