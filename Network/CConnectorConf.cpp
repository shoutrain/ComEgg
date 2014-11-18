#include "CConnectorConf.h"

#include "string.h"

ret_ CConnectorConf::Start(const ch_1 *pszRemoteIP, 
						   ub_2 nRemotePort, 
						   b_4 nReconnect)
{
	_START(START);

#ifdef _DEBUG_
	if (!pszRemoteIP)
		_RET(PARAMETER_NULL | PARAMETER_1);

	if (0 == pszRemoteIP[0])
		_RET(PARAMETER_EMPTY | PARAMETER_1);

	if (-1 > nReconnect)
		_RET(PARAMETER_TYPE_ERROR | PARAMETER_3);
#endif

	m_nCurrentReconnect = 0;

	memset(m_sRemoteIP, 0, IP_MAX_LENGTH);
	strncpy(m_sRemoteIP, pszRemoteIP, IP_MAX_LENGTH_SIGN);
	m_nRemotePort = nRemotePort;

	m_nReconnect = nReconnect;

	_RET(SUCCESS);
}
