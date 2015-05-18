#include "COptSend.h"

#include "../Data/CVarNetwork.h"
#include "../Network/CNetwork.h"
#include "../Network/CNetworkHandle.h"
#include "../Network/CNetworkManager.h"

COptSend::COptSend(const CPDUInfo *pPDUInfo)
	: COperator(OT_SEND)
{
	m_pPDUInfo = (CPDUInfo *)pPDUInfo;

	CField *pFieldInfo = null_v;
	TEvaluate *pEvaluate = null_v;

	m_pPDUInfo->GetStruct(pFieldInfo);

	while (pFieldInfo)
	{
		if (null_v == pFieldInfo->GetGroupField())
		{
			pEvaluate = new TEvaluate;

			pEvaluate->pFieldInfo = pFieldInfo;
			pEvaluate->pField = null_v;
			pEvaluate->pValue = null_v;

			m_EvaluateVector.push_back(pEvaluate);
		}

		pFieldInfo = (CField *)pFieldInfo->GetNextField();
	}
}

COptSend::COptSend(const COptSend &opt): COperator(opt)
{
	m_pPDUInfo = opt.m_pPDUInfo;

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
}

bool_ COptSend::AddEvaluate(const ch_1 *pszFieldName,
							const CVariable *pValue)
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

	if (SUCCESS != m_pPDUInfo->GetField(pszFieldName, pFieldInfo))
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

	(*pos)->pField = (CVariable *)new CVarNetwork(pFieldInfo);
	(*pos)->pValue = pValue->Clone();

	return true_v;
}

void COptSend::Work(const TMU *pTMU)
{
	size_ nSize = 0;

	for (vector_evaluate::const_iterator pos = m_EvaluateVector.begin();
		 pos != m_EvaluateVector.end(); pos++)
	{
		if (FIELD_GROUP_TYPE == (*pos)->pFieldInfo->Type())
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
				else if ((*pos)->pFieldInfo->Size(pTMU->pMessage, pTMU->nSize))
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
		else // if (null_v == (*pos)->pFieldInfo->GetGroupField())
		{
			nSize += (*pos)->pFieldInfo->GetUnitSize();
		}
	}	

	TMU MU;
	
	MU.nSize	= nSize;
	MU.pMessage = new ub_1[MU.nSize];
	MU.pPDUInfo	= m_pPDUInfo;
	memset(MU.pMessage, 0, MU.nSize);

	try
	{
		for (vector_evaluate::const_iterator pos = m_EvaluateVector.begin();
			 pos != m_EvaluateVector.end(); pos++)
		{
			if ((*pos)->pField && (*pos)->pValue)
			{
				if (FIELD_GROUP_TYPE == (*pos)->pFieldInfo->Type())
					if (0 == (*pos)->pValue->Value(pTMU)->size())
						continue;

				v_ *pField = (*pos)->pField->Value(&MU);
				v_ *pValue = (*pos)->pValue->Value(pTMU);

				(*pField) = (*pValue);
			}
		}

		CNetwork *pNetwork =
				(CNetwork *)CNetworkManager::Instance()->GetNetwork();

		if (!pNetwork)
			throw OPERATOR_OPERAITON_ERROR;

		CNetworkHandle *pHandle = (CNetworkHandle *)pNetwork->GetHandle();

		if (!pHandle)
			throw OPERATOR_OPERAITON_ERROR;

		if (SUCCESS != pHandle->CheckSend(m_pPDUInfo, MU.pMessage, MU.nSize))
			throw OPERATOR_OPERAITON_ERROR;

		if (SUCCESS != pHandle->Send(MU.pMessage, MU.nSize))
			throw OPERATOR_OPERAITON_ERROR;
	}
	catch (...)
	{
		_DEL_ARR(MU.pMessage);

		throw;
	}

	_DEL_ARR(MU.pMessage);
}
