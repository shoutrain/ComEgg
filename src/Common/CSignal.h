/*!
* \file CSignal.h
* \brief the header file for class of CSignal
*
*
*
* \author Rafael Gu(shoutrain.goo@gmail.com)
* \version 1.0.0
* \date 02/18/2015
*/

#ifndef SRC_COMMON_CSIGNAL_H_
#define SRC_COMMON_CSIGNAL_H_

#include "CGlobal.h"

/// \brief CSignal is used as an internal message for communication
class CSignal : CGlobal {
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

    ub_4 _commandId;

};

#endif /* SRC_COMMON_CSIGNAL_H_ */
