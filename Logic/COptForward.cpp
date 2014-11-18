#include "COptForward.h"

#include "../Network/NetworkCommon.h"

void COptForward::Work(const TMU *pTMU)
{
	try
	{
		TMsgInfo *pMsgInfo = ((TMU *)pTMU)->pMsgInfo;
		TMsgInfo MsgInfo;
		const CProcessor *pProcessor = GetContainer();

		if (!pProcessor)
			throw OPERATOR_OPERAITON_ERROR;

		if (TCP_SEND == m_SendType && m_pObject)
		{
			v_ *pValue = m_pObject->Value(pTMU);

			pProcessor = (CProcessor *)(obj_)*pValue;
		}
		else if (UDP_SEND == m_SendType && m_pIP && m_pPort)
		{
			v_ *pIP		= m_pIP->Value(pTMU);
			v_ *pPort	= m_pPort->Value(pTMU);

			memset(&MsgInfo, 0, sizeof(TMsgInfo));
			strncpy(MsgInfo.sLocalIP, pMsgInfo->sLocalIP, IP_MAX_LENGTH);
			MsgInfo.nLocalPort	= pMsgInfo->nLocalPort;
			strncpy(MsgInfo.sRemoteIP, (const ch_1 *)*pIP, IP_MAX_LENGTH);
			MsgInfo.nRemotePort = (ub_2)*pPort;

			pMsgInfo = &MsgInfo;
		}

		if (SUCCESS != _ERR(((CProcessor *)pProcessor)->Send(
								(const CPDUInfo *)((TMU *)pTMU)->pPDUInfo,
								((TMU *)pTMU)->pMessage,
								((TMU *)pTMU)->nSize,
								pMsgInfo)))
		{
			throw OPERATOR_OPERAITON_ERROR;
		}
	}
	catch (...)
	{
		throw;
	}
}
