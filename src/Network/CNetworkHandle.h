#ifndef CNETWORK_HANDLE
#define CNETWORK_HANDLE

#include "NetworkCommon.h"
#include "CNodeConf.h"

// transaction level
class CNetworkHandle: public CBaseClass
{
public:
	CNetworkHandle(class_sign ClassID): CBaseClass(ClassID)
	{
		m_pProcessor = null_v;
        memset((obj_) &m_MsgInfo, 0, sizeof(TMsgInfo));
		memset(m_Buf, 0, REV_BUFFER_MAX_SIZE);
		m_nRecvSize = 0;
	}

	virtual int Send(const ub_1 *pBuffer,
					 size_ nSize,
					 const ch_1 *pszIP = null_v,
					 ub_2 nPort = 0) = 0;

    ret_ CheckSend(const CPduInfo *pPDUInfo,
				   const ub_1 *pMsg,
				   size_ nSize);

	const ch_1 *GetLocalIP() const
	{
		return (const ch_1 *)m_MsgInfo.localIP;
	}

	ub_2 GetLocalPort() const
	{
		return m_MsgInfo.localPort;
	}

	const ch_1 *GetRemoteIP() const
	{
		return (const ch_1 *)m_MsgInfo.remoteIP;
	}

	ub_2 GetRemotePort() const
	{
		return m_MsgInfo.remotePort;
	}

protected:
	ret_ Open();
	ret_ Close();
	ret_ OnMessage(const ub_1 *pMsg,
				   size_ nSize,
				   const TMsgInfo *pMsgInfo);

    virtual const CNodeConf *GetConf() const = 0;

	CProcessor	*m_pProcessor;
	TMsgInfo	m_MsgInfo;

	b_1		m_Buf[REV_BUFFER_MAX_SIZE];
	size_	m_nRecvSize;
};

#endif // CNETWORK_HANDLE
