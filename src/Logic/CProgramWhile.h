#ifndef COPT_WHILE_H
#define COPT_WHILE_H

#include "CProgram.h"
#include "CExpression.h"

class CProgramWhile: public CProgram
{
public:
	CProgramWhile(bool_ bJudgeHead,
				  const CExpression *pExpression,
				  const CData *pData = null_v)
		: CProgram(OT_WHILE, pData)
	{
		m_bJudgeHead	= bJudgeHead;
		m_pExpression	= pExpression->Clone();
	}

	virtual ~CProgramWhile()
	{
		Clear();
	}

	CProgramWhile(const CProgramWhile &opt): CProgram(opt)
	{
		m_bJudgeHead	= opt.m_bJudgeHead;
		m_pExpression	= opt.m_pExpression->Clone();
	}

	const CProgramWhile &operator =(const CProgramWhile &opt)
	{
		if (this != &opt)
		{
			Clear();

			CProgram::operator =(opt);

			m_bJudgeHead	= opt.m_bJudgeHead;
			m_pExpression	= opt.m_pExpression->Clone();
		}

		return *this;
	}

	virtual COperator *Clone() const
	{
		return (COperator *)new CProgramWhile(*this);
	}

	virtual void Initialize(const opt_unit *pUnit)
	{
		CProgram::Initialize(pUnit);

		opt_unit Unit;

		memcpy(&Unit, pUnit, sizeof(opt_unit));
		Unit.pData		= &m_Data;
		Unit.pParent	= this;

		m_pExpression->Initialize(&Unit);
	}

	virtual void Work(const TMessageUnit *pTMU);

private:
	CProgramWhile();

	void Clear()
	{
		CProgram::Clear();

		_DEL(m_pExpression);
	}

	bool_		m_bJudgeHead;
	CExpression	*m_pExpression;
};

#endif // COPT_WHILE_H
