#include "token.h"


Token::Token(const QString &text, QString type) : _text(text), _type(type)
{

}

const QString &Token::text() const
{
    return _text;
}

const QString Token::type() const
{
    return _type;
}
const QList<Token> &Token::getTokens() const
{
    return _tokens;
}
