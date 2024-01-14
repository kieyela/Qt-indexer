#include "cmd_factory.h"
#include "Indexer.h"
#include <QCoreApplication>
#include <QDebug>
#include <QMap>
#include <QString>
#include "QSqlDatabase"
#include "QSqlQuery"
#include <QSqlError>


static QString checkAndGetFolderType(Token token)
{
    qDebug()<<token.type();
    if(token.type() == "IDENTIFIER")
    {
        return token.text().toLower();
    }
    else // error
    {
        qWarning() << __FUNCTION__ << "Bad type file";
        // throw exception
        return NULL;
    }
}

static void executeCommand(QString request)
{
    QSqlDatabase db = Database ::getDatabaseConnection();

    QSqlQuery query(db);

    qDebug() << request;

    if (!query.exec(request)) {
        qDebug() << "Erreur lors de l'exécution de la requête merci :" << query.lastError().text();
    }

    // Test if values are insert
//    if(query.exec("SELECT * FROM " + this->folderType)) {
//        while (query.next()) {
//            qDebug() << query.value("folderPath");
//        }
//    }

    db.close();
}


CommandeSearch::CommandeSearch() {}

void CommandeSearch::parse(QList<Token *> tokens) {
    qDebug() << __FUNCTION__ << "on SEARCH";
    // TODO call state chart like this -> stateChart(this)

}

void CommandeSearch::run() {
    qDebug() << __FUNCTION__ << "on SEARCH";
}

/** END CmdSearch **/

/** CmdGet class **/

CommandeGet::CommandeGet() {}

void CommandeGet::parse(QList<Token *> tokens) {
    qDebug() << __FUNCTION__ << "on GET" << tokens[1]->text();

    // complete the data
    this->folderType = checkAndGetFolderType(*tokens[1]);

    // then run
    this->run();
}

void CommandeGet::run() {
    qDebug() << __FUNCTION__ << "on GET ";
    // create request
    QString command = "SELECT * FROM " + this->folderType;

    executeCommand(command);

}

/** END CmdGet **/

/** CmdAdd class **/

CommandeAdd::CommandeAdd() {}

void CommandeAdd::parse(QList<Token *> tokens) {
    //qDebug() << __FUNCTION__ << "on ADD";

    // complete the data
    this->folderType = checkAndGetFolderType(*tokens[1]);
    this->folderPath = tokens[2]->text();

    // then run
    this->run();
}


void CommandeAdd::run() {
    qDebug() << __FUNCTION__ << "on ADD class";

    // create request
    QString command = "INSERT INTO " + this->folderType + " (folderPath) VALUES ('" + this->folderPath + "')";

    executeCommand(command);
}

/** END CmdAdd **/

/** CmdClear class **/

CommandeClear::CommandeClear() {}

void CommandeClear::parse(QList<Token *> tokens) {
    qDebug() << __FUNCTION__ << "on CLEAR" << tokens[1]->text();

    // complete the data
    this->folderType = checkAndGetFolderType(*tokens[1]);

    // then run
    this->run();
}

void CommandeClear::run() {
    qDebug() << __FUNCTION__ << "on CLEAR ";
    // create request
    QString command = "DELETE FROM " + this->folderType;

    executeCommand(command);

}
