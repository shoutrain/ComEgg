#ifndef COPT_SPLIT_H
#define COPT_SPLIT_H

#include "COperator.h"

class COptSplit: public COperator
{
public:
	COptSplit(const CVariable *pEnvironment,
			  const CVariable *pResult)
		: COperator(OT_SPLIT)
	{
		m_pEnvironment	= pEnvironment->Clone();
		m_pResult		= pResult->Clone();
	}

	virtual ~COptSplit()
	{
		_DEL(m_pEnvironment);
		_DEL(m_pResult);
	}

	COptSplit(const COptSplit &opt): COperator(opt)
	{
		m_pEnvironment	= opt.m_pEnvironment->Clone();
		m_pResult		= opt.m_pResult->Clone();
	}

	const COptSplit &operator =(const COptSplit &opt)
	{
		if (this != &opt)
		{
			COperator::operator =(opt);

			_DEL(m_pEnvironment);
			_DEL(m_pResult);
			m_pEnvironment	= opt.m_pEnvironment->Clone();
			m_pResult		= opt.m_pResult->Clone();
		}

		return *this;
	}

	virtual COperator *Clone() const
	{
		return (COperator *)new COptSplit(*this);
	}

	virtual void Initialize(const opt_unit *pUnit)
	{
		COperator::Initialize(pUnit);

		m_pEnvironment->Initialize(pUnit->pData);
		m_pResult->Initialize(pUnit->pData);
	}

	virtual void Work(const TMU *pTMU);

private:
	CVariable *m_pEnvironment;
	CVariable *m_pResult;
};

#endif // COPT_SPLIT_H


