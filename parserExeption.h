#ifndef PARSEREXEPTION_H
#define PARSEREXEPTION_H
#include <QString>

class ParserException {
    QString m_msg;

public:
    ParserException(QString msg);
    QString msg() const;
    void setMsg(const QString &msg);
};
#endif // PARSEREXEPTION_H
