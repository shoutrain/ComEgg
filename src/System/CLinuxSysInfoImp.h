#ifndef CLINUX_SYS_INFO_IMP_H
#define CLINUX_SYS_INFO_IMP_H

#include "CSysInfoImp.h"

#include <sys/sysinfo.h>

class CLinuxSysInfoImp: public CSysInfoImp
{
public:
	bool_ GetSysInfo()
	{
		if (sysinfo(&m_SysInfo))
			return false_v;

		return true_v;
	}

	virtual ub_1 GetMemoryUsage()
	{
		return (ub_1)(((double)m_SysInfo.freeram / (double)m_SysInfo.totalram) * 100);
	}

private:
	struct sysinfo m_SysInfo;
};

#endif // CLINUX_SYS_INFO_IMP_H
