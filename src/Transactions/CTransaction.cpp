#include "CTransaction.h"

ret_ CTransaction::Allocate(CProcessor *&unit)
{
	_START(TRANSACTION_ALLOCATE);

#ifdef _DEBUG_
	if (unit)
		_RET(PARAMETER_NOT_NULL | PARAMETER_1);
#endif

    _RET_BY(m_Resource.Allocate(unit));
}

ret_ CTransaction::Release(CProcessor *&unit)
{
	_START(TRANSACTION_RELEASE);

#ifdef _DEBUG_
	if (!unit)
		_RET(PARAMETER_NULL | PARAMETER_1);
#endif

    _RET_BY(m_Resource.Release(unit));
}
