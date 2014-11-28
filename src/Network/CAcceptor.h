#ifndef CACCEPTOR_H
#define CACCEPTOR_H

#include "CNode.h"
#include "CAcceptorHandle.h"

class CAcceptor: public ACE_Acceptor<CAcceptorHandle, ACE_SOCK_ACCEPTOR>,
                 public CNode
{
public:
	CAcceptor(const CProtocolInfo *pProtocol,
			  const CField *pCommandID,
			  const CField *pSizeID,
			  ub_2 nPort,
			  size_ nMaxConnection,
			  bool_ bIsAutoStart)
            : CNode(bIsAutoStart, NETWORK_ACCEPTOR, CACCEPTOR),
		  m_Conf(pProtocol, pCommandID, pSizeID, nPort, nMaxConnection)

	{
	}

	virtual ~CAcceptor()
	{
		close();
	}

    virtual none_ work()
	{
		ACE_INET_Addr Addr(m_Conf.getLocalPort());

		open(Addr, ACE_Reactor::instance());
	}

    virtual none_ sleep()
	{
		close();
	}

    virtual const CNodeConf *getConf() const
	{
        return (CNodeConf *) &m_Conf;
	}

private:
	CAcceptorConf m_Conf;
};

#endif // CACCEPTOR_H
