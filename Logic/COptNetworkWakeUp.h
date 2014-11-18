#ifndef COPT_NETWORK_WAKE_UP_H
#define COPT_NETWORK_WAKE_UP_H

#include "COperator.h"

class COptNetworkWakeUp: public COperator
{
public:
	COptNetworkWakeUp(const CVariable *pNetworkName,
					  const CVariable *pResult)
		: COperator(OT_NETWORK_WAKE_UP)
	{
		m_pNetworkName	= pNetworkName->Clone();
		m_pResult		= pResult->Clone();
	}

	virtual ~COptNetworkWakeUp()
	{
		_DEL(m_pNetworkName);
		_DEL(m_pResult);
	}

	COptNetworkWakeUp(const COptNetworkWakeUp &opt): COperator(opt)
	{
		m_pNetworkName	= opt.m_pNetworkName->Clone();
		m_pResult		= opt.m_pResult->Clone();
	}

	const COptNetworkWakeUp &operator =(const COptNetworkWakeUp &opt)
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
		return (COperator *)new COptNetworkWakeUp(*this);
	}

	virtual void Initialize(const opt_unit *pUnit)
	{
		COperator::Initialize(pUnit);

		m_pNetworkName->Initialize(pUnit->pData);
		m_pResult->Initialize(pUnit->pData);
	}

	virtual void Work(const TMU *pTMU);

private:
	CVariable *m_pNetworkName;
	CVariable *m_pResult;
};

#endif // COPT_NETWORK_WAKE_UP_H


