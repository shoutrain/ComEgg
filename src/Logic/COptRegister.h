#ifndef COPT_REGISTER_H
#define COPT_REGISTER_H

#include "COperator.h"
#include "../Tools/CRegister.h"

#include "../Transactions/CTransactionManager.h"

class COptRegister: public COperator
{
public:
	COptRegister(const CAutoVar *pCategory,
				 const CAutoVar *pKey,
				 const CAutoVar *pObject,
				 const bool_ bIsCovered = false_v)
		: COperator(OT_REGISTER)
	{
		m_pCategory		= pCategory->Clone();
		m_pKey			= pKey->Clone();
		m_pObject		= pObject->Clone();
		m_bIsCovered	= bIsCovered;
	}

	virtual ~COptRegister()
	{
		_DEL(m_pCategory);
		_DEL(m_pKey);
		_DEL(m_pObject);
	}

	COptRegister(const COptRegister &opt): COperator(opt)
	{
		m_pCategory		= opt.m_pCategory->Clone();
		m_pKey			= opt.m_pKey->Clone();
		m_pObject		= opt.m_pObject->Clone();
		m_bIsCovered	= opt.m_bIsCovered;
	}

	const COptRegister &operator =(const COptRegister &opt)
	{
		if (this != &opt)
		{
			COperator::operator =(opt);

			_DEL(m_pCategory);
			_DEL(m_pKey);
			_DEL(m_pObject);
			m_pCategory		= opt.m_pCategory->Clone();
			m_pKey			= opt.m_pKey->Clone();
			m_pObject		= opt.m_pObject->Clone();
			m_bIsCovered	= opt.m_bIsCovered;
		}

		return *this;
	}

	virtual COperator *Clone() const
	{
		return (COperator *)new COptRegister(*this);
	}

	virtual void Initialize(const opt_unit *pUnit)
	{
		COperator::Initialize(pUnit);

		m_pCategory->Initialize(pUnit->pData);
		m_pKey->Initialize(pUnit->pData);
		m_pObject->Initialize(pUnit->pData);
	}

	virtual void Work(const TMessageUnit *pTMU);

private:
	CAutoVar	*m_pCategory;
	CAutoVar	*m_pKey;
	CAutoVar	*m_pObject;
	bool_		m_bIsCovered;
};

#endif // COPT_REGISTER_H
