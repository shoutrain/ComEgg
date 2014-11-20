#ifndef COPT_EMPTY_H
#define COPT_EMPTY_H

#include "COperator.h"

class COptEmpty: public COperator
{
public:

	COptEmpty(const CAutoVar *pVariable)
		: COperator(OT_EMPTY)
	{
		m_pVariable = pVariable->Clone();
	}

	virtual ~COptEmpty()
	{
		_DEL(m_pVariable);
	}

	COptEmpty(const COptEmpty &opt): COperator(opt)
	{
		m_pVariable = opt.m_pVariable->Clone();
	}

	const COptEmpty &operator =(const COptEmpty &opt)
	{
		if (this != &opt)
		{
			COperator::operator =(opt);

			_DEL(m_pVariable);
			m_pVariable = opt.m_pVariable->Clone();
		}

		return *this;
	}

	virtual COperator *Clone() const
	{
		return (COperator *)new COptEmpty(*this);
	}

	virtual void Initialize(const opt_unit *pUnit)
	{
		COperator::Initialize(pUnit);

		m_pVariable->Initialize(pUnit->pData);
	}

	virtual void Work(const TMessageUnit *pTMU);

private:
	CAutoVar *m_pVariable;
};

#endif // COPT_EMPTY_H


