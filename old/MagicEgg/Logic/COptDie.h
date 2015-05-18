#ifndef COPT_DIE_H
#define COPT_DIE_H

#include "COperator.h"

#include "../Network/CNetworkManager.h"

class COptDie: public COperator
{
public:
	COptDie(): COperator(OT_DIE) {}

	COptDie(const COptDie &opt): COperator(opt)	{}

	const COptDie &operator =(const COptDie &opt)
	{
		if (this != &opt)
			COperator::operator =(opt);

		return *this;
	}

	virtual COperator *Clone() const
	{
		return (COperator *)new COptDie(*this);
	}

	virtual void Work(const TMU *pTMU)
	{
		CNetworkManager::Instance()->Exit();
		exit(0);
	}
};

#endif // COPT_DIE_H
