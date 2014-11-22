#ifndef COPT_UNITARY_CALCULATE_H
#define COPT_UNITARY_CALCULATE_H

#include "COperator.h"

class COptUnitaryCalculate: public COperator
{
public:
	COptUnitaryCalculate(const EUnitaryCalculate Opt,
						 const CAutoVar *pResultVariable,
						 const CAutoVar *pRightVariable)
		: COperator(OT_UNITARY_CALCULATE)
	{
		m_Opt				= Opt;
		m_pResultVariable	= pResultVariable->Clone();
		m_pRightVariable	= pRightVariable->Clone();
	}

	virtual ~COptUnitaryCalculate()
	{
		_DEL(m_pResultVariable);
		_DEL(m_pRightVariable);
	}

	COptUnitaryCalculate(const COptUnitaryCalculate &opt): COperator(opt)
	{
		m_Opt				= opt.m_Opt;
		m_pResultVariable	= opt.m_pResultVariable->Clone();
		m_pRightVariable	= opt.m_pRightVariable->Clone();
	}

	const COptUnitaryCalculate &operator =(const COptUnitaryCalculate &opt)
	{
		if (this != &opt)
		{
			COperator::operator =(opt);

			_DEL(m_pRightVariable);
			_DEL(m_pResultVariable);
			m_Opt				= opt.m_Opt;
			m_pResultVariable	= opt.m_pResultVariable->Clone();
			m_pRightVariable	= opt.m_pRightVariable->Clone();
		}

		return *this;
	}

    virtual COperator *clone() const
	{
		return (COperator *)new COptUnitaryCalculate(*this);
	}

    virtual void init(const optUnit *unit)
	{
        COperator::init(unit);

        m_pResultVariable->Initialize(unit->data);
        m_pRightVariable->Initialize(unit->data);
	}

    virtual void work(const TMessageUnit *tmu);

private:
	EUnitaryCalculate	m_Opt;
	CAutoVar			*m_pResultVariable;
	CAutoVar			*m_pRightVariable;
};

#endif // COPT_UNITARY_CALCULATE_H
