#ifndef CCONNECTOR_H
#define CCONNECTOR_H

#include "CConnectorHandle.h"
#include "CNetwork.h"

class CConnector:
	public ACE_Connector<CConnectorHandle, ACE_SOCK_CONNECTOR>,
	public CNetwork
{
public:
	CConnector(const CProtocolInfo *pProtocol,
			   const CField *pCommandID,
			   const CField *pSizeID,
			   ub_2 nLocalPort,
			   const ch_1 *pszRemoteIP,
			   ub_2 nRemotePort,
			   b_4 nReconnect,
			   bool_ bIsAutoStart)
		: CNetwork(bIsAutoStart, NETWORK_CONNECTOR, CCONNECTOR),
		  m_Conf(pProtocol,
				 pCommandID,
				 pSizeID,
				 nLocalPort,
				 pszRemoteIP,
				 nRemotePort,
				 nReconnect)

	{
		m_bConnected = false_v;
	}

	virtual ~CConnector()
	{
		close();
	}

	virtual void Work()
	{
		ACE_Thread::spawn((ACE_THR_FUNC)Svc, (void *)this);
	}

	virtual void Sleep()
	{
		m_bConnected = false_v;
		close();
	}

	virtual const CNetworkConf *GetConf() const
	{
		return (CNetworkConf *)&m_Conf;
	}

	b_4 Run()
	{
		ACE_INET_Addr LocalAddr(m_Conf.GetLocalPort());
		ACE_INET_Addr RemoteAddr(m_Conf.GetRemotePort(),
								 m_Conf.GetRemoteIP());

		while (m_Conf.Reconnect())
		{
			CConnectorHandle *pHandle = null_v;

			if (0 == connect(pHandle, RemoteAddr, ACE_Synch_Options::defaults,
							 LocalAddr))
			{
				m_bConnected = true_v;

				while (m_bConnected)
					ACE_OS::sleep(5);
			}

			ACE_OS::sleep(3);
		}

		return -1;
	}

	static b_4 Svc(void *p)
	{
		if (p)
			return ((CConnector *)p)->Run();

		return -1;
	}

	void Disconnect()
	{
		m_bConnected = false_v;
	}

private:
	CConnectorConf	m_Conf;
	bool_			m_bConnected;
};

#endif // CCONNECTOR_H
