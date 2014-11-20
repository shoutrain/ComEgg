#ifndef COPT_SEARCH_H
#define COPT_SEARCH_H

#include "COperator.h"
#include "../Tools/CRegister.h"

#include "../Transactions/CTransactionManager.h"

class COptSearch: public COperator
{
public:
	COptSearch(const CAutoVar *pCategory,
			   const CAutoVar *pKey,
			   const CAutoVar *pObject)
		: COperator(OT_SEARCH)
	{
		m_pCategory = pCategory->Clone();
		m_pKey		= pKey->Clone();
		m_pObject	= pObject->Clone();
	}

	virtual ~COptSearch()
	{
		_DEL(m_pCategory);
		_DEL(m_pKey);
		_DEL(m_pObject);
	}

	COptSearch(const COptSearch &opt): COperator(opt)
	{
		m_pCategory	= opt.m_pCategory->Clone();
		m_pKey		= opt.m_pKey->Clone();
		m_pObject	= opt.m_pObject->Clone();
	}

	const COptSearch &operator =(const COptSearch &opt)
	{
		if (this != &opt)
		{
			COperator::operator =(opt);

			_DEL(m_pCategory);
			_DEL(m_pKey);
			_DEL(m_pObject);
			m_pCategory	= opt.m_pCategory->Clone();
			m_pKey		= opt.m_pKey->Clone();
			m_pObject	= opt.m_pObject->Clone();
		}

		return *this;
	}

	virtual COperator *Clone() const
	{
		return (COperator *)new COptSearch(*this);
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
};

#endif // COPT_SEARCH_H
