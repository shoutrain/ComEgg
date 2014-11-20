#include "COptGetAddress.h"

void COptGetAddress::Work(const TMessageUnit *pTMU)
{
	if (!pTMU)
		throw OPERATOR_OPERAITON_ERROR;

	try
	{
		if (m_bRemote)
		{
			*m_pIP->Value(pTMU)	= v_((ch_1 *)(pTMU->msgInfo->remoteIP));
			*m_pPort->Value(pTMU)	= v_((ub_2)(pTMU->msgInfo->remotePort));
		}
		else
		{
			*m_pIP->Value(pTMU)	= v_((ch_1 *)(pTMU->msgInfo->localIP));
			*m_pPort->Value(pTMU)	= v_((ub_2)(pTMU->msgInfo->localPort));
		}
	}
	catch (...)
	{
		throw OPERATOR_OPERAITON_ERROR;
	}
}
