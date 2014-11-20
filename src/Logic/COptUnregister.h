#ifndef COPT_UNREGISTER_H
#define COPT_UNREGISTER_H

#include "COperator.h"

#include "../Tools/CRegister.h"
#include "../Transactions/CTransactionManager.h"

class COptUnregister: public COperator
{
public:
	COptUnregister(const CAutoVar *pCategory,
				   const CAutoVar *pKey)
		: COperator(OT_UNREGISTER)
	{
		m_pCategory	= pCategory->Clone();
		m_pKey		= pKey->Clone();
	}

	virtual ~COptUnregister()
	{
		_DEL(m_pCategory);
		_DEL(m_pKey);
	}

	COptUnregister(const COptUnregister &opt): COperator(opt)
	{
		m_pCategory	= opt.m_pCategory->Clone();
		m_pKey		= opt.m_pKey->Clone();
	}

	const COptUnregister &operator =(const COptUnregister &opt)
	{
		if (this != &opt)
		{
			COperator::operator =(opt);

			_DEL(m_pCategory);
			_DEL(m_pKey);
			m_pCategory	= opt.m_pCategory->Clone();
			m_pKey		= opt.m_pKey->Clone();
		}

		return *this;
	}

	virtual COperator *Clone() const
	{
		return (COperator *)new COptUnregister(*this);
	}

	virtual void Initialize(const opt_unit *pUnit)
	{
		COperator::Initialize(pUnit);

		m_pCategory->Initialize(pUnit->pData);
		m_pKey->Initialize(pUnit->pData);
	}

	virtual void Work(const TMessageUnit *pTMU);

private:
	CAutoVar	*m_pCategory;
	CAutoVar	*m_pKey;
};

#endif // COPT_UNREGISTER_H
