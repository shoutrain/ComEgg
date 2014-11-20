#ifndef COPT_FORWARD_H
#define COPT_FORWARD_H

#include "COperator.h"

#include "../Transactions/CTransactionManager.h"

class COptForward: public COperator
{
public:
	COptForward(const CAutoVar *pObject = null_v): COperator(OT_FORWARD)
	{
		m_pObject = null_v;
		m_pIP = null_v;
		m_pPort = null_v;

		m_SendType = TCP_SEND;

		if (pObject)
			m_pObject = pObject->Clone();
	}

	COptForward(b_4 nSign/*No meaning*/,
			 const CAutoVar *pIP = null_v,
			 const CAutoVar *pPort = null_v)
		: COperator(OT_SEND)
	{
		m_pObject = null_v;
		m_pIP = null_v;
		m_pPort = null_v;

		m_SendType = UDP_SEND;

		if (pIP && pPort)
		{
			m_pIP	= pIP->Clone();
			m_pPort	= pPort->Clone();
		}
	}

	virtual ~COptForward()
	{
		_DEL(m_pObject);
		_DEL(m_pIP);
		_DEL(m_pPort);
	}

	COptForward(const COptForward &opt): COperator(opt)
	{
		m_pObject = null_v;
		m_pIP = null_v;
		m_pPort = null_v;

		m_SendType = opt.m_SendType;

		if (TCP_SEND == m_SendType)
		{
			m_pObject = opt.m_pObject->Clone();
		}
		else
		{
			m_pIP	= opt.m_pIP->Clone();
			m_pPort	= opt.m_pPort->Clone();
		}
	}

	const COptForward &operator =(const COptForward &opt)
	{
		if (this != &opt)
		{
			COperator::operator =(opt);

			_DEL(m_pObject);
			_DEL(m_pIP);
			_DEL(m_pPort);

			m_SendType	= opt.m_SendType;

			if (TCP_SEND == m_SendType)
			{
				m_pObject = opt.m_pObject->Clone();
			}
			else
			{
				m_pIP	= opt.m_pIP->Clone();
				m_pPort	= opt.m_pPort->Clone();
			}
		}

		return *this;
	}

	virtual COperator *Clone() const
	{
		return (COperator *)new COptForward(*this);
	}


	virtual void Initialize(const opt_unit *pUnit)
	{
		COperator::Initialize(pUnit);

		if (TCP_SEND == m_SendType)
		{
			m_pObject->Initialize(pUnit->pData);
		}
		else
		{
			m_pIP->Initialize(pUnit->pData);
			m_pPort->Initialize(pUnit->pData);
		}
	}

	virtual void Work(const TMessageUnit *pTMU);

private:
	enum
	{
		TCP_SEND,
		UDP_SEND
	} m_SendType;

	CAutoVar *m_pObject;
	CAutoVar *m_pIP;
	CAutoVar *m_pPort;
};

#endif // COPT_FORWARD_H
