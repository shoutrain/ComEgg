#ifndef CDATAGRAM_HANDLE_H
#define CDATAGRAM_HANDLE_H

#include "NetworkCommon.h"
#include "CNetworkHandle.h"

struct TMsgInfo;

// UDP Level
class CDatagramHandle: public ACE_Task<ACE_MT_SYNCH>, public CNetworkHandle
{
public:
	CDatagramHandle(class_sign ClassID): CNetworkHandle(ClassID)
	{
		m_bIsInited = false_v;
	}

	int open(ub_2 nPort, ub_1 *pObj)
	{
		if (SUCCESS != _ERR(OnOpen(pObj)))
			return -1;

		ACE_INET_Addr LocalAddr(nPort, "127.0.0.1");

		if (-1 == m_Peer.open(LocalAddr))
			return -1;

		m_bIsInited = true_v;
		strncpy(m_MsgInfo.localIP, LocalAddr.get_host_addr(),
				IP_MAX_LENGTH_SIGN);
		m_MsgInfo.localPort = LocalAddr.get_port_number();

		if (SUCCESS != _ERR(CNetworkHandle::Open()))
			return -1;

		if (-1 ==
				ACE_Reactor::instance()->register_handler(this,
												  ACE_Event_Handler::READ_MASK))
			return -1;

		activate();

		return 0;
	}

	int handle_input(ACE_HANDLE)
	{
		ACE_INET_Addr RemoteAddr;

		m_nRecvSize = m_Peer.recv(m_Buf, REV_BUFFER_MAX_SIZE, RemoteAddr);

		ACE_Message_Block *pMsg = null_v;

		if (0 < m_nRecvSize)
		{
			strncpy(m_MsgInfo.remoteIP, RemoteAddr.get_host_addr(),
					IP_MAX_LENGTH_SIGN);
			m_MsgInfo.remotePort = RemoteAddr.get_port_number();

			if (FROBID_USE == _ERR(Check(&m_MsgInfo)))
				return 0;

			pMsg = new ACE_Message_Block(m_nRecvSize + sizeof(TMsgInfo));

			if (-1 == pMsg->copy((const char *)&m_MsgInfo, sizeof(TMsgInfo)))
				goto BREAK_EXIT_A;

			if (-1 == pMsg->copy(m_Buf, m_nRecvSize))
				goto BREAK_EXIT_A;

			putq(pMsg);
			memset(m_Buf, 0, m_nRecvSize);
			memset(m_MsgInfo.remoteIP, 0, IP_MAX_LENGTH);
			m_MsgInfo.remotePort = 0;

			return 0;
		}

BREAK_EXIT_A:
		pMsg->release();

		return -1;
	}

    ACE_HANDLE get_handle(none_) const
	{
		if (m_bIsInited)
			return m_Peer.get_handle();
		else
			return null_v;
	}

	int svc()
	{
		ACE_Message_Block *pMsg = 0;

		while (true_v)
			if (-1 != getq(pMsg))
			{
				TMsgInfo *pMsgInfo = (TMsgInfo *)pMsg->rd_ptr();

				pMsg->rd_ptr(sizeof(TMsgInfo));

				ub_1 *pBuf = (ub_1 *)pMsg->rd_ptr();

				CNetworkHandle::OnMessage(pBuf, (size_)pMsg->length(),
						pMsgInfo);
				pMsg->release();
			}

		return 0;
	}

	virtual int Send(const ub_1 *pBuffer,
					 size_ nSize,
					 const ch_1 *pszIP = null_v,
					 ub_2 nPort = 0);

protected:
	virtual ret_ OnOpen(const ub_1 *pObj)	= 0;
	virtual ret_ Check(const TMsgInfo *pMsgInfo)
	{
		_START(CHECK);
		_RET(SUCCESS);
	};

    virtual const CNodeConf *GetConf() const
	{
		return null_v;
	}

private:
	ACE_SOCK_Dgram	m_Peer;
	bool_			m_bIsInited;
};

#endif // CDATAGRAM_HANDLE_H
