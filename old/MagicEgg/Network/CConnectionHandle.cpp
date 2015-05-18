#include "CConnectionHandle.h"

ret_ CConnectionHandle::Send(const ub_1 *pBuffer,
							 size_ nSize,
							 const ch_1 *pszIP,
							 ub_2 nPort)
{
#ifdef _DEBUG_
	if (!pBuffer)
		return PARAMETER_NULL | PARAMETER_1;

	if (0 == nSize)
		return PARAMETER_ERROR | PARAMETER_2;
#endif

	if (-1 == peer_.send_n((obj_)pBuffer, (size_t)nSize))
	{
		ACE_Svc_Handler<ACE_SOCK_STREAM, ACE_MT_SYNCH>::close();
		CNetworkHandle::Close();

		return FAILURE;
	}

	return SUCCESS;
}
