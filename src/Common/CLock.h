/*!
* \file CLock.h
* \brief The interface class for all locks.
*
*
*
* \author Rafael Gu(shoutrain.goo@gmail.com)
* \version 1.0.0
* \date 02/15/2015
*/

#ifndef _C_LOCK_H_
#define _C_LOCK_H_

#include "CGlobal.h"

class CLock : CGlobal {
public:
    /// \brief Lock the lock and then block the thread until the corresponding
    /// locker is available.
    ///
    /// \param check This function will check if the locker is available and not
    /// be blocked and return soon if check is true_v; It's a normal block-able
    /// locker if check is false_v.
    /// \return true_v for successful and false_v for failed.
    virtual bool_ lock(bool_ check = false_v) = 0;

    /// \brief Unlock the locker
    virtual none_ unlock() = 0;

protected:
    CLock() {
    }

    virtual ~CLock() {
    }
};

#endif // _C_LOCK_H_
