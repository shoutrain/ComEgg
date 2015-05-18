#include "COptWaitMessage.h"

#include "../UI/CUIManager.h"
#include "../UI/CContainer.h"
#include "../Protocols/CProtocolManager.h"
#include "../Protocols/CProtocolInfo.h"

class CPDUInfo;

void COptWaitMessage::Work(const TMU *pTMU)
{
	CPDUInfo *pPDUInfo = null_v;

	if (SUCCESS != CProtocolManager::Instance()->GetProtocol()->GetPDU(
			m_szMessageName, pPDUInfo))
	{
		throw OPERATOR_OPERAITON_ERROR;
	}

	CContainer *pContainer = CUIManager::Instance()->GetCurContainer();

	if (pContainer)
		pContainer->WaitMessage(pPDUInfo);
	else
		throw OPERATOR_OPERAITON_ERROR;
}



