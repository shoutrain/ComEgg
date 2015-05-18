#include "CReceiverHandle.h"
#include "CReceiver.h"

ret_ CReceiverHandle::OnOpen(const ub_1 *pObj)
{
	_START(ON_OPEN);

#ifdef _DEBUG_
	if (!pObj)
		_RET(PARAMETER_NULL | PARAMETER_1);
#endif

	m_pConf = (CReceiverConf *)((CReceiver *)pObj)->GetConf();

	_RET(SUCCESS);
}

ret_ CReceiverHandle::Check(const TMsgInfo *pMsgInfo)
{
	_START(CHECK);

	if (!m_pConf->IPFilter().IPPermit((ch_1 *)pMsgInfo->sRemoteIP))
		_RET(FROBID_USE);

	_RET(SUCCESS);
}
