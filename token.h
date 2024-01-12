#ifndef TOKEN_H
#define TOKEN_H

#include <QObject>

class Token
{
public:
    Token(const QString &text, QString type);

    const QString &text() const;
    const QString type() const;
    const QList<Token> &getTokens() const;

private:
    QString _text;
    QString _type;
    QList<Token> _tokens;
};

#endif // TOKEN_H
