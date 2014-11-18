#ifndef COPT_GET_ADDRESS_H
#define COPT_GET_ADDRESS_H

#include "COperator.h"

#include "../Transactions/CTransactionManager.h"

class COptGetAddress: public COperator
{
public:
	COptGetAddress(const CVariable *pIP,
				   const CVariable *pPort,
				   bool_ bRemote = true_v)
		: COperator(OT_GET_ADDRESS)
	{
		m_pIP		= pIP->Clone();
		m_pPort		= pPort->Clone();
		m_bRemote	= bRemote;
	}

	virtual ~COptGetAddress()
	{
		_DEL(m_pIP);
		_DEL(m_pPort);
	}

	COptGetAddress(const COptGetAddress &opt): COperator(opt)
	{
		m_pIP		= opt.m_pIP->Clone();
		m_pPort		= opt.m_pPort->Clone();
		m_bRemote	= opt.m_bRemote;
	}

	const COptGetAddress &operator =(const COptGetAddress &opt)
	{
		if (this != &opt)
		{
			_DEL(m_pIP);
			_DEL(m_pPort);
			m_pIP		= opt.m_pIP->Clone();
			m_pPort		= opt.m_pPort->Clone();
			m_bRemote	= opt.m_bRemote;
		}

		return *this;
	}

	virtual COperator *Clone() const
	{
		return (COperator *)new COptGetAddress(*this);
	}

	virtual void Initialize(const opt_unit *pUnit)
	{
		COperator::Initialize(pUnit);

		m_pIP->Initialize(pUnit->pData);
		m_pPort->Initialize(pUnit->pData);
	}

	virtual void Work(const TMU *pTMU);

private:
	bool_ m_bRemote;

	CVariable *m_pIP;
	CVariable *m_pPort;
};

#endif // COPT_GET_ADDRESS_H
