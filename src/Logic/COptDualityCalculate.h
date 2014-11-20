#ifndef COPT_DUALITY_CALCULATE_H
#define COPT_DUALITY_CALCULATE_H

#include "COperator.h"

class COptDualityCalculate: public COperator
{
public:
	COptDualityCalculate(const CAutoVar *pLeftVariable,
						 const EDualityCalculate Opt,
						 const CAutoVar *pRightVariable,
						 const CAutoVar *pResultVariable)
		: COperator(OT_DUALITY_CALCULATE)
	{
		m_pLeftVariable		= pLeftVariable->Clone();
		m_Opt				= Opt;
		m_pRightVariable	= pRightVariable->Clone();
		m_pResultVariable	= pResultVariable->Clone();
	}

	virtual ~COptDualityCalculate()
	{
		_DEL(m_pLeftVariable);
		_DEL(m_pRightVariable);
		_DEL(m_pResultVariable);
	}

	COptDualityCalculate(const COptDualityCalculate &opt): COperator(opt)
	{
		m_pLeftVariable		= opt.m_pLeftVariable->Clone();
		m_Opt				= opt.m_Opt;
		m_pRightVariable	= opt.m_pRightVariable->Clone();
		m_pResultVariable	= opt.m_pResultVariable->Clone();
	}

	const COptDualityCalculate &operator =(const COptDualityCalculate &opt)
	{
		if (this != &opt)
		{
			COperator::operator =(opt);

			_DEL(m_pLeftVariable);
			_DEL(m_pRightVariable);
			_DEL(m_pResultVariable);
			m_pLeftVariable		= opt.m_pLeftVariable->Clone();
			m_Opt				= opt.m_Opt;
			m_pRightVariable	= opt.m_pRightVariable->Clone();
			m_pResultVariable	= opt.m_pResultVariable->Clone();
		}

		return *this;
	}

	virtual COperator *Clone() const
	{
		return (COperator *)new COptDualityCalculate(*this);
	}

	virtual void Initialize(const opt_unit *pUnit)
	{
		COperator::Initialize(pUnit);

		m_pLeftVariable->Initialize(pUnit->pData);
		m_pRightVariable->Initialize(pUnit->pData);
		m_pResultVariable->Initialize(pUnit->pData);
	}

	virtual void Work(const TMessageUnit *pTMU);

private:
	CAutoVar			*m_pLeftVariable;
	EDualityCalculate	m_Opt;
	CAutoVar			*m_pRightVariable;
	CAutoVar			*m_pResultVariable;
};

#endif // COPT_DUALITY_CALCULATE_H
