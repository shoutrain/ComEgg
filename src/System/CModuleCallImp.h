#ifndef CMODULE_CALL_IMP_H
#define CMODULE_CALL_IMP_H

#include "../Common/Common.h"

class CModuleCallImp
{
public:
	virtual bool_ Open(const ch_1 *pszModulePath, 
					   const ch_1 *pszModuleName, 
					   const ch_1 *pszModuleType) = 0;
	virtual bool_ Close() = 0;
	virtual bool_ Call(const ch_1 *pszInterfaceName,
					   const ub_1 *pIn,
					   size_ nInSize,
					   ub_1 *&pOut,
					   size_ &nOutSize) = 0;
};

#endif // CMODULE_CALL_IMP_H
