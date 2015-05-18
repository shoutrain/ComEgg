#ifndef COPT_SHOW_WINDOW_H
#define COPT_SHOW_WINDOW_H

#include "COperator.h"

#include <string.h>

class COptShowWindow: public COperator
{
public:

	COptShowWindow(const ch_1 *pWindowName)
		: COperator(OT_SHOW_WINDOW)
	{
		memset(m_szWindowName, 0, VARIABLE_NAME_LENGTH);
		strncpy(m_szWindowName, pWindowName, VARIABLE_NAME_LENGTH);
	}

	COptShowWindow(const COptShowWindow &opt): COperator(opt)
	{
		memset(m_szWindowName, 0, VARIABLE_NAME_LENGTH);
		strncpy(m_szWindowName, opt.m_szWindowName, VARIABLE_NAME_LENGTH);
	}

	const COptShowWindow &operator =(const COptShowWindow &opt)
	{
		if (this != &opt)
		{
			COperator::operator =(opt);

			memset(m_szWindowName, 0, VARIABLE_NAME_LENGTH);
			strncpy(m_szWindowName, opt.m_szWindowName, VARIABLE_NAME_LENGTH);
		}

		return *this;
	}

	virtual COperator *Clone() const
	{
		return (COperator *)new COptShowWindow(*this);
	}

	virtual void Work(const TMU *pTMU);

private:
	COptShowWindow();

	ch_1 m_szWindowName[VARIABLE_NAME_LENGTH];
};

#endif // COPT_SHOW_WINDOW_H


