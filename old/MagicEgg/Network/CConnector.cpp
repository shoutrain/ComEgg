#include "CConnector.h"
#include "CNetworkManager.h"

b_4 CConnector::Run()
{
	ACE_INET_Addr LocalAddr(m_Conf.GetLocalPort());
	ACE_INET_Addr RemoteAddr(m_Conf.GetRemotePort(), m_Conf.GetRemoteIP());
		
	while (CNetworkManager::Instance()->IsRunning() && m_Conf.Reconnect())
	{
		CConnectorHandle *pHandle = null_v;

		if (0 == connect(pHandle,
						 RemoteAddr,
						 ACE_Synch_Options::defaults,
						 LocalAddr))
		{
			m_pHandle = pHandle;

			while (pHandle->IsRunning())
				ACE_OS::sleep(5);
		}

		ACE_OS::sleep(3);
	}

	return 0;
}

