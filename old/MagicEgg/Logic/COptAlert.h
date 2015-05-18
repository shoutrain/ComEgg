#ifndef COPT_ALERT_H
#define COPT_ALERT_H

#include "COperator.h"

#include <string.h>

class COptAlert: public COperator
{
public:

	COptAlert(const ch_1 *pMessage)
		: COperator(OT_ALERT)
	{
		if (pMessage)
		{
			size_ n = strlen(pMessage);
			
			m_pMessage = new ch_1[n + 1];
			strncpy(m_pMessage, pMessage, n + 1);
		}
		else
		{
			m_pMessage = null_v;
		}
	}

	virtual ~COptAlert()
	{
		_DEL(m_pMessage);
	}

	COptAlert(const COptAlert &opt): COperator(opt)
	{
		if (opt.m_pMessage)
		{
			size_ n = strlen(opt.m_pMessage);
			
			m_pMessage = new ch_1[n + 1];
			strncpy(m_pMessage, opt.m_pMessage, n + 1);
		}
		else
		{
			m_pMessage = null_v;
		}
	}

	const COptAlert &operator =(const COptAlert &opt)
	{
		if (this != &opt)
		{
			COperator::operator =(opt);

			if (m_pMessage)
				_DEL(m_pMessage);

			if (opt.m_pMessage)
			{
				size_ n = strlen(opt.m_pMessage);
			
				m_pMessage = new ch_1[n + 1];
				strncpy(m_pMessage, opt.m_pMessage, n + 1);
			}
			else
			{
				m_pMessage = null_v;
			}
		}

		return *this;
	}

	virtual COperator *Clone() const
	{
		return (COperator *)new COptAlert(*this);
	}

	virtual void Work(const TMU *pTMU);

private:
	COptAlert();

	ch_1 *m_pMessage;
};

#endif // COPT_ALERT_H


