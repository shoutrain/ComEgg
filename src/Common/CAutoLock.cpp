#include "CAutoLock.h"

CAutoLock::CAutoLock(CLock *lock) :
        _lock(lock) {
    if (_lock) {
        _lock->lock();
    }
}

CAutoLock::~CAutoLock() {
    if (_lock) {
        _lock->unlock();
    }
}

