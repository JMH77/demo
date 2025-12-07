#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>

class databasemanager
{
public:
    databasemanager();
    ~databasemanager();

    void initDatabase();
    void createTable();
    bool isConnected();
    void disconnectDb();
    void insertData(const QString &name, int age);

private:
    QSqlDatabase* m_db;
};

#endif // DATABASEMANAGER_H
