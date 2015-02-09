/*!
* \file CSignal.h
* \brief the header file for class of CSignal
*
*
*
* \author Rafael Gu(shoutrain.goo@gmail.com)
* \version 1.0.0
* \date 02/09/2015
*/

#ifndef _C_SIGNAL_H_
#define _C_SIGNAL_H_

#include "CGlobal.h"

/// \brief CSignal is used as an internal message for communication
class CSignal {
public:
    CSignal();

    virtual ~CSignal();

    none_ use(bool_ used) {
        _used = used;
    }

    bool_ isUsed() {
        return _used;
    }

private:
    bool_ _used;
};

#endif // _C_SIGNAL_H_