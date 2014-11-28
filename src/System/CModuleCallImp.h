#ifndef _C_MODULE_CALL_IMP_H_
#define _C_MODULE_CALL_IMP_H_

#include "../Common/CGlobal.h"

class CModuleCallImp {
public:
    virtual bool_ open(const ch_1 *modulePath,
            const ch_1 *moduleName,
            const ch_1 *moduleType) = 0;

    virtual bool_ close() = 0;

    virtual bool_ call(const ch_1 *interfaceName,
            const ub_1 *in,
            size_ inSize,
            ub_1 *&out,
            size_ &outSize) = 0;
};

#endif // _C_MODULE_CALL_IMP_H_
