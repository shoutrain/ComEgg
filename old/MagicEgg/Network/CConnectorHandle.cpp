#include "CConnectorHandle.h"

#include "CNetworkManager.h"
#include "CConnector.h"

ret_ CConnectorHandle::OnOpen(const ub_1 *pObj)
{
#ifdef _DEBUG_
	if (!pObj)
		return (PARAMETER_NULL | PARAMETER_1);
#endif
	CConnector *pConnector = (CConnector *)pObj;

#ifdef _DEBUG_
	if (pConnector != (CConnector *)CNetworkManager::Instance()->GetNetwork())
		return (PARAMETER_ERROR | PARAMETER_1);
#endif

	m_pConf = (CConnectorConf *)pConnector->GetConf();

	return SUCCESS;
}

ret_ CConnectorHandle::OnClose()
{
	CConnector *pConnector = (CConnector *)CNetworkManager::Instance()->GetNetwork();
	
	pConnector->SetHandle(null_v);

	return SUCCESS;
}
