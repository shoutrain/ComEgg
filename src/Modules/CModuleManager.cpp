#include "CModuleManager.h"
#include "CModuleInfo.h"

CModuleManager *CModuleManager::_instance = null_v;

void CModuleManager::stop() {
    for (mapModule::iterator pos = _moduleMap.begin();
         pos != _moduleMap.end(); pos++) {
        assert(pos->second);
        _DEL(pos->second);
    }

    _moduleMap.clear();
}

b_4 CModuleManager::addModule(const ch_1 *path,
        const ch_1 *name,
        const ch_1 *ext,
        CModuleInfo *&module) {
    if (!path || 0 == path[0]) {
        assert(0);
        return 1;
    }

    if (!name || 0 == name[0]) {
        assert(0);
        return 2;
    }

    if (!ext || 0 == ext[0]) {
        assert(0);
        return 3;
    }

    if (module) {
        assert(0);
        return 4;
    }

    module = new CModuleInfo(path, name, ext);
    _moduleMap.insert(mapModule::value_type(name, module));

    return 0;
}

CModuleInfo *CModuleManager::getModule(const ch_1 *name) {
    if (!name || 0 == name[0]) {
        assert(0);
        return null_v;
    }

    mapModule::iterator pos = _moduleMap.find(name);

    if (_moduleMap.end() != pos) {
        assert(pos->second);
        return pos->second;
    }

    return null_v;
}
