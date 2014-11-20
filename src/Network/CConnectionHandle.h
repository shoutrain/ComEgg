#ifndef CONNECTION_HANDLE_H
#define CONNECTION_HANDLE_H

#include "CNetworkHandle.h"

// TCP level
class CConnectionHandle: public ACE_Svc_Handler<ACE_SOCK_STREAM, ACE_MT_SYNCH>,
						 public CNetworkHandle
{
public:
	CConnectionHandle(class_sign ClassID): CNetworkHandle(ClassID)
	{
		m_bIsRunning = false_v;
	}

	int open(void *p)
	{
		if (SUCCESS != _ERR(OnOpen((const ub_1 *)p)))
			return -1;

		ACE_INET_Addr	LocalAddr;
		ACE_INET_Addr	RemoteAddr;

		if (peer_.get_local_addr(LocalAddr))
			return -1;

		if (peer_.get_remote_addr(RemoteAddr))
			return -1;

		strncpy(m_MsgInfo.localIP, LocalAddr.get_host_addr(),
				IP_MAX_LENGTH_SIGN);
		m_MsgInfo.localPort	= LocalAddr.get_port_number();
		strncpy(m_MsgInfo.remoteIP, RemoteAddr.get_host_addr(),
				IP_MAX_LENGTH_SIGN);
		m_MsgInfo.remotePort	= RemoteAddr.get_port_number();

		if (SUCCESS != _ERR(CNetworkHandle::Open()))
			return -1;

		if (-1 ==
				ACE_Reactor::instance()->register_handler(
					this,
					ACE_Event_Handler::READ_MASK))
		{
			return -1;
		}

		m_bIsRunning = true_v;
		activate();

		return 0;
	}

	int handle_input(ACE_HANDLE)
	{
		m_nRecvSize = peer().recv(m_Buf, REV_BUFFER_MAX_SIZE);

		if (0 < m_nRecvSize && REV_BUFFER_MAX_SIZE >= m_nRecvSize)
		{
			ACE_Message_Block *pMsg = new ACE_Message_Block(m_nRecvSize);

			if (-1 != pMsg->copy(m_Buf, m_nRecvSize))
			{
				putq(pMsg);
				memset(m_Buf, 0, m_nRecvSize);

				return 0;
			}
			else
			{
				pMsg->release();
			}

		}

		return -1;
	}

	int svc()
	{
		while (m_bIsRunning)
		{
			ACE_Message_Block *pMsg = null_v;
			ACE_Time_Value timer(1, 0);

			if (-1 != getq(pMsg, &timer))
			{
				CNetworkHandle::OnMessage((ub_1 *)pMsg->rd_ptr(),
										  (size_)pMsg->length(),
										  &m_MsgInfo);
				pMsg->release();
			}
		}
		
		return 0;
	}

	int close(ulong)
	{
		// Just overriding to avoid call handle_close twice
		return 0;
	}
	
	int handle_close(ACE_HANDLE Handle, ACE_Reactor_Mask Mask)
	{
		m_bIsRunning = false_v;
		OnClose();
		CNetworkHandle::Close();

		return -1;
	}

	virtual int Send(const ub_1 *pBuffer,
					 size_ nSize,
					 const ch_1 *pszIP = null_v,
					 ub_2 nPort = 0);

protected:
	virtual const CNetworkConf *GetConf() const
	{
		return null_v;
	}

	virtual ret_ OnOpen(const ub_1 *pObj)	= 0;
	virtual ret_ OnClose()					= 0;

private:
	bool_ m_bIsRunning;
};

#endif // CONNECTION_HANDLE_H
