#include "databasemanager.h"

#include <QDebug>

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
    m_db->setDatabaseName("test1207");
    m_db->setHostName("localhost");	//主机地址
    m_db->setUserName("uroot");			//进入数据库的用户名
    m_db->setPassword("jaten123");		//进入数据库的密码
    m_db->setPort(3306);				//数据库使用的端口号
    if(!m_db->open()){
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


