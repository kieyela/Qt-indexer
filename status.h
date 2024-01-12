#ifndef STATUS_H
#define STATUS_H

#include <QObject>

enum Status
{
    indexing,
    ready,
    stopped,
    paused,
    querying,
    result_available


};

#endif // STATUS_H
