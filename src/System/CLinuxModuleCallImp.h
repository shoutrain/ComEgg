#ifndef _C_LINUX_MODULE_CALL_IMP_H_
#define _C_LINUX_MODULE_CALL_IMP_H_

#include "../Common/CGlobal.h"
#include "CModuleCallImp.h"

class CLinuxModuleCallImp : public CModuleCallImp {
public:
    CLinuxModuleCallImp() : _handle(null_v) {
    }

    virtual ~CLinuxModuleCallImp() {
        close();
    }

    virtual bool_ open(const ch_1 *modulePath,
            const ch_1 *moduleName,
            const ch_1 *moduleType);

    virtual bool_ close();

    virtual bool_ call(const ch_1 *interfaceName,
            const ub_1 *in,
            size_ inSize,
            ub_1 *&out,
            size_ &outSize);

private:
    obj_ _handle;
};

#endif // CLINUX_MODULE_CALL_IMP_H
