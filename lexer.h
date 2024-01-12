#ifndef LEXER_H
#define LEXER_H

#include <QObject>
#include <QMap>
#include <QDebug>
#include "token.h"

class Lexer : public QObject
{
    Q_OBJECT
public:
    Lexer();
    Lexer(QObject *parent );

    QMap<QString, QStringList> _dictionary;

    const QString &source() const;
    void setSource(const QString &newSource);

    const QList<Token *> &tokens() const;

    int current_token_index() const;

public:
    void tokenize();
    void resetTokens();
    QString getType(QString token);
    void loadDialect(QString filename);
    void addToken(QStringList tokens);
    void addTokenString(QString token);
    void addToken(QString token);
   friend QDebug operator<<(QDebug debug, const Lexer &lexer);

signals:
    void sourceChanged();
    void tokenized(int count);
    void current_token_indexChanged(int index);
    void last_token();
    void token_not_ready();

public slots:
    const Token &nextToken();
    void resetToken();
    const Token &getCurrentToken();
public:
    static Lexer *_instance;
    static Lexer* instance();
    QString _source;
    QList<Token *> _tokens;
    int _current_token_index;
};

#endif // LEXER_H
