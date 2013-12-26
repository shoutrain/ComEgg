#include "CMutex.h"

#include <sys/errno.h>

CMutex::CMutex(pthread_mutexattr_t *pAttr) {
    if (0 != pthread_mutex_init(&_mutex, pAttr)) {
        __fatal("CMutex::CMutex: failed to call pthread_mutex_init");
    }
}

CMutex::~CMutex() {
    if (0 != pthread_mutex_destroy(&_mutex)) {
        __fatal("CMutex::~CMutex: failed to call pthread_mutex_destroy");
    }
}

bool_ CMutex::lock(bool_ check) {
    b_4 ret = 0;

    if (check) {
        ret = pthread_mutex_trylock(&_mutex);
    } else {
        ret = pthread_mutex_lock(&_mutex);
    }

    if (EBUSY == ret && check) {
        return false_v;
    }

    if (0 != ret) {
        if (check) {
            __fatal("CMutex::lock: failed to call pthread_mutext_trylock");
        } else {
            __fatal("CMutex::lock: failed to call pthread_mutext_lock");
        }

        return false_v;
    }

    return true_v;
}

void CMutex::unlock() {
    if (0 != pthread_mutex_unlock(&_mutex)) {
        __fatal("CMutex::unlock: failed to call pthread_mutex_unlock");
    }
}

