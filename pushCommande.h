#ifndef PUSHCOMMANDE_H
#define PUSHCOMMANDE_H
#include <Parser.h>

enum class Type {
    WHITELIST,
    BLACKLIST,
    FILTERS,
    SKIPPED_FILTERS
};

class PUSH : public TParser<PUSH> {
public:
    void execute();
};
#endif // PUSHCOMMANDE_H
