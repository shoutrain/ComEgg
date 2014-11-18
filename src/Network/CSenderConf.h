#ifndef SENDER_CONF_H
#define SENDER_CONF_H

#include "CNetworkConf.h"

class CSenderConf: public CNetworkConf
{
public:
	CSenderConf(const CProtocolInfo *pProtocol,
				const CField *pCommandID,
				const CField *pSizeID,
				ub_2 nLocalPort)
		: CNetworkConf(pProtocol,
					   pCommandID,
					   pSizeID,
					   nLocalPort,
					   CSENDERCONF)
	{
	}
};

#endif // SENDER_CONF_H
