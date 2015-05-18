#ifndef COPT_ENABLE_H
#define COPT_ENABLE_H

#include "COperator.h"

#include <string.h>

class COptEnable: public COperator
{
public:

	COptEnable(const ch_1 *pWindowName, bool_ bIsEnable = true_v)
		: COperator(OT_ENABLE)
	{
		memset(m_szWindowName, 0, VARIABLE_NAME_LENGTH);
		strncpy(m_szWindowName, pWindowName, VARIABLE_NAME_LENGTH);
		m_bIsEnable = bIsEnable;
	}

	COptEnable(const COptEnable &opt): COperator(opt)
	{
		memset(m_szWindowName, 0, VARIABLE_NAME_LENGTH);
		strncpy(m_szWindowName, opt.m_szWindowName, VARIABLE_NAME_LENGTH);
		m_bIsEnable = opt.m_bIsEnable;
	}

	const COptEnable &operator =(const COptEnable &opt)
	{
		if (this != &opt)
		{
			COperator::operator =(opt);

			memset(m_szWindowName, 0, VARIABLE_NAME_LENGTH);
			strncpy(m_szWindowName, opt.m_szWindowName, VARIABLE_NAME_LENGTH);
			m_bIsEnable = opt.m_bIsEnable;
		}

		return *this;
	}

	virtual COperator *Clone() const
	{
		return (COperator *)new COptEnable(*this);
	}

	virtual void Work(const TMU *pTMU);

private:
	COptEnable();

	ch_1 m_szWindowName[VARIABLE_NAME_LENGTH];
	bool_ m_bIsEnable;
};

#endif // COPT_ENABLE_H


