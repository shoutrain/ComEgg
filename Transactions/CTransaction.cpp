#include "CTransaction.h"

ret_ CTransaction::Allocate(CProcessor *&pUnit)
{
	_START(TRANSACTION_ALLOCATE);

#ifdef _DEBUG_
	if (pUnit)
		_RET(PARAMETER_NOT_NULL | PARAMETER_1);
#endif

	_RET_BY(m_Resource.Allocate(pUnit));
}

ret_ CTransaction::Release(CProcessor *&pUnit)
{
	_START(TRANSACTION_RELEASE);

#ifdef _DEBUG_
	if (!pUnit)
		_RET(PARAMETER_NULL | PARAMETER_1);
#endif

	_RET_BY(m_Resource.Release(pUnit));
}
