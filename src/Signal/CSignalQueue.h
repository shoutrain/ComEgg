#ifndef _C_SIGNAL_QUEUE_H_
#define _C_SIGNAL_QUEUE_H_

#include "CGlobal.h"
#include "CLoopBuffer.h"


class CSignalQueue {
public:
    CSignalQueue(ub_4 size, CMutex *mutex = null_v)
            : _loopBuffer(size, mutex, false_v) {

    }

    TSignal *allocSignal();

    none_   preparedSignal();


    TSignal *readSignal();

    none_ freeSignal();



private:
    CLoopBuffer _loopBuffer;
};

#endif // _C_SIGNAL_QUEUE_H_