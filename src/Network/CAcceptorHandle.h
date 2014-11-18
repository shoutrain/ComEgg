#ifndef CACCEPTOR_HANDLE_H
#define CACCEPTOR_HANDLE_H

#include "CConnectionHandle.h"
#include "CAcceptorConf.h"

class CAcceptorHandle: public CConnectionHandle
{
public:
	CAcceptorHandle(): CConnectionHandle(CACCEPTORHANDLE)
	{
		m_pConf = null_v;
	}

protected:
	virtual const CNetworkConf *GetConf() const
	{
		return (const CNetworkConf *)m_pConf;
	}

	virtual ret_ OnOpen(const ub_1 *Obj);
	virtual ret_ OnClose();

private:
	CAcceptorConf *m_pConf;
};

#endif // CACCEPTOR_HANDLE_H
