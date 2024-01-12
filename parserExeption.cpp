#include "parserExeption.h"

ParserException::ParserException(QString msg) : m_msg(msg) {}

QString ParserException::msg() const {
    return m_msg;
}

void ParserException::setMsg(const QString &msg) {
    m_msg = msg;
}
