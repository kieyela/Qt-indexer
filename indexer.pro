QT = core sql

CONFIG += c++17 cmdline console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        AddCommand.cpp \
        CommandHandler.cpp \
        Database.cpp \
        Debug.cpp \
        Indexer.cpp \
        Lexer.cpp \
        Parser.cpp \
        main.cpp \
        parserExeption.cpp \
        parserFactory.cpp \
        token.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    AddCommand.h \
    CommandHandler.h \
    Database.h \
    Debug.h \
    Indexer.h \
    Lexer.h \
    Parser.h \
    ParserFactory.h \
    getCommande.h \
    parserExeption.h \
    pushCommande.h \
    token.h