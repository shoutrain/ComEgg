#include "CModuleManager.h"
#include "CModuleInfo.h"

CModuleManager *CModuleManager::m_pInstance = null_v;

ret_ CModuleManager::Stop()
{
	_START(STOP);

	for (map_module::iterator pos = m_ModuleMap.begin();
		 pos != m_ModuleMap.end(); pos++)
	{
#ifdef _DEBUG_
		if (!pos->second)
			_RET(ELEMENT_NULL_IN_CONTAINER);
#endif
		_DEL(pos->second);
	}

	m_ModuleMap.clear();

	_RET(SUCCESS);
}

ret_ CModuleManager::AddModule(const ch_1 *pszPath,
							   const ch_1 *pszName, 
							   const ch_1 *pszExt,
							   CModuleInfo *&pModule)
{
	_START(ADD_MODULE);

#ifdef _DEBUG_
	if (!pszPath)
		_RET(PARAMETER_NULL | PARAMETER_1);

	if (0 == pszPath[0])
		_RET(PARAMETER_EMPTY | PARAMETER_1);

	if (!pszName)
		_RET(PARAMETER_NULL | PARAMETER_2);

	if (0 == pszName[0])
		_RET(PARAMETER_EMPTY | PARAMETER_2);

	if (!pszExt)
		_RET(PARAMETER_NULL | PARAMETER_3);

	if (0 == pszExt[0])
		_RET(PARAMETER_EMPTY | PARAMETER_3);

	if (pModule)
		_RET(PARAMETER_NOT_NULL | PARAMETER_4);

	// pModule should be valid, no check code here.
#endif

	pModule = new CModuleInfo(pszPath, pszName, pszExt);
	m_ModuleMap.insert(map_module::value_type(pszName, pModule));

	_RET(SUCCESS);
}

ret_ CModuleManager::GetModule(const ch_1 *pszName, CModuleInfo *&pModule)
{
	_START(GET_MODULE);

#ifdef _DEBUG_
	if (!pszName)
		_RET(PARAMETER_NULL | PARAMETER_1);

	if (0 == pszName[0])
		_RET(PARAMETER_EMPTY | PARAMETER_1);

	if (pModule)
		_RET(PARAMETER_NOT_NULL | PARAMETER_2);

	// pModule should be valid, no check code here.
#endif

	map_module::iterator pos = m_ModuleMap.find(pszName);

#ifdef _DEBUG_
	if (m_ModuleMap.end() != pos)
	{
		if (pos->second)
#endif
			pModule = (CModuleInfo *)pos->second;

#ifdef _DEBUG_
		else
			_RET(ELEMENT_NULL_IN_CONTAINER);
	}
	else
	{
		_RET(NO_ELEMENT_IN_CONTAINER);
	}
#endif

	_RET(SUCCESS);
}
