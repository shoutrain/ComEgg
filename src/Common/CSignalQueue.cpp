#include "CSignalQueue.h"

#include "CMutex.h"
#include "CSignal.h"

CSignalQueue::CSignalQueue(const ub_4 maxNum, CMutex *mutex) {
    assert(maxNum);
    _maxNum          = maxNum;
    _signals         = new CSignal[_maxNum];
    assert(_signals);
    _mutex = mutex;
    _curPreparedItem = null_v;
    _queueHead       = _queueTail = null_v;
}

CSignalQueue::~CSignalQueue() {
    _DEL_ARR(_signals);
}

CSignal *CSignalQueue::prepare() {
    ub_4 index = 0;

    for (; index < _maxNum; index++) {
        if (!_signals[index].isUsed()) {
            if (_mutex) {
                _mutex->lock();
            }

            _curPreparedItem = &_signals[index];
            _curPreparedItem->use(true_v);

            return &_signals[index];
        }
    }

    return null_v;
}

none_ CSignalQueue::send() {
    if (_mutex) {
        _mutex->unlock();
    }
}

CSignal *CSignalQueue::receive() {

}
