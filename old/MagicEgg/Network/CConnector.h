#ifndef CCONNECTOR_H
#define CCONNECTOR_H

#include "CConnectorHandle.h"
#include "CNetwork.h"

class CConnector:
	public ACE_Connector<CConnectorHandle, ACE_SOCK_CONNECTOR>,
	public CNetwork
{
public:
	CConnector(const CField *pCommandID,
			   const CField *pSizeID,
			   ub_2 nLocalPort,
			   const ch_1 *pszRemoteIP,
			   ub_2 nRemotePort,
			   b_4 nReconnect)
		: m_Conf(pCommandID,
				 pSizeID,
				 nLocalPort,
				 pszRemoteIP,
				 nRemotePort,
				 nReconnect)

	{
		m_pHandle = null_v;
	}

	virtual ~CConnector()
	{
		close();
	}

	virtual void Work()
	{
		ACE_Thread::spawn((ACE_THR_FUNC)Svc, (void *)this);
	}

	void SetHandle(const CNetworkHandle *pHandle)
	{
		m_pHandle = (CConnectorHandle *)pHandle;
	}
	
	virtual CNetworkHandle *GetHandle()
	{
		return (CNetworkHandle *)m_pHandle;
	}
	
	virtual const CNetworkConf *GetConf() const
	{
		return (CNetworkConf *)&m_Conf;
	}

	b_4 Run();

	static b_4 Svc(void *p)
	{
		if (p)
			return ((CConnector *)p)->Run();

		return 0;
	}

private:
	CConnectorHandle *m_pHandle;
	CConnectorConf	m_Conf;
};

#endif // CCONNECTOR_H
