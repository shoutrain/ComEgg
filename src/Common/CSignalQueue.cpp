#include "CSignalQueue.h"

#include "CMutex.h"
#include "CSignal.h"

CSignalQueue::CSignalQueue(const ub_4 maxNum, CMutex *mutex) {
    assert(maxNum);
    _signals = new CSignal[maxNum];
    assert(_signals);
    _mutex = mutex;
}

CSignalQueue::~CSignalQueue() {
    _DEL_ARR(_signals);
}

CSignal *CSignalQueue::prepare() {
}

none_ CSignalQueue::send() {

}

CSignal *CSignalQueue::receive() {

}
