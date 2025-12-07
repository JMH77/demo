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

private:
    QSqlDatabase* m_db;
};

#endif // DATABASEMANAGER_H
