#include "CNetworkHandle.h"

ret_ CNetworkHandle::Open()
{
	_START(OPEN);

	CTransaction *pTransaction = (CTransaction *)GetConf()->getTransaction();
	ret_ Ret = pTransaction->Allocate(m_pProcessor);

	if (SUCCESS != _ERR(Ret))
		_RET(_ERR(Ret));

    m_pProcessor->setHandle(this);
    m_pProcessor->execNormalHandle(&m_MsgInfo, START_HANDLE);

	_RET(SUCCESS);
}

ret_ CNetworkHandle::Close()
{
	_START(CLOSE);

	if (!m_pProcessor)
		_RET(FAILURE);

    m_pProcessor->execNormalHandle(&m_MsgInfo, OVER_HANDLE);
    m_pProcessor->reset();

	CTransaction *pTransaction = (CTransaction *)GetConf()->getTransaction();
	
	pTransaction->Release(m_pProcessor);

	_RET(SUCCESS);
}

ret_ CNetworkHandle::CheckSend(const CPduInfo *pPDUInfo,
							   const ub_1 *pMsg,
							   size_ nSize)
{
	_START(CHECK_SEND);

#ifdef _DEBUG_
	if (!pPDUInfo)
		_RET(PARAMETER_NULL | PARAMETER_1);

	if (!pMsg)
		_RET(PARAMETER_NULL | PARAMETER_2);

	if (0 == size)
		_RET(PARAMETER_ERROR | PARAMETER_3);
#endif

    CNodeConf *pConf = (CNodeConf *) GetConf();

#ifdef _DEBUG_
	if (!pConf)
		_RET(NO_ELEMENT_IN_CONTAINER);
#endif

	CProtocolInfo *pProtocol = (CProtocolInfo *)pConf->getProtocol();

#ifdef _DEBUG_
	if (!pProtocol)
		_RET(NO_ELEMENT_IN_CONTAINER);
#endif

	//
	try
	{
		size_ *pnSize = (size_ *)(pMsg +
                pConf->getSizeId()->offset(pMsg, nSize));
		*pnSize = nSize;
	}
	catch (error_code err)
	{
		_RET(err);
	}


	//
	try
	{
		v_ CommandID((size_ *)(pMsg +
                pConf->getCommandId()->offset(pMsg, nSize)));

		ret_ Ret = pConf->IdentifyPDU(pPDUInfo, CommandID, DIRECTION_OUT);

		if (SUCCESS != _ERR(Ret))
			_RET_BY(Ret);
	}
	catch (error_code err)
	{
		_RET(err);
	}

	_RET(SUCCESS);
}

ret_ CNetworkHandle::OnMessage(const ub_1 *pMsg,
							   size_ nSize,
							   const TMsgInfo *pMsgInfo)
{
	_START(ON_MESSAGE);

#ifdef _DEBUG_
	if (!pMsg)
		_RET(PARAMETER_NULL | PARAMETER_1);

	if (0 == size)
		_RET(PARAMETER_ERROR | PARAMETER_2);

	if (!pMsgInfo)
		_RET(PARAMETER_NULL | PARAMETER_3);
#endif

    CNodeConf *pConf = (CNodeConf *) GetConf();

#ifdef _DEBUG_
	if (!pConf)
		_RET(NO_ELEMENT_IN_CONTAINER);
#endif

	CProtocolInfo *pProtocol = (CProtocolInfo *)pConf->getProtocol();

#ifdef _DEBUG_
	if (!pProtocol)
		_RET(NO_ELEMENT_IN_CONTAINER);
#endif

    CPduInfo *pPDUInfo = null_v;

	try
	{
		v_ CommandID((size_ *)(pMsg +
                pConf->getCommandId()->offset(pMsg, nSize)));
		ret_ Ret = pConf->IdentifyID(CommandID, pPDUInfo, DIRECTION_IN);

		if (SUCCESS != _ERR(Ret))
			_RET_BY(Ret);
	}
	catch (error_code err)
	{
		_RET(err);
	}

#ifdef _DEBUG_
	if (!m_pProcessor)
		_RET(FAILURE);
#endif

    _RET_BY(m_pProcessor->execMsgHandle(pPDUInfo, pMsg, nSize, pMsgInfo,
            DIRECTION_IN));
}
