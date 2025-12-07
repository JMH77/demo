#include "databasemanager.h"

#include <QDebug>

databasemanager::databasemanager() {

}


void databasemanager::initDatabase()
{
    QSqlDatabase m_db = QSqlDatabase::addDatabase("QMYSQL");
    m_db.setDatabaseName("test1207");
    m_db.setHostName("localhost");	//主机地址
    m_db.setUserName("uroot");			//进入数据库的用户名
    m_db.setPassword("jaten123");		//进入数据库的密码
    m_db.setPort(3306);				//数据库使用的端口号
    if(!m_db.open()){
        qDebug() << "asuifhaie";
    }

}
