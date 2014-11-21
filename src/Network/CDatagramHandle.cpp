#include "CDatagramHandle.h"

ret_ CDatagramHandle::Send(const ub_1 *pBuffer, 
						   size_ nSize, 
						   const ch_1 *pszIP, 
						   ub_2 nPort)
{
	_START(HANDLE_SEND);

#ifdef _DEBUG_
	if (!pBuffer)
		_RET(PARAMETER_NULL | PARAMETER_1);

	if (0 == size)
		_RET(PARAMETER_ERROR | PARAMETER_2);

	if (!pszIP)
		_RET(PARAMETER_NULL | PARAMETER_3);
#endif

	if (m_bIsInited)
	{
		ACE_INET_Addr RemoteAddr(nPort, pszIP);

		if (-1 != m_Peer.send(pBuffer, nSize, RemoteAddr))
			_RET(SUCCESS);
	}

	_RET(FAILURE);
}

