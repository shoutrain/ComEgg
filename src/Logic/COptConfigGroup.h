#ifndef COPT_CONFIG_GROUP_H
#define COPT_CONFIG_GROUP_H

#include "COperator.h"

class COptConfigGroup: public COperator
{
public:
	COptConfigGroup(const CVariable *pGroup, const CVariable *pSize)
		: COperator(OT_CONFIG_GROUP)
	{
		m_pGroup = pGroup->Clone();
		m_pSize = pGroup->Clone();
	}

	virtual ~COptConfigGroup()
	{
		_DEL(m_pGroup);
		_DEL(m_pSize);
	}

	COptConfigGroup(const COptConfigGroup &opt): COperator(opt)
	{
		m_pGroup = opt.m_pGroup->Clone();
		m_pSize = opt.m_pGroup->Clone();
	}

	const COptConfigGroup &operator =(const COptConfigGroup &opt)
	{
		if (this != &opt)
		{
			COperator::operator =(opt);

			_DEL(m_pGroup);
			_DEL(m_pSize);
			m_pGroup = opt.m_pGroup->Clone();
			m_pSize = opt.m_pGroup->Clone();
		}

		return *this;
	}

	virtual COperator *Clone() const
	{
		return (COperator *)new COptConfigGroup(*this);
	}

	virtual void Initialize(const opt_unit *pUnit)
	{
		COperator::Initialize(pUnit);

		m_pGroup->Initialize(pUnit->pData);
		m_pSize->Initialize(pUnit->pData);
	}

	virtual void Work(const TMU *pTMU);

private:
	CVariable *m_pGroup;
	CVariable *m_pSize;
};

#endif // COPT_CONFIG_GROUP_H


