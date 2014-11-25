#ifndef _C_SYS_CALL_H_
#define _C_SYS_CALL_H_

#include "CSysFactory.h"

class CSysCall {
public:
    CSysCall() {
        _sysCall = CSysFactory::instance()->makeSysCall();
    }

    virtual ~CSysCall() {
        _DEL(_sysCall);
    }

    bool_ exec(const ch_1 *command) {
        return _sysCall->exec(command);
    }

private:
    CSysCallImp *_sysCall;
};

#endif // _C_SYS_CALL_H_
