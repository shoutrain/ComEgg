/*!
* \file CMutex.h
* \brief The encapsulation class for mutex
*
*
*
* \author Rafael Gu(shoutrain.goo@gmail.com)
* \version 1.1.0
* \date 03/23/2015
*/

#ifndef SRC_COMMON_CMUTEX_H_
#define SRC_COMMON_CMUTEX_H_

#include "CLock.h"

#include <pthread.h>

class CMutex : public CLock {
public:
    CMutex(bool_ recursive = false_v);

    virtual ~CMutex();

    bool_ lock(bool_ check = false_v);

    none_ unlock();

    pthread_mutex_t *getMutex() {
        return &_mutex;
    }

private:
    pthread_mutex_t _mutex;
};

#endif /* SRC_COMMON_CMUTEX_H_ */
