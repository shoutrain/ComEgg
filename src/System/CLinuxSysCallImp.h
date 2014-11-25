#ifndef _C_LINUX_SYS_CALL_IMP_H_
#define _C_LINUX_SYS_CALL_IMP_H_

#include "CSysCallImp.h"

#include <stdlib.h>
#include <stdio.h>

class CLinuxSysCallImp : CSysCallImp {
public:
    virtual bool_ exec(const ch_1 *command) {
        char localCommand[1024] = {0};

        sprintf(localCommand, "%s&", command);

        b_4 ret = system(localCommand);

        if (-1 == ret || 127 == ret) {
            return false_v;
        }

        return true_v;
    }
};

#endif // _C_LINUX_SYS_CALL_IMP_H_
