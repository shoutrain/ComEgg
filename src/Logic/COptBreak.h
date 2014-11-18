#ifndef COPT_BREAK_H
#define COPT_BREAK_H

#include "COperator.h"

class COptBreak: public COperator
{
public:
	COptBreak(): COperator(OT_BREAK)
	{
	}

	COptBreak(const COptBreak &opt): COperator(opt)
	{
	}

	const COptBreak &operator =(const COptBreak &opt)
	{
		if (this != &opt)
			COperator::operator =(opt);

		return *this;
	}

	virtual COperator *Clone() const
	{
		return (COperator *)new COptBreak(*this);
	}

	virtual void Work(const TMU *pTMU)
	{
		call_break Break;

		throw Break;
	}
};

#endif // COPT_BREAK_H
