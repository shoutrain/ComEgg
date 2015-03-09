#include "CCond.h"
#include "CMutex.h"

CCond::CCond(CMutex *mutex) {
    assert(mutex);
    _mutex = mutex;

    if (0 != pthread_cond_init(&_cond, null_v)) {
        log_fatal("CCond::CCond: failed to call pthread_cond_init");
    }
}

CCond::~CCond() {
    if (0 != pthread_cond_destroy(&_cond)) {
        log_fatal("CCond::~CCond: failed to call pthread_cond_destroy");
    }
}

bool_ CCond::lock(bool_ check) {
    if (0 != pthread_cond_wait(&_cond, _mutex->getMutex())) {
        log_fatal("CCond::lock: failed to call pthread_cond_wait");

        return false_v;
    }

    return true_v;
}

none_ CCond::unlock() {
    if (0 != pthread_cond_signal(&_cond)) {
        log_fatal("CCond::unlock failed to call pthread_cond_signal");
    }
}

