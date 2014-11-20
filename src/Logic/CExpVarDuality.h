#ifndef CEXP_VAR_DUALITY_H
#define CEXP_VAR_DUALITY_H

#include "CExpression.h"

class CExpVarDuality: public CExpression
{
public:
	CExpVarDuality(const CAutoVar *pLeftVar,
				   const ECompareCalculate ECC,
				   const CAutoVar *pRightVar)
	{
		m_pLeftVar	= pLeftVar->Clone();
		m_ECC		= ECC;
		m_pRightVar	= pRightVar->Clone();
	}

	virtual ~CExpVarDuality()
	{
		_DEL(m_pLeftVar);
		_DEL(m_pRightVar);
	}

	CExpVarDuality(const CExpVarDuality &exp)
	{
		m_pLeftVar	= exp.m_pLeftVar->Clone();
		m_ECC		= exp.m_ECC;
		m_pRightVar	= exp.m_pRightVar->Clone();
	}

	const CExpVarDuality &operator =(const CExpVarDuality &exp)
	{
		if (this != &exp)
		{
			_DEL(m_pLeftVar);
			_DEL(m_pRightVar);
			m_pLeftVar	= exp.m_pLeftVar->Clone();
			m_ECC		= exp.m_ECC;
			m_pRightVar	= exp.m_pRightVar->Clone();
		}

		return *this;
	}

	virtual CExpression *Clone() const
	{
		return (CExpression *)new CExpVarDuality(*this);
	}

	virtual void Initialize(const opt_unit *pUnit)
	{
		m_pLeftVar->Initialize(pUnit->pData);
		m_pRightVar->Initialize(pUnit->pData);
	}

	virtual bool_ Evaluate(const TMessageUnit *pTMU) const
	{
		bool_ bResult = false_v;

		try
		{
			v_ LeftValue(*m_pLeftVar->Value(pTMU));
			v_ RightValue(*m_pRightVar->Value(pTMU));

			switch (m_ECC)
			{
			case CC_EQ:
				bResult = (bool_)(LeftValue == RightValue);
				break;
			case CC_GL:
				bResult = (bool_)(LeftValue != RightValue);
				break;
			case CC_GT:
				bResult = (bool_)(LeftValue > RightValue);
				break;
			case CC_GE:
				bResult = (bool_)(LeftValue >= RightValue);
				break;
			case CC_LS:
				bResult = (bool_)(LeftValue < RightValue);
				break;
			case CC_LE:
				bResult = (bool_)(LeftValue <= RightValue);
				break;
			}
		}
		catch (...)
		{
			throw;
		}

		return bResult;
	}

private:
	CExpVarDuality();

	CAutoVar			*m_pLeftVar;
	ECompareCalculate	m_ECC;
	CAutoVar			*m_pRightVar;
};

#endif // CEXP_VAR_DUALITY_H

