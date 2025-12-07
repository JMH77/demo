#include "databasemanager.h"

#include <QDebug>
#include <QSqlError>

databasemanager::databasemanager() {
    m_db = nullptr;
}

databasemanager::~databasemanager() {
    if (m_db) {
        m_db->close();
        delete m_db;
    }
}

void databasemanager::initDatabase()
{
    m_db = new QSqlDatabase(QSqlDatabase::addDatabase("QMYSQL"));
    // QSqlDatabase m_db = QSqlDatabase::addDatabase("QODBC");
    m_db->setDatabaseName("MySQL");
    m_db->setHostName("localhost");	//主机地址
    m_db->setUserName("root");			//进入数据库的用户名
    m_db->setPassword("jaten123");		//进入数据库的密码
    m_db->setPort(3306);				//数据库使用的端口号
    if(!m_db->open()){
        QString errorstr = m_db->lastError().text();
        qDebug() << "数据库打开失败，错误信息：" << errorstr;
        qDebug() << "数据库打开失败！";
    }
    else{
        qDebug() << "数据库打开成功！";
    }
}

bool databasemanager::isConnected()
{
    if(!m_db->isOpen()){
        return false;
    }
    return true;
}

void databasemanager::createTable()
{
    
}


