#ifndef CLINUX_MODULE_CALL_IMP_H
#define CLINUX_MODULE_CALL_IMP_H

#include "../Common/Common.h"
#include "CModuleCallImp.h"

class CLinuxModuleCallImp: public CModuleCallImp
{
public:
	CLinuxModuleCallImp(): m_Handle(null_v) {}

	virtual ~CLinuxModuleCallImp()
	{
		Close();
	}

	virtual bool_ Open(const ch_1 *pszModulePath, 
					   const ch_1 *pszModuleName, 
					   const ch_1 *pszModuleType);
	virtual bool_ Close();
	virtual bool_ Call(const ch_1 *pszInterfaceName,
					   const ub_1 *pIn,
					   size_ nInSize,
					   ub_1 *&pOut,
					   size_ &nOutSize);

private:
	obj_ m_Handle;
};

#endif // CLINUX_MODULE_CALL_IMP_H
