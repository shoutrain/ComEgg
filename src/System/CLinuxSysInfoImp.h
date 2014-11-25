#ifndef _C_LINUX_SYS_INFO_IMP_H_
#define _C_LINUX_SYS_INFO_IMP_H_

#include "CSysInfoImp.h"
#include <sys/sysinfo.h>

class CLinuxSysInfoImp : public CSysInfoImp {
public:
    bool_ getSysInfo() {
        if (sysinfo(&_sysInfo)) {
            return false_v;
        }

        return true_v;
    }

    virtual ub_1 getMemoryUsage() {
        return (ub_1) (((double) _sysInfo.freeram / (double) _sysInfo.totalram) * 100);
    }

private:
    struct sysinfo _sysInfo;
};

#endif // _C_LINUX_SYS_INFO_IMP_H_
