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
        m_pExpression = pExpression->clone();
	}

	virtual ~CProgramWhile()
	{
		Clear();
	}

	CProgramWhile(const CProgramWhile &opt): CProgram(opt)
	{
		m_bJudgeHead	= opt.m_bJudgeHead;
        m_pExpression = opt.m_pExpression->clone();
	}

	const CProgramWhile &operator =(const CProgramWhile &opt)
	{
		if (this != &opt)
		{
			Clear();

			CProgram::operator =(opt);

			m_bJudgeHead	= opt.m_bJudgeHead;
            m_pExpression = opt.m_pExpression->clone();
		}

		return *this;
	}

    virtual COperator *clone() const
	{
		return (COperator *)new CProgramWhile(*this);
	}

    virtual void init(const optUnit *unit)
	{
        CProgram::init(unit);

        optUnit Unit;

        memcpy(&Unit, unit, sizeof(optUnit));
        Unit.data = &m_Data;
        Unit.parent = this;

        m_pExpression->init(&Unit);
	}

    virtual void work(const TMessageUnit *tmu);

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
