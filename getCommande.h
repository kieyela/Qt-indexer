#ifndef GETCOMMANDE_H
#define GETCOMMANDE_H
#include <Parser.h>

enum class TypeLists {
    WHITELIST,
    BLACKLIST,
    FILTERS,
    SKIPPED_FILTERS
};

class GET : public TParser<GET> {
public:
    void execute();
};
#endif // GETCOMMANDE_H
