#include "CInterfaceInfo.h"
#include "CModuleInfo.h"

none_ CModuleInfo::stop() {
    for (mapInterface::iterator pos = _interfaceInfoMap.begin();
         pos != _interfaceInfoMap.end(); pos++) {
        assert(null_v != pos->second);
        _DEL(pos->second);
    }

    _interfaceInfoMap.clear();
}

none_ CModuleInfo::addInterface(const ch_1 *name,
        CInterfaceInfo *&interfaceInfo) {
    assert(name && 0 != name[0]);
    assert(!interfaceInfo);

    interfaceInfo = new CInterfaceInfo(this, name);
    _interfaceInfoMap.insert(mapInterface::value_type(name, interfaceInfo));
}

CInterfaceInfo *CModuleInfo::getInterface(const ch_1 *name) {
    assert(name && 0 != name[0]);

    mapInterface::iterator pos = _interfaceInfoMap.find(name);

    if (_interfaceInfoMap.end() != pos) {
        assert(pos->second);
        return pos->second;
    }

    return null_v;
}
