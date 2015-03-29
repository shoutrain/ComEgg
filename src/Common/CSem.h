/*!
* \file CCond.h
* \brief The encapsulation class for semaphore
*
*
*
* \author Rafael Gu(shoutrain.goo@gmail.com)
* \version 1.0.0
* \date 02/15/2015
*/

#ifndef SRC_COMMON_CSEM_H_
#define SRC_COMMON_CSEM_H_

#include "CLock.h"

#include <semaphore.h>

class CSem : public CLock {
public:
    CSem(ub_4 value = 1);

    virtual ~CSem();

    bool_ lock(bool_ check = false_v);

    none_ unlock();

private:
    sem_t _sem;
};

#endif /* SRC_COMMON_CSEM_H_ */
