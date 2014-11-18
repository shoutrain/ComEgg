#ifndef CSYS_CALL_H
#define CSYS_CALL_H

#include "CSysFactory.h"

class CSysCall
{
public:
	CSysCall()
	{
		m_pSysCall = CSysFactory::Instance()->MakeSysCall();
	}

	virtual ~CSysCall()
	{
		_DEL(m_pSysCall);
	}

	bool_ Exec(const ch_1 *pszCommand)
	{
		return m_pSysCall->Exec(pszCommand);
	}

private:
	CSysCallImp *m_pSysCall;
};

#endif // CSYS_CALL_H
