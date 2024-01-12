#include "database.h"
#include <QSqlError>
#include <QStandardPaths>
#include <QDebug>
#include <QThread>

Database::Database(const QString& dbName)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE", dbName);
    m_db.setDatabaseName(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/" + dbName);
}

QSqlDatabase Database::getDatabaseConnection() {
    QString connectionName = QString("indexerConnection_%1").arg((quintptr)QThread::currentThreadId());
    if (!QSqlDatabase::contains(connectionName)) {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", connectionName);
        QString appDataLocation = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
        db.setDatabaseName(appDataLocation + "/indexerFile.db");
        if (!db.open()) {
            qWarning() << "Error: Cannot open database" << db.lastError().text();
            throw std::runtime_error("Database connection failed");
        }
        return db;
    }
    return QSqlDatabase::database(connectionName);
}

void Database::closeConnection()
{
    if (m_db.isOpen()) {
        m_db.close();
    }
    //QSqlDatabase::removeDatabase(m_db.connectionName());
}

bool Database::createTable()
{
    QSqlQuery query(m_db);

    QString tblFileCreate = "CREATE TABLE IF NOT EXISTS files ("
                            "id STRING PRIMARY KEY,"
                            "fileName STRING,"
                            "lastModified DATE,"
                            "creationDate DATE,"
                            "fileSize BIGINT,"
                            "fileExtension STRING,"
                            "fileType STRING"
                            ")";
    if (!query.exec(tblFileCreate)) {
        qCritical() << "Failed to create the 'files' table:" << query.lastError().text();
        return false;
    }

    return true;
}



void Database::removeConnection()
{
    QSqlDatabase::removeDatabase(m_db.connectionName());
}
