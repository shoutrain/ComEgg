/*!
* \file CSignal.h
* \brief the header file for class of CSignal
*
*
*
* \author Rafael Gu(shoutrain.goo@gmail.com)
* \version 1.0.0
* \date 01/25/2015
*/

#ifndef _C_SIGNAL_H_
#define _C_SIGNAL_H

/// \brief CSignal is used as internal message communication
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

#endif // _C_SIGNAL_H