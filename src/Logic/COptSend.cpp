#include "COptSend.h"

#include "../Transactions/CProcessor.h"
#include "../Data/CVarNetwork.h"

COptSend::COptSend(const CPduInfo *pPDUInfo,
				   const CAutoVar *pDestination)
	: COperator(OT_SEND)
{
	m_pDestination = null_v;
	m_pIP = null_v;
	m_pPort = null_v;

	m_SendType = TCP_SEND;
    m_pPDUInfo = (CPduInfo *) pPDUInfo;

	if (m_pDestination)
		m_pDestination = pDestination->Clone();

	CField *pFieldInfo = null_v;
	TEvaluate *pEvaluate = null_v;

	m_pPDUInfo->GetStruct(pFieldInfo);

	while (pFieldInfo)
	{
        if (null_v == pFieldInfo->getGroupField())
		{
			pEvaluate = new TEvaluate;

			pEvaluate->pFieldInfo = pFieldInfo;
			pEvaluate->pField = null_v;
			pEvaluate->pValue = null_v;

			m_EvaluateVector.push_back(pEvaluate);
		}

        pFieldInfo = (CField *) pFieldInfo->getNextField();
	}
}

COptSend::COptSend(b_4 nSign/*No meaning*/,
        const CPduInfo *pPDUInfo,
				   const CAutoVar *pIP,
				   const CAutoVar *pPort)
	: COperator(OT_SEND)
{
	m_pDestination = null_v;
	m_pIP = null_v;
	m_pPort = null_v;

	m_SendType = UDP_SEND;
    m_pPDUInfo = (CPduInfo *) pPDUInfo;

	if (m_pIP)
		m_pIP = pIP->Clone();

	if (m_pPort)
		m_pPort	= pPort->Clone();

	CField *pFieldInfo = null_v;
	TEvaluate *pEvaluate = new TEvaluate;

	m_pPDUInfo->GetStruct(pFieldInfo);

	while (pFieldInfo)
	{
        if (null_v == pFieldInfo->getGroupField())
		{
			pEvaluate->pFieldInfo = pFieldInfo;
			pEvaluate->pField = null_v;
			pEvaluate->pValue = null_v;

			m_EvaluateVector.push_back(pEvaluate);
		}

        pFieldInfo = (CField *) pFieldInfo->getNextField();
	}
}

COptSend::COptSend(const COptSend &opt): COperator(opt)
{
	m_pDestination = null_v;
	m_pIP = null_v;
	m_pPort = null_v;

	m_pPDUInfo = opt.m_pPDUInfo;
	m_SendType = opt.m_SendType;

	if (TCP_SEND == m_SendType && opt.m_pDestination)
	{
		m_pDestination = opt.m_pDestination->Clone();
	}
	else if (UDP_SEND == m_SendType && opt.m_pIP && opt.m_pPort)
	{
		m_pIP	= opt.m_pIP->Clone();
		m_pPort	= opt.m_pPort->Clone();
	}

	for (vector_evaluate::const_iterator pos = opt.m_EvaluateVector.begin();
		pos != opt.m_EvaluateVector.end(); pos++)
	{
		TEvaluate *pEvaluate = new TEvaluate;

		memset(pEvaluate, 0, sizeof(TEvaluate));
		pEvaluate->pFieldInfo = (*pos)->pFieldInfo;

		if ((*pos)->pField)
			pEvaluate->pField = (*pos)->pField->Clone();

		if ((*pos)->pValue)
			pEvaluate->pValue = (*pos)->pValue->Clone();

		m_EvaluateVector.push_back(pEvaluate);
	}
}

const COptSend &COptSend::operator =(const COptSend &opt)
{
	if (this != &opt)
	{
		COperator::operator =(opt);

		Clear();

		m_pPDUInfo	= opt.m_pPDUInfo;
		m_SendType	= opt.m_SendType;

		if (TCP_SEND == m_SendType && opt.m_pDestination)
		{
			m_pDestination = opt.m_pDestination->Clone();
		}
		else if (UDP_SEND == m_SendType && opt.m_pIP && opt.m_pPort)
		{
			m_pIP	= opt.m_pIP->Clone();
			m_pPort	= opt.m_pPort->Clone();
		}

		for (vector_evaluate::const_iterator pos = opt.m_EvaluateVector.begin();
			pos != opt.m_EvaluateVector.end(); pos++)
		{
			TEvaluate *pEvaluate = new TEvaluate;

			memset(pEvaluate, 0, sizeof(TEvaluate));
			pEvaluate->pFieldInfo = (*pos)->pFieldInfo;

			if ((*pos)->pField)
				pEvaluate->pField = (*pos)->pField->Clone();

			if ((*pos)->pValue)
				pEvaluate->pValue = (*pos)->pValue->Clone();

			m_EvaluateVector.push_back(pEvaluate);
		}
	}

	return *this;
}

COptSend::~COptSend()
{
	Clear();
}

void COptSend::Clear()
{
	m_pPDUInfo	= null_v;
	m_SendType	= NONE_SEND;

	_DEL(m_pDestination);
	_DEL(m_pIP);
	_DEL(m_pPort);

	for (vector_evaluate::iterator pos = m_EvaluateVector.begin();
		 pos != m_EvaluateVector.end(); pos++)
	{
		_DEL((*pos)->pField);
		_DEL((*pos)->pValue);
		_DEL(*pos);
	}

	m_EvaluateVector.clear();
}

void COptSend::Initialize(const opt_unit *pUnit)
{
	COperator::Initialize(pUnit);

	for (vector_evaluate::iterator pos = m_EvaluateVector.begin();
        pos != m_EvaluateVector.end(); pos++)
    {
		if ((*pos)->pField)
			(*pos)->pField->Initialize(pUnit->pData);

		if ((*pos)->pValue)
			(*pos)->pValue->Initialize(pUnit->pData);
    }

	if (TCP_SEND == m_SendType && m_pDestination)
	{
		m_pDestination->Initialize(pUnit->pData);
	}
	else if (UDP_SEND == m_SendType && m_pIP && m_pPort)
	{
		m_pIP->Initialize(pUnit->pData);
		m_pPort->Initialize(pUnit->pData);
	}

	
}

bool_ COptSend::AddEvaluate(const ch_1 *pszFieldName,
							const CAutoVar *pValue)
{
#ifdef _DEBUG_
	if (!m_pPDUInfo)
		return false_v;

	if (!pszFieldName || 0 == pszFieldName[0])
		return false_v;

	if (!pValue)
		return false_v;
#endif

	CField *pFieldInfo = null_v;

	if (SUCCESS != _ERR(m_pPDUInfo->GetField(pszFieldName, pFieldInfo)))
		return false_v;

	vector_evaluate::iterator pos;

	for (pos = m_EvaluateVector.begin();
		 pos != m_EvaluateVector.end(); pos++)
	{
		if ((*pos)->pFieldInfo == pFieldInfo)
		{
			if ((*pos)->pField || (*pos)->pValue)
				return false_v;

			break;
		}
	}

	if (m_EvaluateVector.end() == pos)
		return false_v;

	(*pos)->pField = (CAutoVar *)new CVarNetwork(pFieldInfo);
	(*pos)->pValue = pValue->Clone();

	return true_v;
}

void COptSend::Work(const TMessageUnit *pTMU)
{
	size_ nSize = 0;

	for (vector_evaluate::const_iterator pos = m_EvaluateVector.begin();
		 pos != m_EvaluateVector.end(); pos++)
	{
        if (FIELD_GROUP_TYPE == (*pos)->pFieldInfo->type())
		{
			// If it's Group, check if it's available.
			if ((*pos)->pField && (*pos)->pValue)
			{
				obj_ Temp = null_v;
				bool_ bIsCountSize = false_v;

				 // If ture, Defined Group
				if ((*pos)->pValue->Value(Temp))
					bIsCountSize = true_v;
				// If ture, Network Group
                else if ((*pos)->pFieldInfo->size(pTMU->message, pTMU->size))
					bIsCountSize = true_v;

				if (bIsCountSize)
				{
					try
					{
						nSize += (*pos)->pValue->Value(pTMU)->size();
					}
					catch (...)
					{
						throw;
					}
				}
			}
		}
        else // if (null_v == (*pos)->pFieldInfo->getGroupField())
		{
            nSize += (*pos)->pFieldInfo->getUnitSize();
		}
	}	

	TMessageUnit MU;

	MU.size	= nSize;
	MU.message = new ub_1[MU.size];
	MU.pduInfo	= m_pPDUInfo;
	memset(MU.message, 0, MU.size);

	TMsgInfo *pMsgInfo = ((TMessageUnit *)pTMU)->msgInfo;
	TMsgInfo MsgInfo;
	const CProcessor *pProcessor = GetContainer();

	try
	{
		if (!pProcessor)
			throw OPERATOR_OPERAITON_ERROR;

		for (vector_evaluate::const_iterator pos = m_EvaluateVector.begin();
			 pos != m_EvaluateVector.end(); pos++)
		{
			if ((*pos)->pField && (*pos)->pValue)
			{
                if (FIELD_GROUP_TYPE == (*pos)->pFieldInfo->type())
					if (0 == (*pos)->pValue->Value(pTMU)->size())
						continue;

				v_ *pField = (*pos)->pField->Value(&MU);
				v_ *pValue = (*pos)->pValue->Value(pTMU);

				(*pField) = (*pValue);
			}
		}

		if (TCP_SEND == m_SendType && m_pDestination)
		{
			v_ *pValue = m_pDestination->Value(pTMU);

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

		if (SUCCESS != _ERR(((CProcessor *)pProcessor)->Send(m_pPDUInfo,
															 MU.message,
															 MU.size,
															 pMsgInfo)))
        {
			throw OPERATOR_OPERAITON_ERROR;
        }
	}
	catch (...)
	{
		_DEL_ARR(MU.message);

		throw;
	}

	_DEL_ARR(MU.message);
}
