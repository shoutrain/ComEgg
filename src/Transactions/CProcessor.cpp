#include "CProcessor.h"

#include "CTransactionManager.h"

#include "../Logic/LogicCommon.h"
#include "../Network/CNetworkHandle.h"
#include "../Tools/CRegister.h"

CProcessor::CProcessor(): CBaseClass(CPROCESSOR)
{
	m_Data.SetParent((const CData *)&CTransactionManager::Instance()->Data());

	opt_unit Unit;

	Unit.pData		= &m_Data;
	Unit.pContainer = this;
	Unit.pParent	= null_v;

	for (size_ i = 0; i < (size_)NORMAL_HANDLE; i++)
		m_NormalHandle[i].Initialize(&Unit);

	m_pHandle = null_v;
}

CProcessor::CProcessor(const CProcessor &Processor): CBaseClass(CPROCESSOR)
{
	m_OrnData	= Processor.m_OrnData;
	m_Data		= Processor.m_Data;
	m_Data.SetParent((const CData *)&CTransactionManager::Instance()->Data());

	opt_unit Unit;

	Unit.pContainer = this;
	Unit.pData		= &m_Data;
	Unit.pParent	= null_v;

	for (size_ i = 0; i < (size_)NORMAL_HANDLE; i++)
	{
		m_NormalHandle[i] = Processor.m_NormalHandle[i];
		m_NormalHandle[i].Initialize(&Unit);
	}

	m_pHandle = null_v;

	map_handle::const_iterator pos;

	for (pos = Processor.m_HandleInMap.begin();
		 pos != Processor.m_HandleInMap.end(); pos++)
	{
		CProgram *pHandle = new CProgram(*pos->second);

		m_HandleInMap.insert(map_handle::value_type(pos->first, pHandle));
	}

	for (pos = Processor.m_HandleOutMap.begin();
		 pos != Processor.m_HandleOutMap.end(); pos++)
	{
		CProgram *pHandle = new CProgram(*pos->second);

		m_HandleOutMap.insert(map_handle::value_type(pos->first, pHandle));
	}
}

const CProcessor &CProcessor::operator =(const CProcessor &Processor)
{
	if (this != &Processor)
	{
		Stop();

		m_OrnData	= Processor.m_OrnData;
		m_Data		= Processor.m_Data;

		opt_unit Unit;

		Unit.pContainer = this;
		Unit.pData		= &m_Data;
		Unit.pParent	= null_v;

		for (size_ i = 0; i < (size_)NORMAL_HANDLE; i++)
		{
			m_NormalHandle[i] = Processor.m_NormalHandle[i];
			m_NormalHandle[i].Initialize(&Unit);
		}

		m_pHandle = null_v;

		map_handle::const_iterator pos;

		for (pos = Processor.m_HandleInMap.begin();
			 pos != Processor.m_HandleInMap.end(); pos++)
		{
			CProgram *pHandle = new CProgram(*pos->second);

			m_HandleInMap.insert(map_handle::value_type(pos->first, pHandle));
		}

		for (pos = Processor.m_HandleOutMap.begin();
			 pos != Processor.m_HandleOutMap.end(); pos++)
		{
			CProgram *pHandle = new CProgram(*pos->second);

			m_HandleOutMap.insert(map_handle::value_type(pos->first, pHandle));
		}
	}

	return *this;
}

ret_ CProcessor::Stop()
{
	_START(STOP);

	map_handle::iterator pos;

	for (pos = m_HandleInMap.begin(); pos != m_HandleInMap.end(); pos++)
	{
#ifdef _DEBUG_
		if (!pos->second)
			_RET(ELEMENT_NULL_IN_CONTAINER);
#endif
		_DEL(pos->second);
	}

	for (pos = m_HandleOutMap.begin(); pos != m_HandleOutMap.end(); pos++)
	{
#ifdef _DEBUG_
		if (!pos->second)
			_RET(ELEMENT_NULL_IN_CONTAINER);
#endif
		_DEL(pos->second);
	}

	m_HandleInMap.clear();
	m_HandleOutMap.clear();

	for (map_register::iterator pos_ = m_RegisterMap.begin();
		 pos_ != m_RegisterMap.end(); pos_++)
	{
#ifdef _DEBUG_
		if (!pos_->second)
			_RET(ELEMENT_NULL_IN_CONTAINER);
#endif

		for (set_register::iterator pos_1 = pos_->second->begin();
			 pos_1 != pos_->second->end(); pos_1++)
		{
			ch_1 *sCategory	= (ch_1 *)pos_->first.data();
			ch_1 *pszKey		= (ch_1 *)pos_1->data();
			ret_ Ret		=
				CRegister::Instance()->Unregister(sCategory, pszKey);

#ifdef _DEBUG_
			if (SUCCESS != _ERR(Ret))
				_RET_BY(Ret);
#endif

			CTransactionManager::Instance()->Unregister(sCategory, pszKey);
		}

		pos_->second->clear();
		_DEL(pos_->second);
	}

	m_RegisterMap.clear();

	_RET(SUCCESS);
}

ret_ CProcessor::Reset()
{
	_START(RESET);

	m_Data = m_OrnData;

	for (size_ i = 0; i < (size_)NORMAL_HANDLE; i++)
		m_NormalHandle[i].Reset();

	m_pHandle = null_v;

	map_handle::iterator pos;

	for (pos = m_HandleInMap.begin(); pos != m_HandleInMap.end(); pos++)
	{
#ifdef _DEBUG_
		if (!pos->second)
			_RET(ELEMENT_NULL_IN_CONTAINER);
#endif
		((CProgram *)pos->second)->Reset();
	}

	for (pos = m_HandleOutMap.begin(); pos != m_HandleOutMap.end(); pos++)
	{
#ifdef _DEBUG_
		if (!pos->second)
			_RET(ELEMENT_NULL_IN_CONTAINER);
#endif
		((CProgram *)pos->second)->Reset();
	}

	for (map_register::iterator pos_ = m_RegisterMap.begin();
		 pos_ != m_RegisterMap.end(); pos_++)
	{
#ifdef _DEBUG_
		if (!pos_->second)
			_RET(ELEMENT_NULL_IN_CONTAINER);
#endif

		for (set_register::iterator pos_1 = pos_->second->begin();
			 pos_1 != pos_->second->end(); pos_1++)
		{
			ch_1 *sCategory	= (ch_1 *)pos_->first.data();
			ch_1 *pszKey		= (ch_1 *)pos_1->data();
			ret_ Ret		=
				CRegister::Instance()->Unregister(sCategory, pszKey);

#ifdef _DEBUG_
			if (SUCCESS != _ERR(Ret))
				_RET_BY(Ret);
#endif

			CTransactionManager::Instance()->Unregister((const ch_1 *)sCategory,
														pszKey);
		}

		pos_->second->clear();
		_DEL(pos_->second);
	}

	m_RegisterMap.clear();

	_RET(SUCCESS);
}

ret_ CProcessor::SetMsgHandle(const CProgram &Program,
							  EDirection Direction,
        const CPduInfo *pPDUInfo)
{
	_START(SET_MSG_HANDLE);

#ifdef _DEBUG_
	if (DIRECTION_IN		!= Direction &&
		DIRECTION_OUT		!= Direction &&
		DIRECTION_ALL		!= Direction)

	{
		_RET(PARAMETER_TYPE_ERROR | PARAMETER_2);
	}

	if (!pPDUInfo)
		_RET(PARAMETER_NULL | PARAMETER_3);
#endif

	if (DIRECTION_IN == (EDirection)(Direction & DIRECTION_IN))
	{
#ifdef _DEBUG_
		map_handle::const_iterator pos = m_HandleInMap.find(pPDUInfo);

		if (pos != m_HandleInMap.end())
			_RET(ELEMENT_EXIST_IN_CONTAINER);
#endif

		CProgram *pHandle = new CProgram(Program);

		m_HandleInMap.insert(map_handle::value_type(pPDUInfo, pHandle));
	}

	if (DIRECTION_OUT == (EDirection)(Direction & DIRECTION_OUT))
	{
#ifdef _DEBUG_
		map_handle::const_iterator pos = m_HandleOutMap.find(pPDUInfo);

		if (pos != m_HandleOutMap.end())
			_RET(ELEMENT_EXIST_IN_CONTAINER);
#endif

		CProgram *pHandle = new CProgram(Program);

		m_HandleOutMap.insert(map_handle::value_type(pPDUInfo, pHandle));
	}

	_RET(SUCCESS);
}

ret_ CProcessor::ExecNormalHandle(const TMsgInfo *pMsgInfo, ENormalHandle enh)
{
	_START(EXEC_NORMAL_HANDLE);

	TMessageUnit tmu;

	memset(&tmu, 0, sizeof(TMessageUnit));
	tmu.msgInfo = (TMsgInfo *)pMsgInfo;

	try
	{
		m_NormalHandle[enh].Work(&tmu);
	}
	catch (error_code err)
	{
		_RET(err);
	}

	_RET(SUCCESS);
}

ret_ CProcessor::ExecMsgHandle(const CPduInfo *pPDUInfo,
							   const ub_1 *pMsg,
							   size_ nSize,
							   const TMsgInfo *pMsgInfo,
							   EDirection Direction)
{
	_START(EXEC_MSG_HANDLE);

#ifdef _DEBUG_
	if (!pPDUInfo)
		_RET(PARAMETER_NULL | PARAMETER_1);

	if (!pMsg)
		_RET(PARAMETER_NULL | PARAMETER_2);

	if (0 >= size)
		_RET(PARAMETER_ERROR | PARAMETER_3);

	if (DIRECTION_IN		!= Direction &&
		DIRECTION_OUT		!= Direction)
	{
		_RET(PARAMETER_TYPE_ERROR | PARAMETER_4);
	}
#endif

	TMessageUnit tmu;

    tmu.pduInfo = (CPduInfo *) pPDUInfo;
	tmu.message	= (ub_1 *)pMsg;
	tmu.size		= nSize;
	tmu.msgInfo	= (TMsgInfo *)pMsgInfo;

	opt_unit Unit;

	Unit.pData		= &m_Data;
	Unit.pContainer = this;
	Unit.pParent	= null_v;

	map_handle::const_iterator pos;

	if (DIRECTION_IN == Direction)
	{
		pos = m_HandleInMap.find(pPDUInfo);

		if (pos != m_HandleInMap.end())
		{
#ifdef _DEBUG_
			if (!pos->second)
				_RET(ELEMENT_NULL_IN_CONTAINER);
#endif

			try
			{
				((CProgram *)pos->second)->Initialize(&Unit);
				((CProgram *)pos->second)->Work(&tmu);
			}
			catch (error_code err)
			{
				_RET(err);
			}
		}
		else
		{
			try
			{
				m_NormalHandle[DEFAULT_IN_HANDLE].Work(&tmu);
			}
			catch (error_code err)
			{
				_RET(err);
			}
		}
	}
	else if (DIRECTION_OUT == Direction)
	{
		pos = m_HandleOutMap.find(pPDUInfo);

		if (pos != m_HandleOutMap.end())
		{
#ifdef _DEBUG_
			if (!pos->second)
				_RET(ELEMENT_NULL_IN_CONTAINER);
#endif

			try
			{
				((CProgram *)pos->second)->Initialize(&Unit);
				((CProgram *)pos->second)->Work(&tmu);
			}
			catch (error_code err)
			{
				_RET(err);
			}
		}
		else
		{
			try
			{
				m_NormalHandle[DEFAULT_OUT_HANDLE].Work(&tmu);
			}
			catch (error_code err)
			{
				_RET(err);
			}
		}
	}

	_RET(SUCCESS);
}

ret_ CProcessor::SetHandle(const CNetworkHandle *pHandle)
{
	_START(SET_HANDLE);

#ifdef _DEBUG_
	if (!pHandle)
		_RET(PARAMETER_NULL | PARAMETER_1);
#endif

	m_pHandle = (CNetworkHandle *)pHandle;

	_RET(SUCCESS);
}

ret_ CProcessor::Send(const CPduInfo *pPDUInfo,
					  const ub_1 *pMsg,
					  size_ nSize,
					  const TMsgInfo *pMsgInfo)
{
	_START(SEND);

#ifdef _DEBUG_
	if (!m_pHandle)
		_RET(FAILURE);

	if (!pPDUInfo)
		_RET(PARAMETER_NULL | PARAMETER_1);

	if (!pMsg)
		_RET(PARAMETER_NULL | PARAMETER_2);

	if (0 >= size)
		_RET(PARAMETER_ERROR | PARAMETER_3);

	if (!pMsgInfo)
		_RET(PARAMETER_NULL | PARAMETER_4);
#endif

	ret_ Ret = m_pHandle->CheckSend(pPDUInfo, pMsg, nSize);

	if (SUCCESS != _ERR(Ret))
		_RET_BY(Ret);

	TMsgInfo MsgInfo;

	memcpy(&MsgInfo, pMsgInfo, sizeof(TMsgInfo));
	memcpy(MsgInfo.localIP, m_pHandle->GetLocalIP(), IP_MAX_LENGTH);
	MsgInfo.localPort = m_pHandle->GetLocalPort();

	Ret = ExecMsgHandle(pPDUInfo, pMsg, nSize, &MsgInfo, DIRECTION_OUT);

	if (SUCCESS != _ERR(Ret))
		_RET(Ret);

	_RET_BY(m_pHandle->Send(pMsg,
							nSize,
							MsgInfo.remoteIP,
							MsgInfo.remotePort));
}

ret_ CProcessor::Register(const ch_1 *pszCategory,
						  const ch_1 *pszKey,
						  bool_ bIsCovered)
{
	_START(PROCESSOR_REGISTER);

#ifdef _DEBUG_
	if (!pszCategory)
		_RET(PARAMETER_NULL | PARAMETER_1);

	if (0 == pszCategory[0])
		_RET(PARAMETER_EMPTY | PARAMETER_1);

	if (!pszKey)
		_RET(PARAMETER_NULL | PARAMETER_2);

	if (0 == pszKey[0])
		_RET(PARAMETER_EMPTY | PARAMETER_2);
#endif

	try
	{
		v_		Varialbe((obj_)this);
		ret_	Ret = CRegister::Instance()->Register(pszCategory,
													  pszKey,
													  &Varialbe,
													  bIsCovered);

		if (SUCCESS != _ERR(Ret))
			_RET_BY(Ret);
	}
	catch (...)
	{
		_RET(DEFINE_VARIABLE_FAILURE);
	}

	map_register::iterator pos = m_RegisterMap.find(pszCategory);

	if (m_RegisterMap.end() != pos)
	{
		set_register::iterator pos_ = pos->second->find(pszKey);

		if (pos->second->end() == pos_)
			pos->second->insert(pszKey);
	}
	else
	{
		set_register *pSet = new set_register;

		pSet->insert(pszKey);
		m_RegisterMap.insert(map_register::value_type(pszCategory, pSet));
	}

    CProcessor *pProcessor = this;

	CTransactionManager::Instance()->Register(pszCategory,
											  pszKey,
											  pProcessor,
											  bIsCovered);

	_RET(SUCCESS);
}

ret_ CProcessor::Unregister(const ch_1 *pszCategory, const ch_1 *pszKey)
{
	_START(PROCESSOR_UNREGISTER);

#ifdef _DEBUG_
	if (!pszCategory)
		_RET(PARAMETER_NULL | PARAMETER_1);

	if (0 == pszCategory[0])
		_RET(PARAMETER_EMPTY | PARAMETER_1);

	if (!pszKey)
		_RET(PARAMETER_NULL | PARAMETER_2);

	if (0 == pszKey[0])
		_RET(PARAMETER_EMPTY | PARAMETER_2);
#endif

	CProcessor *pProcessor = null_v;

	if (SUCCESS == _ERR(CTransactionManager::Instance()->Search(pszCategory,
																pszKey,
																pProcessor)))
	{
#ifdef _DEUB_
		if (!pProcessor)
			_RET(ELEMENT_NULL_IN_CONTAINER);
#endif

		map_register::iterator pos = m_RegisterMap.find(pszCategory);

		if (m_RegisterMap.end() != pos)
		{
			set_register::iterator pos_ = pos->second->find(pszKey);

			if (pos->second->end() != pos_)
			{
				pos->second->erase(pszKey);

				if (0 == pos->second->size())
					m_RegisterMap.erase(pszCategory);
			}
		}

		CTransactionManager::Instance()->Unregister(pszCategory, pszKey);
	}

	ret_ Ret = CRegister::Instance()->Unregister(pszCategory, pszKey);

	if (SUCCESS != _ERR(Ret))
		_RET_BY(Ret);

	_RET(SUCCESS);
}

