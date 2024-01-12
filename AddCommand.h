#ifndef ADDCOMMAND_H
#define ADDCOMMAND_H

#include "token.h"
#include "Parser.h"
#include <QString>

enum class Options {
    WHITELIST,
    BLACKLIST,
    FILTERS,
    SKIPPED_FILTERS
};

class ADD : public TParser<ADD> {
public:
    ADD() : TParser<ADD>(){}
    ADD(QString path, Options option);



};

#endif // ADDCOMMAND_H
