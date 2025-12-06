#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void getInfo(QString username,QString password);
    void showInText();
    void clearInText();

signals:
    void btnClicked();
    void showInfo();
    void clearInfo();

private slots:
    void on_btn1_clicked();
    void showDialog();


    void on_btn2_clicked();

private:
    Ui::MainWindow *ui;
    QString m_username;
    QString m_password;
};
#endif // MAINWINDOW_H
