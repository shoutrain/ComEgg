#ifndef CACCEPTOR_H
#define CACCEPTOR_H

#include "CNetwork.h"
#include "CAcceptorHandle.h"

class CAcceptor: public ACE_Acceptor<CAcceptorHandle, ACE_SOCK_ACCEPTOR>,
				 public CNetwork
{
public:
	CAcceptor(const CProtocolInfo *pProtocol,
			  const CField *pCommandID,
			  const CField *pSizeID,
			  ub_2 nPort,
			  size_ nMaxConnection,
			  bool_ bIsAutoStart)
		: CNetwork(bIsAutoStart, NETWORK_ACCEPTOR, CACCEPTOR),
		  m_Conf(pProtocol, pCommandID, pSizeID, nPort, nMaxConnection)

	{
	}

	virtual ~CAcceptor()
	{
		close();
	}

	virtual void work()
	{
		ACE_INET_Addr Addr(m_Conf.getLocalPort());

		open(Addr, ACE_Reactor::instance());
	}

	virtual void sleep()
	{
		close();
	}

	virtual const CNetworkConf *getConf() const
	{
		return (CNetworkConf *)&m_Conf;
	}

private:
	CAcceptorConf m_Conf;
};

#endif // CACCEPTOR_H
