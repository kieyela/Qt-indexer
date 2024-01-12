#include "indexer.h"
#include <QSqlDatabase>
#include <QDir>
#include <QSqlQuery>
#include <QFile>
#include <QFileInfo>
#include <QStandardPaths>
#include <QSqlError>
#include <QDirIterator>
#include <iomanip>
#include <iostream>
#include <Database.h>

Indexer::Indexer(const QString& path)
    : m_database("testdb.db"), m_indexing(false), m_path(path)

{

}
void Indexer::processIndexingCommand()
{
    if (m_indexing) {
        qDebug() << "Indexing is already in progress.";
        return;
    }

    start();

    qDebug() << "Indexing command processed.";
}
void Indexer::start()
{
    if (!m_indexing) {
        m_indexing = true;
        index();
    } else {
        qDebug() << "Indexing already in progress.";
    }
}

void Indexer::stop()
{
    if (m_indexing) {
        m_indexing = false;
        qDebug() << "Indexing stopped.";
    } else {
        qDebug() << "No indexing in progress.";
    }
}

void Indexer::index()
{
    indexDirectory(QDir(m_path));
}

void Indexer::indexDirectory(const QDir& dir)
{
    QDirIterator it(dir, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        QFileInfo file(it.next());
        if (file.isFile()) {
            this->indexFile(file);
        }
    }
}

void Indexer::indexFile(const QFileInfo& file)
{
    QSqlDatabase db = Database::getDatabaseConnection();
    QSqlQuery query(db);

    query.exec("pragma temp_store = memory");
    query.exec("PRAGMA synchronous = OFF");
    query.exec("pragma mmap_size = 30000000000");
    query.exec("PRAGMA journal_mode = MEMORY");
    db.transaction();
    query.prepare("INSERT INTO files (id, fileName, lastModified, creationDate, fileSize, fileExtension, fileType)"
                  "VALUES (:id, :fileName, :lastModified, :creationDate, :fileSize, :fileExtension, :fileType)");

    for (int i = 0; i <= INSERTS_COUNT; i++) {
        QString sI = QString::number(i);
        if (i % DISPLAY_EVERY == 0)
            std::cout << __FUNCTION__ << " " << i << "/" << INSERTS_COUNT << std::endl;

        query.bindValue(":id", QString(file.absoluteFilePath()));
        query.bindValue(":fileName",QString(file.fileName()));
        query.bindValue(":lastModified", QString(file.lastModified().toString()));
        query.bindValue(":creationDate", QString(file.birthTime().toString()));
        query.bindValue(":fileSize", QString::number(file.size()));
        query.bindValue(":fileExtension", QString(file.suffix()));
        query.bindValue(":fileType", QString("none"));

        query.exec();
    }
    db.commit();
    std::cout << std::setw(func_width) << __FUNCTION__;
}
