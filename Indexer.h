#ifndef INDEXER_H
#define INDEXER_H

#include <QSqlDatabase>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include "Database.h"


#define INSERTS_COUNT 10000
#define DISPLAY_EVERY 1000
#define func_width    50

class Indexer
{
public:
    Indexer(const QString& path);

    void index();
    void start();
    void stop();
    void processIndexingCommand();

private:
    Database m_database;
    bool m_indexing;
    QSqlDatabase m_db;
    QString m_path;

    void indexDirectory(const QDir& dir);
    void indexFile(const QFileInfo& file);


};

#endif //
