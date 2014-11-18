#include "CSenderHandle.h"

#include "CSender.h"

ret_ CSenderHandle::OnOpen(const ub_1 *pObj)
{
	_START(ON_OPEN);

#ifdef _DEBUG_
	if (!pObj)
		_RET(PARAMETER_NULL | PARAMETER_1);
#endif

	m_pConf = (CSenderConf *)((CSender *)pObj)->GetConf();

	_RET(SUCCESS);
}
