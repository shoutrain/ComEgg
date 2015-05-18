#ifndef CRECEIVER_HANDLE_H
#define CRECEIVER_HANDLE_H

#include "CDatagramHandle.h"
#include "CReceiverConf.h"

class CReceiverHandle: public CDatagramHandle
{
public:
	CReceiverHandle(): CDatagramHandle(CRECEIVERHANDLE)
	{
		m_pConf = null_v;
	}

protected:
	virtual ret_ OnOpen(const ub_1 *pObj);
	virtual ret_ Check(const TMsgInfo *pMsgInfo);

	virtual const CNetworkConf *GetConf() const
	{
		return (const CNetworkConf *)m_pConf;
	}

private:
	CReceiverConf *m_pConf;
};

#endif // CRECEIVER_HANDLE_H
