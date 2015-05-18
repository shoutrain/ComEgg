#include "CNetworkManager.h"

CNetworkManager *CNetworkManager::m_pInstance = null_v;

void CNetworkManager::Work()
{
	m_bIsRunning = true_v;
	
	if (m_pNetwork)
		m_pNetwork->Work();

	ACE_Reactor::instance()->owner(ACE_OS::thr_self());
	ACE_Reactor::instance()->run_reactor_event_loop();
}
