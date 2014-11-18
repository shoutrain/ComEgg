#ifndef CRECEIVER_H
#define CRECEIVER_H

#include "CReceiverHandle.h"
#include "CNetwork.h"

class CReceiver: public CNetwork
{
public:
	CReceiver(const CProtocolInfo *pProtocol,
			  const CField *pCommandID,
			  const CField *pSizeID,
			  ub_2 nPort,
			  bool_ bIsAutoStart)
		: CNetwork(bIsAutoStart, NETWORK_RECEIVER, CRECEIVER),
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
	CReceiverConf	m_Conf;
	CReceiverHandle m_Handle;
};

#endif // CRECEIVER_H
