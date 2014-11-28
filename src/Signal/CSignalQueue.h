#ifndef _C_SIGNAL_QUEUE_H_
#define _C_SIGNAL_QUEUE_H_

#include "CGlobal.h"
#include "CLoopBuffer.h"

struct TSignal {
    ub_1 size;
    ub_1 cmd;
};

class CSignalQueue {
public:
    CSignalQueue(ub_4 size, CMutex *mutex = null_v)
            : _loopBuffer(size, mutex, false_v) {

    }

private:
    CLoopBuffer _loopBuffer;
};

#endif // _C_SIGNAL_QUEUE_H_