#include "CInterfaceInfo.h"
#include "CModuleInfo.h"

ret_ CModuleInfo::Stop()
{
	_START(STOP);

	for (map_interface::iterator pos = m_InterfaceInfoMap.begin();
		 pos != m_InterfaceInfoMap.end(); pos++)
	{
#ifdef _DEBUG_
		if (!pos->second)
			_RET(ELEMENT_NULL_IN_CONTAINER);
#endif
		_DEL(pos->second);
	}

	m_InterfaceInfoMap.clear();

	_RET(SUCCESS);
}

ret_ CModuleInfo::AddInterface(const ch_1 *pszName,
							   CInterfaceInfo *&pInterfaceInfo)
{
	_START(ADD_INTERFACE);

#ifdef _DEBUG_
	if (!pszName)
		_RET(PARAMETER_NULL | PARAMETER_1);

	if (0 == pszName[0])
		_RET(PARAMETER_EMPTY | PARAMETER_1);

	if (pInterfaceInfo)
		_RET(PARAMETER_NOT_NULL | PARAMETER_2);

	// pInterfaceInfo should be valid, no check code here.
#endif

	pInterfaceInfo = new CInterfaceInfo(this, pszName);
	m_InterfaceInfoMap.insert(map_interface::value_type(pszName, pInterfaceInfo));

	_RET(SUCCESS);
}

ret_ CModuleInfo::GetInterface(const ch_1 *pszName, 
							   CInterfaceInfo *&pInterfaceInfo)
{
	_START(GET_INTERFACE);

#ifdef _DEBUG_
	if (!pszName)
		_RET(PARAMETER_NULL | PARAMETER_1);

	if (0 == pszName[0])
		_RET(PARAMETER_EMPTY | PARAMETER_1);

	if (pInterfaceInfo)
		_RET(PARAMETER_NOT_NULL | PARAMETER_2);
#endif

	map_interface::iterator pos = m_InterfaceInfoMap.find(pszName);

#ifdef _DEBUG_
	if (m_InterfaceInfoMap.end() != pos)
	{
		if (pos->second)
#endif
			pInterfaceInfo = (CInterfaceInfo *)pos->second;

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
