#ifndef COPT_IF_H
#define COPT_IF_H

#include "CProgram.h"
#include "CExpression.h"

class CProgramIf: public CProgram
{
public:
	CProgramIf(const CData *pData = null_v): CProgram(OT_IF, pData) {};

	virtual ~CProgramIf()
	{
		Clear();
	}

	CProgramIf(const CProgramIf &opt);
	const CProgramIf &operator =(const CProgramIf &opt);

    virtual COperator *clone() const
	{
		return (COperator *)new CProgramIf(*this);
	}
	
	virtual bool_ AddOperator(const COperator *pOperator);
	bool_ AddExpression(const CExpression *pExpression);

    virtual void init(const optUnit *unit);

    virtual void work(const TMessageUnit *tmu);

private:
	void Clear();

    vectorExp m_ExpVector;
};

#endif // COPT_IF_H
