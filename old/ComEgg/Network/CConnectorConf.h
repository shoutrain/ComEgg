#ifndef CCONNECTOR_CONF_H
#define CCONNECTOR_CONF_H

#include "CNetworkConf.h"

class CConnectorConf: public CNetworkConf
{
public:
	CConnectorConf(const CProtocolInfo *pProtocol,
				   const CField *pCommandID,
				   const CField *pSizeID,
				   ub_2 nLocalPort,
				   const ch_1 *pszRemoteIP,
				   ub_2 nRemotePort,
				   b_4 nReconnect)
		: CNetworkConf(pProtocol,
					   pCommandID,
					   pSizeID,
					   nLocalPort,
					   CCONNECTORCONF)
	{
		Start(pszRemoteIP, nRemotePort, nReconnect);
	}

	const ch_1 *GetRemoteIP() const
	{
		return (const ch_1 *)m_sRemoteIP;
	}

	ub_2 GetRemotePort() const
	{
		return m_nRemotePort;
	}

	bool_ Reconnect()
	{
		if (0 == m_nReconnect)
		{
			return true_v;
		}
		else if (0 < m_nReconnect
				 &&	m_nCurrentReconnect < (size_)m_nReconnect)
		{
			m_nCurrentReconnect++;

			return true_v;
		}

		return false_v;
	}

protected:
	ret_ Start(const ch_1 *pszRemoteIP, ub_2 nRemotePort, b_4 nReconnect);

private:
	ch_1	m_sRemoteIP[IP_MAX_LENGTH];
	ub_2	m_nRemotePort;

	b_4		m_nReconnect;	// 0:	reconnect forever;
							// >0:	reconnect >0 times.
	size_	m_nCurrentReconnect;
};

#endif // CCONNECTOR_CONF_H
