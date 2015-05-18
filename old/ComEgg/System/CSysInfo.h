#ifndef CSYS_INFO_H
#define CSYS_INFO_H

#include "CSysFactory.h"

class CSysInfo
{
public:
	CSysInfo()
	{
		m_pSysInfo = CSysFactory::Instance()->MakeSysInfo();
	}

	~CSysInfo()
	{
		_DEL(m_pSysInfo);
	}

	ub_1 GetUsage()
	{
		return m_pSysInfo->GetMemoryUsage();
	}

private:
	CSysInfoImp *m_pSysInfo;
};

#endif // CSYS_INFO_H
