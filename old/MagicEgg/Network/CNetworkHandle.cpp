#include "CNetworkHandle.h"

#include "../UI/CUIManager.h"
#include "../UI/CContainer.h"

ret_ CNetworkHandle::Open()
{
	printf("The network works now!\n");
	
	return SUCCESS;
}

ret_ CNetworkHandle::Close()
{
	printf("The network are broken now, you'd better wait or close it.\n");

	return SUCCESS;
}

ret_ CNetworkHandle::CheckSend(const CPDUInfo *pPDUInfo,
							   const ub_1 *pMsg,
							   size_ nSize)
{
#ifdef _DEBUG_
	if (!pPDUInfo)
		return PARAMETER_NULL | PARAMETER_1;

	if (!pMsg)
		return PARAMETER_NULL | PARAMETER_2;

	if (0 == nSize)
		return PARAMETER_ERROR | PARAMETER_3;
#endif

	CNetworkConf *pConf = (CNetworkConf *)GetConf();

#ifdef _DEBUG_
	if (!pConf)
		return NO_ELEMENT_IN_CONTAINER;
#endif

	//
	try
	{
		size_ *pnSize = (size_ *)(pMsg +
								  pConf->GetSizeID()->Offset(pMsg, nSize));
		*pnSize = nSize;
	}
	catch (error_code err)
	{
		return err;
	}

	//
	try
	{
		v_ CommandID((size_ *)(pMsg +
							   pConf->GetCommandID()->Offset(pMsg, nSize)));

		ret_ Ret = pConf->IdentifyPDU(pPDUInfo, CommandID, DIRECTION_OUT);

		if (SUCCESS != Ret)
			return Ret;
	}
	catch (error_code err)
	{
		return err;
	}

	return SUCCESS;
}

ret_ CNetworkHandle::OnMessage(const ub_1 *pMsg,
							   size_ nSize,
							   const TMsgInfo *pMsgInfo)
{
#ifdef _DEBUG_
	if (!pMsg)
		return PARAMETER_NULL | PARAMETER_1;

	if (0 == nSize)
		return PARAMETER_ERROR | PARAMETER_2;

	if (!pMsgInfo)
		return PARAMETER_NULL | PARAMETER_3;
#endif

	CNetworkConf *pConf = (CNetworkConf *)GetConf();

#ifdef _DEBUG_
	if (!pConf)
		return NO_ELEMENT_IN_CONTAINER;
#endif

	CPDUInfo *pPDUInfo = null_v;

	try
	{
		v_ CommandID((size_ *)(pMsg +
							   pConf->GetCommandID()->Offset(pMsg, nSize)));
		ret_ Ret = pConf->IdentifyID(CommandID, pPDUInfo, DIRECTION_IN);

		if (SUCCESS != Ret)
			return Ret;
	}
	catch (error_code err)
	{
		return err;
	}

	TMU tmu;

	tmu.pPDUInfo = pPDUInfo;
	tmu.pMessage = (ub_1 *)pMsg;
	tmu.nSize = nSize;
	tmu.pMsgInfo = (TMsgInfo *)pMsgInfo;
	
	CContainer *pContainer = CUIManager::Instance()->GetCurContainer();

	if (pContainer)
		pContainer->OnMessage(&tmu);

	return SUCCESS;
}
