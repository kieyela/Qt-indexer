#ifndef PARSER_H
#define PARSER_H
#include <QString>
#include <QDebug>

class Parser {
    QString _name;
    QString _type;

public:
    Parser();
    virtual ~Parser();

    virtual QString name() const;
    virtual void setName(const QString& name);
    //virtual void execute();

    QString type() const;
    void setType(const QString& type);
};

typedef Parser *(*CreateParserFn)();
template <class T>
class TParser : public Parser {
public:
    static Parser *create(){
        qDebug() << __FUNCTION__;
        return new T;
    }

};

#endif // PARSER_H
