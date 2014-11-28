#ifndef CACCEPTOR_CONF_H
#define CACCEPTOR_CONF_H

#include "CNodeConf.h"
#include "CIPFilter.h"
#include "ace/Synch.h"

class CAcceptorConf : public CNodeConf
{
public:
	CAcceptorConf(const CProtocolInfo *pProtocol,
				  const CField *pCommandID,
				  const CField *pSizeID,
				  ub_2 nLocalPort,
				  size_ nMaxConnection)
            : CNodeConf(pProtocol,
					   pCommandID,
					   pSizeID,
					   nLocalPort,
					   CACCEPTORCONF)
	{
		m_nMaxConnection		= nMaxConnection;
		m_nCurrentConnection	= 0;
	}

	// Just for counting, actual action will be launched in CAcceptor
	bool_ OpenConnection()
	{
		m_Mutex.acquire();

		if (m_nCurrentConnection < m_nMaxConnection)
		{
			m_nCurrentConnection++;
			m_Mutex.release();

			return true_v;
		}

		m_Mutex.release();

		return false_v;
	}

	// Just for counting, actual action will be launched in CAcceptor
    none_ CloseConnection()
	{
		m_Mutex.acquire();
		m_nCurrentConnection--;
		m_Mutex.release();
	}

	CIPFilter &IPFilter()
	{
		return m_IPFilter;
	}

	size_ GetMaxConnection() const
	{
		return m_nMaxConnection;
	}

private:
	size_ m_nMaxConnection;
	size_ m_nCurrentConnection;

	ACE_Thread_Mutex m_Mutex;

	CIPFilter m_IPFilter;
};

#endif // CACCEPTOR_CONF_H
