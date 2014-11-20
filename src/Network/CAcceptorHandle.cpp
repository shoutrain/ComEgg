#include "CAcceptorHandle.h"

#include "CAcceptor.h"

ret_ CAcceptorHandle::OnOpen(const ub_1 *pObj)
{
	_START(ON_OPEN);

#ifdef _DEBUG_
	if (!pObj)
		_RET(PARAMETER_NULL | PARAMETER_1);
#endif

	m_pConf = (CAcceptorConf *)((CAcceptor *)pObj)->getConf();

	if (!m_pConf->OpenConnection())
		_RET(FROBID_USE);

	ACE_INET_Addr Addr;

	peer().get_remote_addr(Addr);

	if (!m_pConf->IPFilter().IPPermit((const ch_1 *)Addr.get_host_addr()))
		_RET(FROBID_USE);

	_RET(SUCCESS);
}

ret_ CAcceptorHandle::OnClose()
{
	_START(ON_CLOSE);

	m_pConf->CloseConnection();

	_RET(SUCCESS);
}
