#ifndef COPT_WAIT_MESSAGE_H
#define COPT_WAIT_MESSAGE_H

#include "COperator.h"

#include <string.h>

class COptWaitMessage: public COperator
{
public:

	COptWaitMessage(const ch_1 *szMessageName)
		: COperator(OT_WAIT_MESSAGE)
	{
		memset(m_szMessageName, 0, VARIABLE_NAME_LENGTH);
		strncpy(m_szMessageName, szMessageName, VARIABLE_NAME_LENGTH);
	}

	COptWaitMessage(const COptWaitMessage &opt): COperator(opt)
	{
		memset(m_szMessageName, 0, VARIABLE_NAME_LENGTH);
		strncpy(m_szMessageName, opt.m_szMessageName, VARIABLE_NAME_LENGTH);
	}

	const COptWaitMessage &operator =(const COptWaitMessage &opt)
	{
		if (this != &opt)
		{
			COperator::operator =(opt);

			memset(m_szMessageName, 0, VARIABLE_NAME_LENGTH);
			strncpy(m_szMessageName, opt.m_szMessageName, VARIABLE_NAME_LENGTH);
		}

		return *this;
	}

	virtual COperator *Clone() const
	{
		return (COperator *)new COptWaitMessage(*this);
	}

	virtual void Work(const TMU *pTMU);

private:
	COptWaitMessage();

	ch_1 m_szMessageName[VARIABLE_NAME_LENGTH];
};

#endif // COPT_WAIT_MESSAGE_H


