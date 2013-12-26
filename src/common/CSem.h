#ifndef C_SEM_H_
#define C_SEM_H_

#include "CLock.h"

#include <semaphore.h>

class CSem: public CLock {
public:
    CSem(ub_4 value = 1);
    virtual ~CSem();

    bool_ lock(bool_ check = false_v);
    void unlock();

    ub_4 getValue();

private:
    sem_t _sem;
};

#endif // C_SEM_H_
