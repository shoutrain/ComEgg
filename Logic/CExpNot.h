#ifndef CEXP_NOT_H
#define CEXP_NOT_H

#include "CExpression.h"

class CExpNot: CExpression
{
public:
	CExpNot(const CExpression *pExp)
	{
		m_pExp = pExp->Clone();
	}

	virtual ~CExpNot()
	{
		_DEL(m_pExp);
	}

	CExpNot(const CExpNot &exp)
	{
		m_pExp = exp.m_pExp->Clone();
	}

	const CExpNot &operator =(const CExpNot &exp)
	{
		if (this != &exp)
		{
			_DEL(m_pExp);

			m_pExp = exp.m_pExp->Clone();
		}

		return *this;
	}

	virtual CExpression *Clone() const
	{
		return (CExpression *)new CExpNot(*this);
	}

	virtual void Initialize(const opt_unit *pUnit)
	{
		m_pExp->Initialize(pUnit);
	}

	virtual bool_ Evaluate(const TMU *pTMU) const
	{
		try
		{
			return (bool_)!m_pExp->Evaluate(pTMU);
		}
		catch (...)
		{
			throw;
		}
	}

private:
	CExpNot();

	CExpression	*m_pExp;
};

#endif // CEXP_OR_H

