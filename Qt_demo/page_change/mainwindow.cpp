#include "mainwindow.h"
#include <QMainWindow>
#include <QWidget>
#include <QStackedWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpacerItem>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setFixedSize(600,400);
    InitStackedWidget();

}

MainWindow::~MainWindow()
{

}

void MainWindow::InitStackedWidget()
{
    //创建实例并设置为中央部件
    m_stackedwidget = new QStackedWidget(this);
    setCentralWidget(m_stackedwidget);

    QWidget* pagelogin = new QWidget(this);
    QWidget* pagemain = new QWidget(this);

    setLoginPage(pagelogin);

    int loginIndex = m_stackedwidget->addWidget(pagelogin);
    int mainIndex = m_stackedwidget->addWidget(pagemain);
    qDebug() << "ewfhuiaew" << loginIndex << "     " << mainIndex;


    m_stackedwidget->setCurrentIndex(loginIndex);

}


void MainWindow::setLoginPage(QWidget* page)
{
    page->setWindowTitle("登录");
    page->setFixedSize(600,400);

    //水平
    QHBoxLayout* hbox = new QHBoxLayout(page);
    //竖直
    QVBoxLayout* vbox = new QVBoxLayout(page);

    //标签
    QLabel* usernameLabel = new QLabel(page);
    QLabel* passwordLabel = new QLabel(page);

    //输入框
    QLineEdit* usernameEdit = new QLineEdit(page);
    QLineEdit* passwordEdit = new QLineEdit(page);

    //按钮
    QPushButton* loginButton = new QPushButton(page);
    QPushButton* registButton = new QPushButton(page);
    loginButton->setText("登录");
    registButton->setText("注册");

    //控件样式设置
    // 1. 标签样式（字体、大小、固定宽度，确保左右对齐）
    QString labelQss = R"(
        QLabel {
            height: 60px;
            font-size: 16px; /* 字体大小 */
            font-weight: 500; /* 字体粗细（500=半粗） */
            color: #333333; /* 字体颜色（深灰） */
            width: 80px; /* 固定宽度，让两个标签对齐 */
            text-align: right; /* 文本右对齐，贴近输入框 */
        }
    )";
    usernameLabel->setStyleSheet(labelQss);
    passwordLabel->setStyleSheet(labelQss);

    // 2. 输入框样式（高度、边框、内边距、聚焦效果）
    QString editQss = R"(
        QLineEdit {
            height: 60px; /* 输入框高度 */
            width: 280px;   //zhege  这个不生效我靠
            font-size: 15px; /* 输入框内字体大小 */
            border: 1px solid #E5E5E5; /* 边框颜色（浅灰） */
            border-radius: 6px; /* 圆角（柔和） */
            padding-left: 15px; /* 左侧内边距，避免文字贴边 */
            padding-right: 15px; /* 右侧内边距 */
            background-color: white; /* 背景色 */
        }
        QLineEdit:focus {
            border-color: #1890FF; /* 聚焦时边框变蓝色 */
            outline: none; /* 去掉默认聚焦外框 */
            box-shadow: 0 0 5px rgba(24, 144, 255, 0.2); /* 聚焦时轻微阴影，增强视觉反馈 */
        }
    )";
    usernameEdit->setStyleSheet(editQss);
    passwordEdit->setStyleSheet(editQss);
    // 输入框固定宽度（可选，避免太宽或太窄）
    passwordEdit->setFixedWidth(280);
    usernameEdit->setFixedWidth(280);

    // 3. 按钮样式（两个按钮完全一样，共用一个 QSS）
    QString btnQss = R"(
    QPushButton {
        height: 42px; /* 按钮高度 */
        font-size: 16px; /* 字体大小 */
        padding: 0 45px; /* 左右内边距（控制按钮宽度） */
        border: none; /* 去掉默认边框 */
        border-radius: 6px; /* 圆角 */
        background-color: #1890FF; /* 统一颜色（你可以随便改） */
        color: white; /* 字体白色 */
        cursor: pointer; /* 鼠标悬浮变手型 */
    }
    QPushButton:hover {
        background-color: #096DD9; /* hover 加深 */
    }
    QPushButton:pressed {
        background-color: #0050B3; /* 按下再加深 */
    }
)";

    // 两个按钮直接用同一个 QSS，样式完全一致
    loginButton->setStyleSheet(btnQss);
    registButton->setStyleSheet(btnQss);



    //用户名行
    QHBoxLayout* usernameBox = new QHBoxLayout(page);
    usernameLabel->setText("用户名：");
    usernameBox->addWidget(usernameLabel);
    usernameBox->addWidget(usernameEdit);

    //密码行
    QHBoxLayout* passwordBox = new QHBoxLayout(page);
    passwordLabel->setText("密码：");
    passwordBox->addWidget(passwordLabel);
    passwordBox->addWidget(passwordEdit);

    //按钮行
    QHBoxLayout* buttonBox = new QHBoxLayout(page);
    buttonBox->addWidget(loginButton);
    buttonBox->addWidget(registButton);

    /*向垂直盒子添加*/
    //给 vbox 添加「顶部弹簧」：推动控件往下，实现垂直居中
    vbox->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    vbox->addLayout(usernameBox);
    vbox->addLayout(passwordBox);
    vbox->addLayout(buttonBox);
    //给 vbox 添加「顶部弹簧」：推动控件往下，实现垂直居中
    vbox->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));

    /*向水平盒子添加*/
    //给 hbox 添加「左侧弹簧」：推动 vbox 往右，实现水平居中
    hbox->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    hbox->addLayout(vbox);
    //给 hbox 添加「右侧弹簧」：和左侧弹簧配合，实现水平居中
    hbox->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
}




