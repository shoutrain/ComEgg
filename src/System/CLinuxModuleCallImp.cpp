#include "CLinuxModuleCallImp.h"
#include "../Modules/ModuleCommon.h"

#include <dlfcn.h>

bool_ CLinuxModuleCallImp::open(const ch_1 *modulePath,
        const ch_1 *moduleName,
        const ch_1 *moduleType) {
    assert(modulePath && 0 != modulePath[0]
            && MODULE_PATH_LENGTH > strlen(modulePath));
    assert(moduleName && 0 != moduleName[0]
            && MODULE_NAME_LENGTH > strlen(moduleName));
    assert(moduleType && 0 != moduleType[0]
            && MODULE_EXT_LENGTH > strlen(moduleType));

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
    assert(interfaceName
            && 0 != interfaceName[0]
            && INTERFACE_NAME_LEGNTH > strlen(interfaceName));
    assert(!out);

    if (!_handle) {
        return false_v;
    }

    none_ (*callFun)(const ub_1 *, size_, ub_1 *&, size_ &);

    callFun = (none_ (*)(const ub_1 *, size_, ub_1 *&, size_ &))
            dlsym(_handle, interfaceName);

    const ch_1 *errMsg = dlerror();

    if (null_v != errMsg) {
        return false_v;
    }

    callFun(in, inSize, out, outSize);

    return true_v;
}
