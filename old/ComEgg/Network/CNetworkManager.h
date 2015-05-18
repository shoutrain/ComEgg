#ifndef CNETWORK_MANAGER_H
#define CNETWORK_MANAGER_H

#include "CAcceptor.h"
#include "CConnector.h"
#include "CReceiver.h"
#include "CSender.h"

#include <string>
#include <map>

using namespace std;

typedef map<string, const CNetwork *> map_network;

class CNetworkManager: public CBaseClass
{
public:
	static CNetworkManager *Instance()
	{
		if (m_pInstance)
			return m_pInstance;

		m_pInstance = new CNetworkManager;

		return m_pInstance;
	}

	static void Destory()
	{
		_DEL(m_pInstance);
	}

	ret_ AddNetwork(const ch_1 *pszName,
					ENetworkType Type,
					const CNetwork *pNetwork);

	ret_ Work();

	void Exit()
	{
		ACE_Reactor::instance()->end_reactor_event_loop();
	}

	const CNetwork *GetNetwork(const ch_1 *pszName)
	{
		map_network::iterator pos = m_NetworkMap.find(pszName);

		if (m_NetworkMap.end() != pos)
			return pos->second;

		return null_v;
	}

protected:
	ret_ Stop();

private:
	CNetworkManager(): CBaseClass(CINTERFACEMANAGER) {}

	CNetworkManager(const CNetworkManager &);
	const CNetworkManager &operator =(const CNetworkManager &);

	virtual ~CNetworkManager()
	{
		Stop();
	}

	map_network m_NetworkMap;

	static CNetworkManager *m_pInstance;
};

#endif // CNETWORK_MANAGER_H
