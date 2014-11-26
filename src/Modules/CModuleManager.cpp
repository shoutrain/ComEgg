#include "CModuleManager.h"
#include "CModuleInfo.h"

CModuleManager *CModuleManager::_instance = null_v;

none_ CModuleManager::stop() {
    for (mapModule::iterator pos = _moduleMap.begin();
         pos != _moduleMap.end(); pos++) {
        assert(pos->second);
        _DEL(pos->second);
    }

    _moduleMap.clear();
}

none_ CModuleManager::addModule(const ch_1 *path,
        const ch_1 *name,
        const ch_1 *ext,
        CModuleInfo *&module) {
    assert(path && 0 != path[0]);
    assert(name && 0 != name[0]);
    assert(ext && 0 != ext[0]);
    assert(!module);

    module = new CModuleInfo(path, name, ext);
    _moduleMap.insert(mapModule::value_type(name, module));
}

CModuleInfo *CModuleManager::getModule(const ch_1 *name) {
    assert(name && 0 != name[0]);

    mapModule::iterator pos = _moduleMap.find(name);

    if (_moduleMap.end() != pos) {
        assert(pos->second);
        return pos->second;
    }

    return null_v;
}
