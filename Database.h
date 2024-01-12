#ifndef DATABASE_H
#define DATABASE_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStandardPaths>
#include <QDebug>

class Database
{
public:
    Database(const QString& dbName);

    static QSqlDatabase getDatabaseConnection();
    void openConnection();
    void closeConnection();

    bool createTable();
    void removeConnection();

private:
    QString m_dbName;
    QSqlDatabase m_db;
};
#endif // DATABASE_H
