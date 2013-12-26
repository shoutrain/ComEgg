#ifndef C_MUTEX_H_
#define C_MUTEX_H_

#include "CLock.h"

#include <pthread.h>

class CMutex: public CLock {
public:
    CMutex(pthread_mutexattr_t *pAttr = null_v);
    virtual ~CMutex();

    bool_ lock(bool_ check = false_v);
    void unlock();

    pthread_mutex_t *get() {
        return &_mutex;
    }

private:
    pthread_mutex_t _mutex;
};

#endif // C_MUTEX_H_
