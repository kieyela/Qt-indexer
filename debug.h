#ifndef DEBUG_H
#define DEBUG_H
#include <QDebug>
#include "token.h"

// set this to 1 to log fiunction / lines
#define DEBUG_FUNCTIONS 1
#define APP_VERSION "1"
#define GIT_VERSION 1

#if DEBUG_FUNCTIONS
#define LOGGING_MESSAGE_PATTERN                                                                                              \
"%{time hh:mm:ss.zzz} "                                                                                                  \
    "%{if-category}%{category}.%{endif}"                                                                                     \
    "%{if-debug}DBG%{endif}"                                                                                                 \
    "%{if-info}INF%{endif}"                                                                                                  \
    "%{if-warning}WRN%{endif}"                                                                                               \
    "%{if-critical}CRT%{endif}"                                                                                              \
    "%{if-fatal}FTL%{endif} "                                                                                                \
    "%{message} - %{file}@%{line} - %{function}"
#else
#define LOGGING_MESSAGE_PATTERN                                                                                              \
"%{time hh:mm:ss.zzz} "                                                                                                  \
    "%{if-category}%{category}.%{endif}"                                                                                     \
    "%{if-debug}DBG%{endif}"                                                                                                 \
    "%{if-info}INF%{endif}"                                                                                                  \
    "%{if-warning}WRN%{endif}"                                                                                               \
    "%{if-critical}CRT%{endif}"                                                                                              \
    "%{if-fatal}FTL%{endif} "                                                                                                \
    "%{message}"
#endif

    // clang-format off

void    myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg);

void    initDebug();

QString loadLoggingRules(QString filename);

void    logAppInfo();
// clang-format on

QDebug operator<<(QDebug debug, const Token &token) {
    QDebugStateSaver saver(debug);
    debug.nospace() << "[Token: Value=" << token.text() << ", Type=" << token.type() << "]";
    return debug;
}

#endif // DEBUG_H
