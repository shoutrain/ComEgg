#ifndef _C_MODULE_CALL_H_
#define _C_MODULE_CALL_H_

#include "CSysFactory.h"

class CModuleCall {
public:
    CModuleCall() {
        _moduleCall = CSysFactory::instance()->makeModuleCall();
    }

    virtual ~CModuleCall() {
        _DEL(_moduleCall);
    }

    bool_ call(const ch_1 *modulePath,
            const ch_1 *moduleName,
            const ch_1 *moduleType,
            const ch_1 *interfaceName,
            const ub_1 *in,
            size_ inSize,
            ub_1 *&out,
            size_ &outSize) {
        if (!_moduleCall->open(modulePath, moduleName, moduleType)) {
            return false_v;
        }

        if (!_moduleCall->call(interfaceName, in, inSize, out, outSize)) {
            _moduleCall->close();

            return false_v;
        }

        return _moduleCall->close();
    }

private:
    CModuleCallImp *_moduleCall;
};

#endif // _C_MODULE_CALL_H_
