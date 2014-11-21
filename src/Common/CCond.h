#ifndef _C_COND_H_
#define _C_COND_H_

#include "CLock.h"

#include <pthread.h>

class CMutex;

class CCond : public CLock {
public:
    CCond(CMutex *mutex);

    virtual ~CCond();

    bool_ lock(bool_ check = false_v);

    void unlock();

private:
    pthread_cond_t _cond;
    CMutex *_mutex;
};

#endif // _C_COND_H_
