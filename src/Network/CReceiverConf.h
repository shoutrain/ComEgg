#ifndef RECEIVER_CONF_H
#define RECEIVER_CONF_H

#include "CNetworkConf.h"
#include "CIPFilter.h"

class CReceiverConf: public CNetworkConf
{
public:
	CReceiverConf(const CProtocolInfo *pProtocol,
				  const CField *pCommandID,
				  const CField *pSizeID,
				  ub_2 nLocalPort)
		: CNetworkConf(pProtocol,
					   pCommandID,
					   pSizeID,
					   nLocalPort,
					   CRECEIVERCONF)
	{
	}

	CIPFilter &IPFilter()
	{
		return m_IPFilter;
	}

private:
	CIPFilter m_IPFilter;
};

#endif // RECEIVER_CONF_H
