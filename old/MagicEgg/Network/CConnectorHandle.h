#ifndef CCONNECTOR_HANDLE_H
#define CCONNECTOR_HANDLE_H

#include "CConnectionHandle.h"
#include "CConnectorConf.h"

class CConnector;

class CConnectorHandle: public CConnectionHandle
{
public:
	CConnectorHandle(): CConnectionHandle()
	{
		m_pConf = null_v;
	}

protected:
	virtual const CNetworkConf *GetConf() const
	{
		return (const CNetworkConf *)m_pConf;
	}

	virtual ret_ OnOpen(const ub_1 *pObj);
	virtual ret_ OnClose();

private:
	CConnectorConf *m_pConf;
};

#endif // CCONNECTOR_HANDLE_H
