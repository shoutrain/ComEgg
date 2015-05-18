#ifndef CNETWORK_HANDLE
#define CNETWORK_HANDLE

#include "NetworkCommon.h"
#include "CNetworkConf.h"

// transaction level
class CNetworkHandle
{
public:
	CNetworkHandle()
	{
		memset((void *)&m_MsgInfo, 0, sizeof(TMsgInfo));
		memset(m_Buf, 0, REV_BUFFER_MAX_SIZE);
		m_nRecvSize = 0;
	}

	virtual int Send(const ub_1 *pBuffer,
					 size_ nSize,
					 const ch_1 *pszIP = null_v,
					 ub_2 nPort = 0) = 0;

	ret_ CheckSend(const CPDUInfo *pPDUInfo,
				   const ub_1 *pMsg,
				   size_ nSize);

	const ch_1 *GetLocalIP() const
	{
		return m_MsgInfo.sLocalIP;
	}

	ub_2 GetLocalPort() const
	{
		return m_MsgInfo.nLocalPort;
	}

	const ch_1 *GetRemoteIP() const
	{
		return m_MsgInfo.sRemoteIP;
	}

	ub_2 GetRemotePort() const
	{
		return m_MsgInfo.nRemotePort;
	}

protected:
	ret_ Open();
	ret_ Close();
	ret_ OnMessage(const ub_1 *pMsg,
				   size_ nSize,
				   const TMsgInfo *pMsgInfo);

	virtual const CNetworkConf *GetConf() const = 0;

	TMsgInfo m_MsgInfo;

	b_1		m_Buf[REV_BUFFER_MAX_SIZE];
	size_	m_nRecvSize;
};

#endif // CNETWORK_HANDLE
