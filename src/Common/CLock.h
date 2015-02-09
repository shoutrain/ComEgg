/*!
* \file CLock.h
* \brief the interface class for all locks
*
*
*
* \author Rafael Gu(shoutrain.goo@gmail.com)
* \version 1.0.0
* \date 02/09/2015
*/

#ifndef _C_LOCK_H_
#define _C_LOCK_H_

#include "CGlobal.h"

/// \brief CSignal is used as an internal message for communication
class CLock {
public:
    virtual bool_ lock(bool_ bCheck = false_v) = 0;

    virtual none_ unlock() = 0;

protected:
    CLock() {
    }

    virtual ~CLock() {
    }
};

#endif // _C_LOCK_H_
