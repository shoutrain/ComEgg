#ifndef _C_PROTOCOL_MANAGER_H_
#define _C_PROTOCOL_MANAGER_H_

#include "ProtocolCommon.h"

#include <string>
#include <map>

using namespace std;

class CProtocolInfo;

typedef map<string, CProtocolInfo *> MapProtocol;

class CProtocolManager : public CBase {
public:
    static CProtocolManager *instance() {
        if (_instance) {
            return _instance;
        }

        _instance = new CProtocolManager;

        return _instance;
    }

    static none_ destroy() {
        _DEL(_instance);
    }

    none_ addProtocol(const ch_1 *name, CProtocolInfo *&protocolInfo);

    CProtocolInfo *getProtocol(const ch_1 *pszName);

    bool_ isProtocolReady(const ch_1 *name) {
        assert(name && 0 != name[0]);

        if (_protocolMap.end() != _protocolMap.find(name)) {
            return true_v;
        }

        return false_v;
    }

protected:
    none_ stop();

private:
    CProtocolManager() {
    }

    CProtocolManager(const CProtocolManager &);

    const CProtocolManager &operator=(const CProtocolManager &);

    virtual ~CProtocolManager() {
        stop();
    }

    MapProtocol _protocolMap;

    static CProtocolManager *_instance;
};

#endif // _C_PROTOCOL_MANAGER_H_
