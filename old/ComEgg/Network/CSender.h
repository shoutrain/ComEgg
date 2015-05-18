#ifndef CSENDER_H
#define CSENDER_H

#include "CSenderHandle.h"
#include "CNetwork.h"

class CSender: public CNetwork
{
public:
	CSender(const CProtocolInfo *pProtocol,
			const CField *pCommandID,
			const CField *pSizeID,
			ub_2 nPort,
			bool_ bIsAutoStart)
		: CNetwork(bIsAutoStart, NETWORK_SENDER, CSENDER),
		  m_Conf(pProtocol, pCommandID, pSizeID, nPort)

	{
	}

	virtual void Work()
	{
		m_Handle.open(m_Conf.GetLocalPort(), (ub_1 *)this);
	}

	virtual void Sleep() {}

	virtual const CNetworkConf *GetConf() const
	{
		return (CNetworkConf *)&m_Conf;
	}

private:
	CSenderConf		m_Conf;
	CSenderHandle 	m_Handle;
};

#endif // CSENDER_H
