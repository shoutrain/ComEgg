#include "CSignalQueue.h"

#include "CSignal.h"

CSignalQueue::CSignalQueue(const ub_4 maxNum, CMutex *mutex) {
    assert(maxNum);
    _signals = new CSignal[maxNum];
    assert(_signals);
    _mutex = mutex;
}

CSignalQueue::~CSignalQueue() {

}

CSignal *CSignalQueue::prepare() {

}

CSignal *CSignalQueue::receive() {

}

none_ CSignalQueue::send() {

}