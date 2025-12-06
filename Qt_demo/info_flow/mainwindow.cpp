#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this,&MainWindow::btnClicked,this,&MainWindow::showDialog);
    connect(this,&MainWindow::showInfo,this,&MainWindow::showInText);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn1_clicked()
{
    emit btnClicked();
}

void MainWindow::showDialog()
{
    //创建对话框、设置大小
    QDialog dlg(this);
    dlg.setWindowTitle("登录"); // 对话框标题
    dlg.setFixedSize(300, 150); // 固定大小

    //创建控件：用户名标签+输入框、密码标签+输入框
    QLabel *lblUser = new QLabel("用户名：", &dlg);
    QLineEdit *editUser = new QLineEdit(&dlg); // 用户名输入框
    QLabel *lblPwd = new QLabel("密  码：", &dlg);
    QLineEdit *editPwd = new QLineEdit(&dlg); // 密码输入框
    editPwd->setEchoMode(QLineEdit::Password); // 密码隐藏显示


    //创建确认/取消按钮
    QPushButton *btnOk = new QPushButton("确认", &dlg);
    QPushButton *btnCancel = new QPushButton("取消", &dlg);

    //布局控件（垂直+水平布局）
    QVBoxLayout *mainLayout = new QVBoxLayout(&dlg); // 主垂直布局
    QHBoxLayout *userLayout = new QHBoxLayout();     // 用户名行布局
    QHBoxLayout *pwdLayout = new QHBoxLayout();      // 密码行布局
    QHBoxLayout *btnLayout = new QHBoxLayout();      // 按钮行布局

    userLayout->addWidget(lblUser);
    userLayout->addWidget(editUser);
    pwdLayout->addWidget(lblPwd);
    pwdLayout->addWidget(editPwd);
    btnLayout->addStretch(); // 按钮右对齐
    btnLayout->addWidget(btnOk);
    btnLayout->addWidget(btnCancel);

    mainLayout->addLayout(userLayout);
    mainLayout->addLayout(pwdLayout);
    mainLayout->addLayout(btnLayout);
    dlg.setLayout(mainLayout);

    //建立对话框槽函数连接
    connect(btnOk,&QPushButton::clicked,&dlg,&QDialog::accept);
    connect(btnCancel,&QPushButton::clicked,&dlg,&QDialog::reject);

    //点击确认之后的逻辑
    if(dlg.exec() == QDialog::Accepted){
        getInfo(editUser->text(),editPwd->text());
    }
    // qDebug() << "asuifgu" << m_username << "asdufhi" << m_password;
}


void MainWindow::getInfo(QString username,QString password)
{
    m_username = username;
    m_password = password;
}

void MainWindow::showInText()
{
    ui->textShow->setText("用户名："  + m_username +  + "\n密码：" + m_password);
}

void MainWindow::clearInText()
{
    ui->textShow->clear();
}

void MainWindow::on_btn2_clicked()
{
        emit showInfo();
        qDebug() << "asfgbiuye";

}
