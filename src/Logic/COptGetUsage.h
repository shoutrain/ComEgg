#ifndef COPT_GET_USAGE_H
#define COPT_GET_USAGE_H

#include "COperator.h"

class COptGetUsage: public COperator
{
public:
	COptGetUsage(const CVariable *pResult): COperator(OT_GET_USAGE)
	{
		m_pResult = pResult->Clone();
	}

	virtual ~COptGetUsage()
	{
		_DEL(m_pResult);
	}

	COptGetUsage(const COptGetUsage &opt): COperator(opt)
	{
		m_pResult = opt.m_pResult->Clone();
	}

	const COptGetUsage &operator =(const COptGetUsage &opt)
	{
		if (this != &opt)
		{
			COperator::operator =(opt);

			_DEL(m_pResult);
			m_pResult = opt.m_pResult->Clone();
		}

		return *this;
	}

	virtual COperator *Clone() const
	{
		return (COperator *)new COptGetUsage(*this);
	}

	virtual void Initialize(const opt_unit *pUnit)
	{
		COperator::Initialize(pUnit);

		m_pResult->Initialize(pUnit->pData);
	}

	virtual void Work(const TMU *pTMU);

private:
	CVariable *m_pResult;
};

#endif // COPT_GET_USAGE_H


