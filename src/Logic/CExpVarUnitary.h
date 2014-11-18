#ifndef CEXP_VAR_UNITARY_H
#define CEXP_VAR_UNITARY_H

#include "CExpression.h"

class CExpVarUnitary: public CExpression
{
public:
	CExpVarUnitary(const CVariable *pVariable)
	{
		m_pVariable = pVariable->Clone();
	}

	virtual ~CExpVarUnitary()
	{
		_DEL(m_pVariable);
	}

	CExpVarUnitary(const CExpVarUnitary &exp)
	{
		m_pVariable = exp.m_pVariable->Clone();
	}

	const CExpVarUnitary &operator =(const CExpVarUnitary &exp)
	{
		if (this != &exp)
		{
			_DEL(m_pVariable);

			m_pVariable = exp.m_pVariable->Clone();
		}

		return *this;
	}

	virtual CExpression *Clone() const
	{
		return (CExpression *)new CExpVarUnitary(*this);
	}

	virtual void Initialize(const opt_unit *pUnit)
	{
		m_pVariable->Initialize(pUnit->pData);
	}

	virtual bool_ Evaluate(const TMU *pTMU) const
	{

		bool_ bResult;

		try
		{
			v_		Value(*m_pVariable->Value(pTMU));
			eht_	Style = (eht_)_STYLE(Value.get_type());

			switch (Style)
			{
			case NORMAL_STYLE:
			case FLOAT_STYLE:
				bResult = (0 == (b_4)Value) ? false_v : true_v;
				break;
			case STRING_STYLE:
			{
				const ch_1 *psz = (const ch_1 *)Value;

				if (null_v == psz || 0 == psz[0])
					bResult = false_v;
				else
					bResult = true_v;
			}
			break;
			case OBJECT_STYLE:
			{
				const obj_ p = (const obj_)Value;

				if (null_v == p)
					bResult = false_v;
				else
					bResult = true_v;
			}
			break;
			}

		}
		catch (...)
		{
			bResult = false_v;
		}

		return bResult;
	}

private:
	CExpVarUnitary();

	CVariable *m_pVariable;
};

#endif // CEXP_VAR_UNITARY_H

