#include "COptGetAddress.h"

void COptGetAddress::Work(const TMU *pTMU)
{
	if (!pTMU)
		throw OPERATOR_OPERAITON_ERROR;

	try
	{
		if (m_bRemote)
		{
			*m_pIP->Value(pTMU)	= v_((ch_1 *)(pTMU->pMsgInfo->sRemoteIP));
			*m_pPort->Value(pTMU)	= v_((ub_2)(pTMU->pMsgInfo->nRemotePort));
		}
		else
		{
			*m_pIP->Value(pTMU)	= v_((ch_1 *)(pTMU->pMsgInfo->sLocalIP));
			*m_pPort->Value(pTMU)	= v_((ub_2)(pTMU->pMsgInfo->nLocalPort));
		}
	}
	catch (...)
	{
		throw OPERATOR_OPERAITON_ERROR;
	}
}
