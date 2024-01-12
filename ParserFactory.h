#ifndef PARSERFACTORY_H
#define PARSERFACTORY_H
#include <QString>
#include <parser.h>

class ParserFactory {
    QMap<QString, CreateParserFn> m_factoryMap;
    QList<Parser *> parserList;

public:
    ~ParserFactory();
    ParserFactory();

   void Register(QString parserName, CreateParserFn fn);
   Parser *create(QString parserName);
   operator QString() const;
};


#endif // PARSERFACTORY_H
