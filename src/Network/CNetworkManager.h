#ifndef _C_NETWORK_MANAGER_H_
#define _C_NETWORK_MANAGER_H_

#include "CAcceptor.h"
#include "CConnector.h"
#include "CReactor.h"

#include <string>
#include <map>

using namespace std;

typedef map<string, CNode *>    MapNode;
typedef map<string, CReactor *> MapReactor;

class CNetworkManager {
public:
    static CNetworkManager *instance() {
        if (_instance) {
            return _instance;
        }

        _instance = new CNetworkManager;

        return _instance;
    }

    static none_ destroy() {
        _DEL(_instance);
    }

    none_ addReactor(const ch_1 *name, const CReactor *reactor);

    CReactor *getReactor(const ch_1 *name) {
        MapReactor::iterator pos = _reactorMap.find(name);

        if (_reactorMap.end() != pos) {
            assert(pos->second);
            return pos->second;
        }

        return null_v;
    }

    none_ addNode(const ch_1 *name, const CNode *node);

    CNode *getNode(const ch_1 *name) {
        MapNode::iterator pos = _nodeMap.find(name);

        if (_nodeMap.end() != pos) {
            assert(pos->second);
            return pos->second;
        }

        return null_v;
    }

    none_ work();

    none_ exit();

private:
    CNetworkManager() {
    }

    CNetworkManager(const CNetworkManager &);

    const CNetworkManager &operator=(const CNetworkManager &);

    virtual ~CNetworkManager() {
    }

    MapNode    _nodeMap;
    MapReactor _reactorMap;

    static CNetworkManager *_instance;
};

#endif // _C_NETWORK_MANAGER_H_
