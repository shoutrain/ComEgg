#include "CLinuxModuleCallImp.h"
#include "../Modules/ModuleCommon.h"

#include <string.h>

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

bool_ CLinuxModuleCallImp::Open(const ch_1 *pszModulePath, 
								const ch_1 *pszModuleName, 
								const ch_1 *pszModuleType)
{
	if ((!pszModulePath || 0 == pszModulePath[0] 
		 || MODULE_PATH_LENGTH <= strlen(pszModulePath))
		|| 
		(!pszModuleName || 0 == pszModuleName[0] 
		 || MODULE_NAME_LENGTH <= strlen(pszModuleName))
		|| 
		(!pszModuleType || 0 == pszModuleType[0]
		 || MODULE_EXT_LENGTH <= strlen(pszModuleType)))
	{
		return false_v;
	}

	
	size_ nLength = MODULE_PATH_LENGTH 
		+ MODULE_NAME_LENGTH 
		+ MODULE_EXT_LENGTH;
	ch_1 szModule[nLength];

	memset(szModule, 0, nLength);
	sprintf(szModule, "%s/lib%s.%s", pszModulePath, pszModuleName, pszModuleType);

	m_Handle = dlopen(szModule, RTLD_NOW);

	if (!m_Handle)
		return false_v;

	return true_v;
}

bool_ CLinuxModuleCallImp::Close()
{
	if (m_Handle)
	{
		dlclose(m_Handle);
		m_Handle = null_v;
	}

	return true_v;
}

bool_ CLinuxModuleCallImp::Call(const ch_1 *pszInterfaceName,
								const ub_1 *pIn,
								size_ nInSize,
								ub_1 *&pOut,
								size_ &nOutSize)
{
	if (!pszInterfaceName 
		|| 0 == pszInterfaceName[0]
		|| INTERFACE_NAME_LEGNTH <= strlen(pszInterfaceName))
	{
		return false_v;
	}

	if (pOut)
		return false_v;

	if (!m_Handle)
		return false_v;
	
	void (*CallFun)(const ub_1 *, size_, ub_1 *&, size_ &);

	CallFun = (void (*)(const ub_1 *, size_, ub_1 *&, size_ &))
		dlsym(m_Handle, pszInterfaceName);

	const ch_1 *pszErrMsg = dlerror();

	if (NULL != pszErrMsg)
		return false_v;

	CallFun(pIn, nInSize, pOut, nOutSize);
	
	return true_v;
}
