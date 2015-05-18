#ifndef COPERATOR_H
#define COPERATOR_H

#include "LogicCommon.h"
#include "../Data/CVariable.h"

class COperator
{
public:
	virtual COperator *Clone() const = 0;

	EOperatorType GetType() const
	{
		return m_Type;
	}

	const COperator *GetParent() const
	{
		return m_pParent;
	}

	virtual void Reset() {}

	virtual void Initialize(const opt_unit *pUnit)
	{
		m_pParent = pUnit->pParent;
		m_pData = pUnit->pData;
	}

	virtual void Work(const TMU *pTMU) = 0;

protected:
	COperator(const EOperatorType Type)
	{
		m_Type = Type;
		m_pParent = null_v;
		m_pData = null_v;
	}

	COperator(const COperator &opt)
	{
		m_Type = opt.m_Type;
		m_pParent = null_v;
		m_pData = null_v;
	}

	const COperator &operator =(const COperator &opt)
	{
		if (this != &opt)
		{
			m_Type = opt.m_Type;
			m_pParent = null_v;
			m_pData = null_v;
		}

		return *this;
	}

	EOperatorType m_Type;
	COperator *m_pParent;
	CData *m_pData;

private:
	COperator();
};

#endif // COPERATOR_H
