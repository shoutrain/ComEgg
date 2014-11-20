#ifndef COPT_NETWORK_SLEEP_H
#define COPT_NETWORK_SLEEP_H

#include "COperator.h"

class COptNetworkSleep: public COperator
{
public:
	COptNetworkSleep(const CAutoVar *pNetworkName,
					 const CAutoVar *pResult)
		: COperator(OT_NETWORK_SLEEP)
	{
		m_pNetworkName	= pNetworkName->Clone();
		m_pResult		= pResult->Clone();
	}

	virtual ~COptNetworkSleep()
	{
		_DEL(m_pNetworkName);
		_DEL(m_pResult);
	}

	COptNetworkSleep(const COptNetworkSleep &opt): COperator(opt)
	{
		m_pNetworkName	= opt.m_pNetworkName->Clone();
		m_pResult		= opt.m_pResult->Clone();
	}

	const COptNetworkSleep &operator =(const COptNetworkSleep &opt)
	{
		if (this != &opt)
		{
			COperator::operator =(opt);

			_DEL(m_pNetworkName);
			_DEL(m_pResult);
			m_pNetworkName	= opt.m_pNetworkName->Clone();
			m_pResult		= opt.m_pResult->Clone();
		}

		return *this;
	}

	virtual COperator *Clone() const
	{
		return (COperator *)new COptNetworkSleep(*this);
	}

	virtual void Initialize(const opt_unit *pUnit)
	{
		COperator::Initialize(pUnit);

		m_pNetworkName->Initialize(pUnit->pData);
		m_pResult->Initialize(pUnit->pData);
	}

	virtual void Work(const TMessageUnit *pTMU);

private:
	CAutoVar *m_pNetworkName;
	CAutoVar *m_pResult;
};

#endif // COPT_NETWORK_SLEEP_H



