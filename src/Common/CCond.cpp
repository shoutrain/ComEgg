#include "CCond.h"
#include "CMutex.h"

CCond::CCond(CMutex *mutex) {
    assert(mutex);
    _mutex = mutex;

    if (0 != pthread_cond_init(&_cond, null_v)) {
        logFatal("CCond::CCond: failed to call pthread_cond_init");
    }
}

CCond::~CCond() {
    if (0 != pthread_cond_destroy(&_cond)) {
        logFatal("CCond::~CCond: failed to call pthread_cond_destroy");
    }
}

bool_ CCond::lock(bool_ check) {
    if (0 != pthread_cond_wait(&_cond, _mutex->getMutex())) {
        logFatal("CCond::lock: failed to call pthread_cond_wait");

        return false_v;
    }

    return true_v;
}

void CCond::unlock() {
    if (0 != pthread_cond_signal(&_cond)) {
        logFatal("CCond::unlock failed to call pthread_cond_signal");
    }
}

