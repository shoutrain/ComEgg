#include "CNetworkManager.h"

CNetworkManager *CNetworkManager::m_pInstance = null_v;

ret_ CNetworkManager::Stop()
{
	_START(STOP);

	for (map_network::iterator pos = m_NetworkMap.begin();
		pos != m_NetworkMap.end(); pos++)
	{
#ifdef _DEBUG_
		if (!pos->second)
			_RET(ELEMENT_NULL_IN_CONTAINER);
#endif

		_DEL(pos->second);
	}

	m_NetworkMap.clear();

	_RET(SUCCESS);
}

ret_ CNetworkManager::AddNetwork(const ch_1 *pszName,
								 ENetworkType Type,
								 const CNetwork *pNetwork)
{
	_START(ADD_NETWORK);

#ifdef _DEBUG_
	if (GetNetwork(pszName))
		_RET(ELEMENT_EXIST_IN_CONTAINER);
#endif

	m_NetworkMap.insert(map_network::value_type(pszName, pNetwork));

	_RET(SUCCESS);
}

ret_ CNetworkManager::Work()
{
	_START(WORK);

	for (map_network::iterator pos = m_NetworkMap.begin();
		 pos != m_NetworkMap.end(); pos++)
	{
#ifdef _DEBUG_
		if (!pos->second)
			_RET(ELEMENT_NULL_IN_CONTAINER);
#endif
		CNetwork *pNetwork = (CNetwork *)pos->second;

		if (pNetwork->IsAutoStart())
			pNetwork->Work();
	}

	ACE_Reactor::instance()->owner(ACE_OS::thr_self());
	ACE_Reactor::instance()->run_reactor_event_loop();

	_RET(SUCCESS);
}
