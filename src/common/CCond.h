#ifndef C_COND_H_
#define C_COND_H_

#include "CLock.h"

#include <pthread.h>

class CMutex;

class CCond: public CLock {
public:
    CCond(CMutex *pMutex);
    virtual ~CCond();

    bool_ lock(bool_ check = false_v);
    none_ unlock();

private:
    pthread_cond_t _cond;
    CMutex *_pMutex;
};

#endif // C_COND_H_
