#include "CProtocolManager.h"
#include "CProtocolInfo.h"

CProtocolManager *CProtocolManager::m_pInstance = null_v;

ret_ CProtocolManager::Stop()
{
	_START(STOP);

	for (map_protocol::iterator pos = m_ProtocolMap.begin(); 
		 pos != m_ProtocolMap.end(); pos++)
	{
#ifdef _DEBUG_
		if (!pos->second)
			_RET(ELEMENT_NULL_IN_CONTAINER);
#endif
		_DEL(pos->second);
	}

	m_ProtocolMap.clear();

	_RET(SUCCESS);
}

ret_ CProtocolManager::AddProtocol(const ch_1 *pszName, CProtocolInfo *&pProtocol)
{
	_START(ADD_PROTOCOL);

#ifdef _DEBUG_
	if (!pszName)
		_RET(PARAMETER_NULL | PARAMETER_1);

	if (0 == pszName[0])
		_RET(PARAMETER_EMPTY | PARAMETER_1);

	if (pProtocol)
		_RET(PARAMETER_NOT_NULL | PARAMETER_2);

	// pProtocol should be valid, no check code here.
#endif

	pProtocol = new CProtocolInfo();
	m_ProtocolMap.insert(map_protocol::value_type(pszName, pProtocol));

	_RET(SUCCESS);
}

ret_ CProtocolManager::GetProtocol(const ch_1 *pszName, CProtocolInfo *&pProtocol)
{
	_START(GET_PROTOCOL);

#ifdef _DEBUG_
	if (!pszName)
		_RET(PARAMETER_NULL | PARAMETER_1);

	if (0 == pszName[0])
		_RET(PARAMETER_EMPTY | PARAMETER_1);

	if (pProtocol)
		_RET(PARAMETER_NOT_NULL | PARAMETER_2);

	// pProtocol should be valid, no check code here.
#endif

	map_protocol::iterator pos = m_ProtocolMap.find(pszName);

#ifdef _DEBUG_
	if (m_ProtocolMap.end() != pos)
	{
		if (pos->second)
#endif
			pProtocol = (CProtocolInfo *)pos->second;

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
