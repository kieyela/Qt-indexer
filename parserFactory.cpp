#include "ParserFactory.h"
#include "parserExeption.h"
#include "pushCommande.h"
#include "AddCommand.h"
#include "getCommande.h"

#include <QString>
#define STR_PTR(ptr) QString("0x%1").arg(reinterpret_cast<quintptr>(ptr), QT_POINTER_SIZE * 2, 16, QChar('0'))

ParserFactory::~ParserFactory() {
    foreach (auto parser, parserList) {
        delete parser;
    }
}

ParserFactory::ParserFactory() {
    qDebug() << __FUNCTION__;
    Register("ADD", &ADD::create);
    Register("PUSH", &PUSH::create);
    Register("GET", &GET::create);
}

void ParserFactory::Register(QString parserName, CreateParserFn fn) {
    qDebug() << __FUNCTION__ << parserName << fn;
    m_factoryMap[parserName] = fn;
}

Parser *ParserFactory::create(QString parserName) {
    qDebug() << __FUNCTION__ << parserName;

    CreateParserFn fn = m_factoryMap[parserName];
    if (fn == nullptr) {
        throw ParserException("Unable to create " + parserName);
    }

    Parser *parser = fn();
    parser->setType(parserName);
    parser->setName(QString(parserName + " #%1").arg(parserList.size()));
    parserList.append(parser);

    return parser;
}

ParserFactory::operator QString() const {
    QString ret;
    ret += "ACTIONS MAP:\n";
    foreach (auto key, m_factoryMap.keys()) {
        ret += " > " + key + ": " + STR_PTR(m_factoryMap[key]);
        ret += '\n';
    }

    ret += "Parser LIST:\n";
    foreach (auto parser, parserList) {
        ret += " > " + parser->type() + ": " + parser->name();
        ret += '\n';
    }

    return ret;
}
