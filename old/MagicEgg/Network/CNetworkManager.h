#ifndef CNETWORK_MANAGER_H
#define CNETWORK_MANAGER_H

#include "CConnector.h"

class CNetworkManager
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

	void Work();

	void Exit()
	{
		m_bIsRunning = false_v;
		ACE_Reactor::instance()->end_reactor_event_loop();
	}

	bool_ IsRunning() const
	{
		return m_bIsRunning;
	}
	
	bool_ SetNetwork(const CNetwork *pNetwork)
	{
		if (!pNetwork || m_pNetwork)
			return false_v;

		m_pNetwork = (CNetwork *)pNetwork;

		return true_v;
	}

	const CNetwork *GetNetwork() const
	{
		return m_pNetwork;
	}

private:
	CNetworkManager()
	{
		m_bIsRunning = false_v;
		m_pNetwork = null_v;
	}

	CNetworkManager(const CNetworkManager &);
	const CNetworkManager &operator =(const CNetworkManager &);

	virtual ~CNetworkManager()
	{
		_DEL(m_pNetwork);
	}

	static CNetworkManager *m_pInstance;

	CNetwork *m_pNetwork;
	bool_ m_bIsRunning;
};

#endif // CNETWORK_MANAGER_H
