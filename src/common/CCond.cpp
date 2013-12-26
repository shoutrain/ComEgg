#include "CCond.h"
#include "CMutex.h"

CCond::CCond(CMutex *pMutex) {
    assert(pMutex);
    _pMutex = pMutex;

    if (0 != pthread_cond_init(&_cond, null_v)) {
        __fatal("CCond::CCond: failed to call pthread_cond_init");
    }
}

CCond::~CCond() {
    if (0 != pthread_cond_destroy(&_cond)) {
        __fatal("CCond::~CCond: failed to call pthread_cond_destroy");
    }
}

bool_ CCond::lock(bool_ check) {
    if (0 != pthread_cond_wait(&_cond, _pMutex->get())) {
        __fatal("CCond::lock: failed to call pthread_cond_wait");

        return false_v;
    }

    return true_v;
}

void CCond::unlock() {
    if (0 != pthread_cond_signal(&_cond)) {
        __fatal("CCond::unlock failed to call pthread_cond_signal");
    }
}

