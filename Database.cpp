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
        QSqlDatabase m_db = QSqlDatabase::addDatabase("QSQLITE", connectionName);
        QString appDataLocation = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
        m_db.setDatabaseName(appDataLocation + "/indexerFile.db");
        if (!m_db.open()) {
            qWarning() << "Erreur : Impossible d'ouvrir la base de données" << m_db.lastError().text();
                                                                                throw std::runtime_error("Échec de la connexion à la base de données");
        }

        // Définir le nom de la connexion pour la base de données nouvellement créée
        m_db.setConnectOptions("connectOptions=QSQLITE_ENABLE_SHARED_CACHE");

        return m_db;
    }
    return QSqlDatabase::database(connectionName);
}

void Database::openConnection()
{
    if (!m_db.isOpen()) {
        if (!m_db.open()) {
                                                                                qWarning() << "Erreur : Impossible d'ouvrir la base de données" << m_db.lastError().text();
                                                                                                                                                   throw std::runtime_error("Échec de la connexion à la base de données");
        }

    }
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
    if (!m_db.isOpen()) {
        qCritical() << "Erreur : La base de données n'est pas ouverte.";
            return false;
    }
    QSqlQuery query(m_db);

    QStringList existingTables = m_db.tables();
    if (existingTables.contains("files")) {
        return true;
    }

    QString tblFileCreate = "CREATE TABLE IF NOT EXISTS files ("
                            "'id' TEXT PRIMARY KEY,"
                            "'fileName' TEXT,"
                            "'lastModified' DATE,"
                            "'creationDate' DATE,"
                            "'fileSize' INTEGER,"
                            "'fileExtension' TEXT,"
                            "'fileType' TEXT,"
                            "'folderPath' TEXT"
                            ");";
    if (!query.exec(tblFileCreate)) {
        qCritical() << "Failed to create the table::" << query.lastError().text();
        return false;
    }
    qDebug() << "La table 'whitelist' a été créée avec succès.";

    return true;
}



void Database::removeConnection()
{
    QSqlDatabase::removeDatabase(m_db.connectionName());
}
