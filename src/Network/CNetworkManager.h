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

class CNetworkManager : public CBase
{
public:
    static CNetworkManager *instance()
	{
        if (_instance) {
            return _instance;
        }

        _instance = new CNetworkManager;

        return _instance;
	}

    static none_ destroy()
	{
        _DEL(_instance);
	}

	ret_ AddNetwork(const ch_1 *pszName,
					ENetworkType Type,
            const CNode *pNetwork);

	ret_ Work();

    none_ Exit()
	{
		ACE_Reactor::instance()->end_reactor_event_loop();
	}

    const CNode *GetNetwork(const ch_1 *pszName)
	{
        MapNode::iterator pos = _nodeMap.find(pszName);

        if (_nodeMap.end() != pos)
			return pos->second;

		return null_v;
	}

protected:
	ret_ Stop();

private:
    CNetworkManager() {
    }

	CNetworkManager(const CNetworkManager &);
	const CNetworkManager &operator =(const CNetworkManager &);

	virtual ~CNetworkManager()
	{
		Stop();
	}

    MapNode    _nodeMap;
    MapReactor _reactorMap;

    static CNetworkManager *_instance;
};

#endif // _C_NETWORK_MANAGER_H_
