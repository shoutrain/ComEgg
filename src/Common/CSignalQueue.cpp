#include "CSignalQueue.h"

#include "CMutex.h"
#include "CAutoLock.h"
#include "CSignal.h"

CSignalQueue::CSignalQueue(const ub_4 maxNum, CMutex *mutex)
        : _totalNum(maxNum), _res(maxNum, this, mutex) {
    assert(maxNum);
    _mutex = mutex;
}

CSignalQueue::~CSignalQueue() {
}

CSignal *CSignalQueue::prepare() {
    CSignal *signal = _res.allocate();

    if (null_v == signal) {
        logCrit("There is no more signal resource for signal queue");
    }

    return signal;
}

none_ CSignalQueue::send(const CSignal *signal) {
    assert(signal);
    CAutoLock al(_mutex);

    _queue.push(signal);
}

CSignal *CSignalQueue::receive() {
    CAutoLock al(_mutex);

    CSignal *signal = _queue.front();

    if (null_v != signal) {
        _queue.pop();

        return signal;
    }

    return null_v;
}

none_ CSignalQueue::complete(const CSignal *signal) {
    assert(signal);
    if (false_v == _res.reclaim(signal)) {
        assert(false_v);
    }
}
