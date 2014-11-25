#include "CInterfaceInfo.h"
#include "CModuleInfo.h"

void CModuleInfo::stop() {
    for (mapInterface::iterator pos = _interfaceInfoMap.begin();
         pos != _interfaceInfoMap.end(); pos++) {
        assert(null_v != pos->second);
        _DEL(pos->second);
    }

    _interfaceInfoMap.clear();
}

b_4 CModuleInfo::addInterface(const ch_1 *name,
        CInterfaceInfo *&interfaceInfo) {
    if (!name || 0 == name[0]) {
        assert(0);
        return 1;
    }

    if (interfaceInfo) {
        assert(0);
        return 2;
    }

    interfaceInfo = new CInterfaceInfo(this, name);
    _interfaceInfoMap.insert(mapInterface::value_type(name, interfaceInfo));

    return 0;
}

CInterfaceInfo *CModuleInfo::getInterface(const ch_1 *name) {
    if (!name || 0 == name[0]) {
        assert(0);
        return null_v;
    }

    mapInterface::iterator pos = _interfaceInfoMap.find(name);

    if (_interfaceInfoMap.end() != pos) {
        assert(null_v != pos->second);
        return pos->second;
    }

    return null_v;
}
