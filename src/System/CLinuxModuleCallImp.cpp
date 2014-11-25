#include "CLinuxModuleCallImp.h"
#include "../Modules/ModuleCommon.h"

#include <dlfcn.h>

bool_ CLinuxModuleCallImp::open(const ch_1 *modulePath,
        const ch_1 *moduleName,
        const ch_1 *moduleType) {
    if ((!modulePath || 0 == modulePath[0]
            || MODULE_PATH_LENGTH <= strlen(modulePath))
            ||
            (!moduleName || 0 == moduleName[0]
                    || MODULE_NAME_LENGTH <= strlen(moduleName))
                    ||
            (!moduleType || 0 == moduleType[0]
                    || MODULE_EXT_LENGTH <= strlen(moduleType))) {
        return false_v;
    }


    size_ length = MODULE_PATH_LENGTH
            + MODULE_NAME_LENGTH
            + MODULE_EXT_LENGTH;
    ch_1  module[length];

    memset(module, 0, length);
    sprintf(module, "%s/lib%s.%s", modulePath, moduleName, moduleType);

    _handle = dlopen(module, RTLD_NOW);

    if (!_handle) {
        return false_v;
    }

    return true_v;
}

bool_ CLinuxModuleCallImp::close() {
    if (_handle) {
        dlclose(_handle);
        _handle = null_v;
    }

    return true_v;
}

bool_ CLinuxModuleCallImp::call(const ch_1 *interfaceName,
        const ub_1 *in,
        size_ inSize,
        ub_1 *&out,
        size_ &outSize) {
    if (!interfaceName
            || 0 == interfaceName[0]
            || INTERFACE_NAME_LEGNTH <= strlen(interfaceName)) {
        return false_v;
    }

    if (out) {
        return false_v;
    }

    if (!_handle) {
        return false_v;
    }

    void (*callFun)(const ub_1 *, size_, ub_1 *&, size_ &);

    callFun = (void (*)(const ub_1 *, size_, ub_1 *&, size_ &))
            dlsym(_handle, interfaceName);

    const ch_1 *errMsg = dlerror();

    if (NULL != errMsg) {
        return false_v;
    }

    callFun(in, inSize, out, outSize);

    return true_v;
}
