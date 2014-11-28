#include "CProtocolManager.h"
#include "CProtocolInfo.h"

CProtocolManager *CProtocolManager::_instance = null_v;

none_ CProtocolManager::stop() {
    for (MapProtocol::iterator pos = _protocolMap.begin();
         pos != _protocolMap.end(); pos++) {
        assert(pos->second);
        _DEL(pos->second);
    }

    _protocolMap.clear();
}

none_ CProtocolManager::addProtocol(const ch_1 *name, CProtocolInfo *&protocolInfo) {
    assert(name && 0 != name && !protocolInfo);

    protocolInfo = new CProtocolInfo();
    _protocolMap.insert(MapProtocol::value_type(name, protocolInfo));
}

CProtocolInfo *CProtocolManager::getProtocol(const ch_1 *name) {
    assert(name && 0 != name[0]);

    MapProtocol::iterator pos = _protocolMap.find(name);

    if (_protocolMap.end() != pos) {
        assert(pos->second);
        return pos->second;
    }

    return pos->second;
}
