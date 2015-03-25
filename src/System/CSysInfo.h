#ifndef _C_SYS_INFO_H_
#define _C_SYS_INFO_H_

#include "CSysFactory.h"

class CSysInfo {
public:
	CSysInfo() {
		_sysInfo = CSysFactory::instance()->makeSysInfo();
	}

	~CSysInfo() {
		_DEL(_sysInfo);
	}

	ub_1 getUsage() {
		return _sysInfo->getMemoryUsage();
	}

private:
	CSysInfoImp *_sysInfo;
};

#endif // _C_SYS_INFO_H_
