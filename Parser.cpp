#include "parser.h"

Parser::Parser() {}

Parser::~Parser() {}

QString Parser::name() const {
    return _name;
}

void Parser::setName(const QString& name) {
    _name = name;
}

QString Parser::type() const {
    return _type;
}

void Parser::setType(const QString& type) {
    _type = type;
}
