#ifndef COPT_BLOCK_H
#define COPT_BLOCK_H

#include "COperator.h"

class COptBlock: public COperator
{
public:
	COptBlock(): COperator(OT_BLOCK)
	{
	}

	COptBlock(const COptBlock &opt): COperator(opt)
	{
	}

	const COptBlock &operator =(const COptBlock &opt)
	{
		if (this != &opt)
			COperator::operator =(opt);

		return *this;
	}

	virtual COperator *Clone() const
	{
		return (COperator *)new COptBlock(*this);
	}

	virtual void Work(const TMessageUnit *pTMU)
	{
		call_block Block;

		throw Block;
	}
};

#endif // COPT_BLOCK_H
