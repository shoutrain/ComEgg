#ifndef CLINUX_SYS_CALL_IMP_H
#define CLINUX_SYS_CALL_IMP_H

#include "CSysCallImp.h"

#include <stdlib.h>
#include <stdio.h>

class CLinuxSysCallImp: CSysCallImp
{
public:
	virtual bool_ Exec(const ch_1 *pszCommand)
	{
		char szCommand[1024] = {0};

		sprintf(szCommand, "%s&", pszCommand);
		
		b_4 Ret = system(szCommand);

		if (-1 == Ret || 127 == Ret)
			return false_v;

		return true_v;
	}
};

#endif // CLINUX_SYS_CALL_IMP_H
