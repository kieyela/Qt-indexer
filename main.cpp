#include <QCoreApplication>
#include "Lexer.h"
#include "Indexer.h"
#include "cmd_factory.h"

#include <QDebug>
#include <QString>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Database m_database = Database("testdb.db");
    m_database.getDatabaseConnection();

    //Indexer indexer("C:/TP_YNOV");
    //indexer.processIndexingCommand();

    bool test = false;
    bool in = true;
    Lexer lexer;
    lexer.loadDialect("C:/Users/Querido/Documents/indexer/dico.json");

     CommandeFactory *factory = new CommandeFactory;

     while(!test)
     {
        QString input = in ? QLatin1String("ADD WHITELIST myster") : QLatin1String("CLEAR WHITELIST");

        lexer.setSource(input);

        foreach (auto token, lexer.tokens())
        {
            auto tok = &token;
            qDebug() << "donne moi le token :" << tok;
            qDebug() << "donne moi le texte :" << token->text();
            qDebug() << "donne moi le type :" <<token->type();
        }

        QString s = lexer.tokens()[0]->text();

        if(s == "ADD")
        {
            Commande *command = factory->create("CmdAdd");
            command->parse(lexer.tokens());
            in = false;
        }
        else if(s == "GET")
        {
            Commande *command = factory->create("CmdGet");
            command->parse(lexer.tokens());
            test = true;
        }
        else if(s == "CLEAR")
        {
            Commande *command = factory->create("CmdClear");
            command->parse(lexer.tokens());
            test = true;
        }
        else if(s == "SEARCH")
        {
            Commande *command = factory->create("CmdSearch");
            command->parse(lexer.tokens());
        }
     }
    return a.exec();


}
