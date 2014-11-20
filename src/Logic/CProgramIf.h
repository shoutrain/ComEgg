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
	
	virtual COperator *Clone() const
	{
		return (COperator *)new CProgramIf(*this);
	}
	
	virtual bool_ AddOperator(const COperator *pOperator);
	bool_ AddExpression(const CExpression *pExpression);

	virtual void Initialize(const opt_unit *pUnit);
	virtual void Work(const TMessageUnit *pTMU);

private:
	void Clear();

	vector_exp m_ExpVector;
};

#endif // COPT_IF_H
