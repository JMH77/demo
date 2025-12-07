#include "databasemanager.h"

#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

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
    //此处是为了检查之前是否有数据库连接对象存在，若存在则先关闭连接并删除对象，防止内存泄漏
    //首先检查m_db指的是否为空
    if(m_db){
        // 检查是否打开
        if(m_db->isOpen()){
            m_db->close();  // 先关闭
        }
        delete m_db;  // 再删除
        m_db = nullptr;  // 置空
    }

    m_db = new QSqlDatabase(QSqlDatabase::addDatabase("QMYSQL"));
    // QSqlDatabase m_db = QSqlDatabase::addDatabase("QODBC");
    m_db->setDatabaseName("SYS");  // 改成自己的数据库   这个地方些什么？  就是你在navicat中看到的每个连接下面的，就是数据库名字
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

//判断是否连接
bool databasemanager::isConnected()
{
    // 先检查指针是否为空
    if(!m_db){
        return false;
    }
    // 再检查数据库是否打开
    if(!m_db->isOpen()){
        return false;
    }
    return true;
}

//断开数据库
void databasemanager::disconnectDb()
{
    // 先检查指针是否为空
    if(!m_db){
        qDebug() << "数据库对象为空，无需断开连接！";
        return;
    }
    // 再检查是否打开
    if(m_db->isOpen()){
        m_db->close();
        qDebug() << "数据库连接已断开！";
    }
}

//建表
void databasemanager::createTable()
{
    // if(!m_db->isOpen()){
    //     if(!m_db){
    //         qDebug() << "数据库对象为空，无法创建数据表！";
    //         return ;
    //     }
    //     qDebug() << "数据库未打开，无法创建数据表！";
    //     return ;
    // }

    // 1. 先检查指针是否为空
    if(!m_db){
        qDebug() << "数据库对象为空，无法创建数据表！";
        return;
    }
    
    // 2. 检查数据库是否打开
    if(!m_db->isOpen()){
        qDebug() << "数据库未打开，无法创建数据表！";
        return;
    }

    QString crtUserTable = R"(
      CREATE TABLE IF NOT EXISTS USERS(
        id INTEGER PRIMARY KEY AUTO_INCREMENT,
        name VARCHAR(50) NOT NULL,
        age INTEGER DEFAULT 0,
        create_time DATETIME DEFAULT CURRENT_TIMESTAMP
        )
     )";
    
    QSqlQuery query(*m_db);
    // query.exec(crtUserTable);
    if(!query.exec(crtUserTable)){
        QString errorstr = query.lastError().text();
        qDebug() << "创建数据表失败，错误信息：" << errorstr;
    }
    else{
        qDebug() << "创建数据表成功！";
    }
}

void databasemanager::insertData(const QString &name, int age)
{
    if(!m_db){
        qDebug() << "数据库对象为空，无法创建数据表！";
        return;
    }
    
    // 2. 检查数据库是否打开
    if(!m_db->isOpen()){
        qDebug() << "数据库未打开，无法创建数据表！";
        return;
    }

    QSqlQuery query(*m_db);
    query.prepare("INSERT INTO USERS (name,age) VALUES (:name, :age)");
    query.bindValue(":name", name); 
    query.bindValue(":age", age);
    if(!query.exec()){
        QString errorstr = query.lastError().text();
        qDebug() << "插入数据失败，错误信息：" << errorstr;
    }
    else{
        qDebug() << "插入数据成功！";
    }
}







