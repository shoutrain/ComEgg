#include "CConnectorHandle.h"

#include "CConnector.h"

ret_ CConnectorHandle::OnOpen(const ub_1 *pObj)
{
	_START(ON_OPEN);

#ifdef _DEBUG_
	if (!pObj)
		_RET(PARAMETER_NULL | PARAMETER_1);
#endif
	m_pConnector = (CConnector *)pObj;
	m_pConf		 = (CConnectorConf *)m_pConnector->getConf();

	_RET(SUCCESS);
}

ret_ CConnectorHandle::OnClose()
{
	_START(ON_CLOSE);

	if (m_pConnector)
		m_pConnector->Disconnect();

	_RET(SUCCESS);
}
