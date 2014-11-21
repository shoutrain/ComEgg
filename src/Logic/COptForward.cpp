#include "COptForward.h"

#include "../Network/NetworkCommon.h"

void COptForward::Work(const TMessageUnit *pTMU)
{
	try
	{
		TMsgInfo *pMsgInfo = ((TMessageUnit *)pTMU)->msgInfo;
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
			strncpy(MsgInfo.localIP, pMsgInfo->localIP, IP_MAX_LENGTH);
			MsgInfo.localPort	= pMsgInfo->localPort;
			strncpy(MsgInfo.remoteIP, (const ch_1 *)*pIP, IP_MAX_LENGTH);
			MsgInfo.remotePort = (ub_2)*pPort;

			pMsgInfo = &MsgInfo;
		}

		if (SUCCESS != _ERR(((CProcessor *)pProcessor)->Send(
                (const CPduInfo *) ((TMessageUnit *) pTMU)->pduInfo,
								((TMessageUnit *)pTMU)->message,
								((TMessageUnit *)pTMU)->size,
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
