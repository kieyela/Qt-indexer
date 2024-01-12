#include <QCoreApplication>
#include "Lexer.h"
#include "Indexer.h"
//#include "CommandHandler.h"
#include "ParserFactory.h"

#include <QDebug>
#include <QString>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Database m_database = Database("testdb.db");
    m_database.getDatabaseConnection();

    Indexer indexer("C:/TP_YNOV");
    indexer.processIndexingCommand();

    Lexer lexer;
    lexer.loadDialect("C:/Users/Querido/Documents/indexer/dico.json");
    QString input = QLatin1String("ADD");
    lexer.setSource(input);
    foreach (auto token, lexer.tokens())
    {
        auto tok = &token;
        qDebug() << "donne moi le token :" << tok;
        qDebug() << "donne moi le texte :" << token->text();
        qDebug() << "donne moi le type :" <<token->type();
    }
    qDebug() << lexer;
//    CommandHandler commandHandler(indexer);
//    commandHandler.processCommand("ADD");

    ParserFactory *factory = new ParserFactory;
    Parser *add = factory->create("ADD");

    return a.exec();


}
