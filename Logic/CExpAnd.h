#ifndef CEXP_AND_H
#define CEXP_AND_H

#include "CExpression.h"

class CExpAnd: CExpression
{
public:
	CExpAnd(const CExpression *pLeftExp, const CExpression *pRightExp)
	{
		m_pLeftExp	= pLeftExp->Clone();
		m_pRightExp	= pRightExp->Clone();
	}

	virtual ~CExpAnd()
	{
		_DEL(m_pLeftExp);
		_DEL(m_pRightExp);
	}

	CExpAnd(const CExpAnd &exp)
	{
		m_pLeftExp	= exp.m_pLeftExp->Clone();
		m_pRightExp	= exp.m_pRightExp->Clone();
	}

	const CExpAnd &operator =(const CExpAnd &exp)
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
		return (CExpression *)new CExpAnd(*this);
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
				&& m_pRightExp->Evaluate(pTMU));
		}
		catch (...)
		{
			throw;
		}
	}

private:
	CExpAnd();

	CExpression	*m_pLeftExp;
	CExpression	*m_pRightExp;
};

#endif // CEXP_AND_H


