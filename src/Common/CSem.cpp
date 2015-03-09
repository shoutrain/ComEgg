#include "CSem.h"

#include <sys/errno.h>

CSem::CSem(ub_4 value) {
    if (-1 == sem_init(&_sem, 0, value)) {
        log_fatal("CSem::CSem: failed to call sem_init");
    }
}

CSem::~CSem() {
    if (-1 == sem_destroy(&_sem)) {
        log_fatal("CSem::~CSem: failed to call sem_destroy");
    }
}

bool_ CSem::lock(bool_ check) {
    b_4 ret = 0;

    if (check) {
        ret = sem_trywait(&_sem);
    } else {
        ret = sem_wait(&_sem);
    }

    if (-1 == ret) {
        if (EBUSY == errno && check) {
            return false_v;
        }

        if (check) {
            log_fatal("CSem::lock: failed to call sem_trywait");
        } else {
            log_fatal("CSem::lock: failed to call sem_wait");
        }

        return false_v;
    }

    return true_v;
}

none_ CSem::unlock() {
    if (-1 == sem_post(&_sem)) {
        log_fatal("CSem::unlock: failed to call sem_post");
    }
}
