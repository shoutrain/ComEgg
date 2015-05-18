#ifndef CEXP_OR_H
#define CEXP_OR_H

#include "CExpression.h"

class CExpOr: CExpression
{
public:
	CExpOr(const CExpression *pLeftExp, const CExpression *pRightExp)
	{
		m_pLeftExp	= pLeftExp->Clone();
		m_pRightExp	= pRightExp->Clone();
	}


	virtual ~CExpOr()
	{
		_DEL(m_pLeftExp);
		_DEL(m_pRightExp);
	}

	CExpOr(const CExpOr &exp)
	{
		m_pLeftExp	= exp.m_pLeftExp->Clone();
		m_pRightExp	= exp.m_pRightExp->Clone();
	}

	const CExpOr &operator =(const CExpOr &exp)
	{
		if (this != &exp)
		{
			_DEL(m_pLeftExp);
			_DEL(m_pRightExp);
			m_pLeftExp	= exp.m_pLeftExp->Clone();
			m_pRightExp	= exp.m_pRightExp->Clone();
		}

		return *this;
	}

	virtual CExpression *Clone() const
	{
		return (CExpression *)new CExpOr(*this);
	}

	virtual void Initialize(const opt_unit *pUnit)
	{
		m_pLeftExp->Initialize(pUnit);
		m_pRightExp->Initialize(pUnit);
	}

	virtual bool_ Evaluate(const TMU *pTMU) const
	{
		try
		{
			return (bool_)(m_pLeftExp->Evaluate(pTMU)
				|| m_pRightExp->Evaluate(pTMU));
		}
		catch (...)
		{
			throw;
		}
	}

private:
	CExpOr();

	CExpression	*m_pLeftExp;
	CExpression	*m_pRightExp;
};

#endif // CEXP_OR_H


