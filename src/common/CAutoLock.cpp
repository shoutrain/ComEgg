#include "CAutoLock.h"

CAutoLock::CAutoLock(CLock *pLock) :
        _pLock(pLock) {
    assert(pLock);
    _pLock->lock();
}

CAutoLock::~CAutoLock() {
    _pLock->unlock();
}

