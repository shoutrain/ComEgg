#ifndef COPT_CONTINUE_H
#define COPT_CONTINUE_H

#include "COperator.h"

class COptContinue: public COperator
{
public:
	COptContinue(): COperator(OT_CONTINUE)
	{
	}

	COptContinue(const COptContinue &opt): COperator(opt)
	{
	}

	const COptContinue &operator =(const COptContinue &opt)
	{
		if (this != &opt)
			COperator::operator =(opt);

		return *this;
	}

	virtual COperator *Clone() const
	{
		return (COperator *)new COptContinue(*this);
	}

	virtual void Work(const TMessageUnit *pTMU)
	{
		call_break Continue;

		throw Continue;
	}
};

#endif // COPT_CONTINUE_H
