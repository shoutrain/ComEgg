#include "COptUseModule.h"
#include "../Data/CVarModule.h"
#include "../System/CModuleCall.h"
#include "../Modules/CModuleInfo.h"

COptUseModule::COptUseModule(const CInterfaceInfo *pInterfaceInfo)
	: COperator(OT_USE_MODULE)
{
	m_pInterfaceInfo = (CInterfaceInfo *)pInterfaceInfo;

	CField *pFieldInfo = null_v;
	TEvaluate *pEvaluate = null_v;

	m_pInterfaceInfo->GetInStruct(pFieldInfo);

	while (pFieldInfo)
	{
		if (null_v == pFieldInfo->GetGroupField())
		{
			pEvaluate = new TEvaluate;

			pEvaluate->pFieldInfo = pFieldInfo;
			pEvaluate->pField = null_v;
			pEvaluate->pValue = null_v;

			m_InEvaluateVector.push_back(pEvaluate);
		}

		pFieldInfo = (CField *)pFieldInfo->GetNextField();
	}

	m_pInterfaceInfo->GetOutStruct(pFieldInfo);

	while (pFieldInfo)
	{
		if (null_v == pFieldInfo->GetGroupField())
		{
			pEvaluate = new TEvaluate;

			pEvaluate->pFieldInfo = pFieldInfo;
			pEvaluate->pField = null_v;
			pEvaluate->pValue = null_v;
			
			m_OutEvaluateVector.push_back(pEvaluate);
		}

		pFieldInfo = (CField *)pFieldInfo->GetNextField();
	}
}

COptUseModule::COptUseModule(const COptUseModule &opt): COperator(opt)
{
	m_pInterfaceInfo = opt.m_pInterfaceInfo;

	for (vector_evaluate::const_iterator pos = opt.m_InEvaluateVector.begin();
		pos != opt.m_InEvaluateVector.end(); pos++)
	{
		TEvaluate *pEvaluate = new TEvaluate;

		memset(pEvaluate, 0, sizeof(TEvaluate));
		pEvaluate->pFieldInfo = (*pos)->pFieldInfo;

		if ((*pos)->pField)
			pEvaluate->pField = (*pos)->pField->Clone();

		if ((*pos)->pValue)
			pEvaluate->pValue = (*pos)->pValue->Clone();

		m_InEvaluateVector.push_back(pEvaluate);
	}

	for (vector_evaluate::const_iterator pos_ = opt.m_OutEvaluateVector.begin();
		pos_ != opt.m_OutEvaluateVector.end(); pos_++)
	{
		TEvaluate *pEvaluate = new TEvaluate;

		memset(pEvaluate, 0, sizeof(TEvaluate));
		pEvaluate->pFieldInfo = (*pos_)->pFieldInfo;

		if ((*pos_)->pField)
			pEvaluate->pField = (*pos_)->pField->Clone();

		if ((*pos_)->pValue)
			pEvaluate->pValue = (*pos_)->pValue->Clone();

		m_OutEvaluateVector.push_back(pEvaluate);
	}
}

const COptUseModule &COptUseModule::operator =(const COptUseModule &opt)
{
	if (this != &opt)
	{
		COperator::operator =(opt);

		Clear();

		m_pInterfaceInfo = opt.m_pInterfaceInfo;

		for (vector_evaluate::const_iterator pos 
				 = opt.m_InEvaluateVector.begin();
			 pos != opt.m_InEvaluateVector.end(); pos++)
		{
			TEvaluate *pEvaluate = new TEvaluate;

			memset(pEvaluate, 0, sizeof(TEvaluate));
			pEvaluate->pFieldInfo = (*pos)->pFieldInfo;

			if ((*pos)->pField)
				pEvaluate->pField = (*pos)->pField->Clone();

			if ((*pos)->pValue)
				pEvaluate->pValue = (*pos)->pValue->Clone();

			m_InEvaluateVector.push_back(pEvaluate);
		}

		for (vector_evaluate::const_iterator pos_ 
				 = opt.m_OutEvaluateVector.begin();
			 pos_ != opt.m_OutEvaluateVector.end(); pos_++)
		{
			TEvaluate *pEvaluate = new TEvaluate;

			memset(pEvaluate, 0, sizeof(TEvaluate));
			pEvaluate->pFieldInfo = (*pos_)->pFieldInfo;

			if ((*pos_)->pField)
				pEvaluate->pField = (*pos_)->pField->Clone();

			if ((*pos_)->pValue)
				pEvaluate->pValue = (*pos_)->pValue->Clone();

			m_OutEvaluateVector.push_back(pEvaluate);
		}
	}

	return *this;
}

COptUseModule::~COptUseModule()
{
	Clear();
}

void COptUseModule::Clear()
{
	m_pInterfaceInfo = null_v;

	for (vector_evaluate::iterator pos = m_InEvaluateVector.begin();
		 pos != m_InEvaluateVector.end(); pos++)
	{
		_DEL((*pos)->pField);
		_DEL((*pos)->pValue);
		_DEL(*pos);
	}

	for (vector_evaluate::iterator pos = m_OutEvaluateVector.begin();
		 pos != m_OutEvaluateVector.end(); pos++)
	{
		_DEL((*pos)->pField);
		_DEL((*pos)->pValue);
		_DEL(*pos);
	}

	m_InEvaluateVector.clear();
	m_OutEvaluateVector.clear();
}

void COptUseModule::Initialize(const opt_unit *pUnit)
{
	COperator::Initialize(pUnit);

	for (vector_evaluate::iterator pos = m_InEvaluateVector.begin();
        pos != m_InEvaluateVector.end(); pos++)
    {
		if ((*pos)->pField)
			(*pos)->pField->Initialize(pUnit->pData);

		if ((*pos)->pValue)
			(*pos)->pValue->Initialize(pUnit->pData);
    }

	for (vector_evaluate::iterator pos_ = m_OutEvaluateVector.begin();
        pos_ != m_OutEvaluateVector.end(); pos_++)
    {
		if ((*pos_)->pField)
			(*pos_)->pField->Initialize(pUnit->pData);

		if ((*pos_)->pValue)
			(*pos_)->pValue->Initialize(pUnit->pData);
    }
}

bool_ COptUseModule::AddInParameter(CAutoVar *pValue)
{
#ifdef _DEBUG_
	if (!m_pInterfaceInfo)
		return false_v;

	if (!pValue)
		return false_v;
#endif

	vector_evaluate::iterator pos;

	for (pos = m_InEvaluateVector.begin();
		 pos != m_InEvaluateVector.end(); pos++)
	{
		if (!(*pos)->pField || !(*pos)->pValue)
		{
			(*pos)->pField = (CAutoVar *)new CVarModule((*pos)->pFieldInfo);
			(*pos)->pValue = pValue->Clone();

			break;
		}
	}

	if (m_InEvaluateVector.end() == pos)
		return false_v;

	return true_v;
}

bool_ COptUseModule::AddOutParameter(const ch_1 *pszFieldName, 
									  CAutoVar *pValue)
{
#ifdef _DEBUG_
	if (!m_pInterfaceInfo)
		return false_v;

	if (!pszFieldName || 0 == pszFieldName[0])
		return false_v;

	if (!pValue)
		return false_v;
#endif

	CField *pFieldInfo = null_v;

	if (SUCCESS != _ERR(m_pInterfaceInfo->GetOutField(pszFieldName, pFieldInfo)))
		return false_v;

	vector_evaluate::iterator pos;

	for (pos = m_OutEvaluateVector.begin();
		 pos != m_OutEvaluateVector.end(); pos++)
	{
		if ((*pos)->pFieldInfo == pFieldInfo)
		{
			if ((*pos)->pField || (*pos)->pValue)
				return false_v;

			break;
		}
	}

	if (m_OutEvaluateVector.end() == pos)
		return false_v;

	(*pos)->pField = (CAutoVar *)new CVarModule(pFieldInfo);
	(*pos)->pValue = pValue->Clone();

	return true_v;
}

void COptUseModule::Work(const TMessageUnit *pTMU)
{
	size_ nSize = 0;

	for (vector_evaluate::const_iterator pos = m_InEvaluateVector.begin();
		 pos != m_InEvaluateVector.end(); pos++)
	{
		if (FIELD_GROUP_TYPE == (*pos)->pFieldInfo->Type())
		{
			// If it's Group, check if it's available.
			if ((*pos)->pField && (*pos)->pValue)
			{
				obj_ Temp;
				bool_ bIsCountSize = false_v;

				 // If ture, Defined Group
				if ((*pos)->pValue->Value(Temp))
					bIsCountSize = true_v;
				// If ture, Network Group
				else if ((*pos)->pFieldInfo->Size(pTMU->message, pTMU->size))
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

	TMessageUnit InMU;

	memset(&InMU, 0, sizeof(TMessageUnit));
	InMU.size = nSize;

	if (InMU.size)
	{
		InMU.message = new ub_1[InMU.size];
		memset(InMU.message, 0, InMU.size);		
	}

	TMessageUnit OutMU;

	memset(&OutMU, 0, sizeof(TMessageUnit));

	try
	{
		for (vector_evaluate::const_iterator pos = m_InEvaluateVector.begin();
			 pos != m_InEvaluateVector.end(); pos++)
		{
			v_ *pField = (*pos)->pField->Value(&InMU);
			v_ *pValue = (*pos)->pValue->Value(pTMU);

			(*pField) = (*pValue);
		}

		CModuleCall mc;

		if (!mc.Call(m_pInterfaceInfo->GetModuleInfo()->GetPath(),
					 m_pInterfaceInfo->GetModuleInfo()->GetName(),
					 m_pInterfaceInfo->GetModuleInfo()->GetExt(),
					 m_pInterfaceInfo->Name(),
					 InMU.message,
					 InMU.size,
					 OutMU.message,
					 OutMU.size))
		{
			throw OPERATOR_OPERAITON_ERROR;
		}

		// Get variable size first, so that can create enough memory to keep it.
		for (vector_evaluate::const_iterator pos = m_OutEvaluateVector.begin();
			 pos != m_OutEvaluateVector.end(); pos++)
		{
			if ((*pos)->pField && (*pos)->pValue)
			{
				if (FIELD_GROUP_TYPE == (*pos)->pFieldInfo->Type() &&
					// It must be CFieldGroup(Module), check if it's available.
					(*pos)->pFieldInfo->Size(OutMU.message, OutMU.size))
				{
					try
					{
						v_ *pField = (*pos)->pField->Value(&OutMU);
						CField *pValueField = null_v;
						v_ *pValueData =
							(*pos)->pValue->Value((obj_ &)pValueField);
						TFieldGroup *pValueGroup =
							(TFieldGroup *)(obj_)*pValueData;

						if (pValueGroup->nSize && pValueGroup->pData)
						{
							_DEL_ARR(pValueGroup->pData);
							pValueGroup->nSize = 0;
						}

						pValueGroup->nSize = pField->size();

						if (pValueGroup->nSize) // should be true
						{
							pValueGroup->pData = new ub_1[pValueGroup->nSize];
							memset(pValueGroup->pData, 0, pValueGroup->nSize);
						}
						else
						{
							throw OPERATOR_OPERAITON_ERROR;
						}
					}
					catch (...)
					{
						throw;
					}
				}
			}
			else
			{
				throw OPERATOR_OPERAITON_ERROR;
			}
		}

		for (vector_evaluate::const_iterator pos = m_OutEvaluateVector.begin();
			 pos != m_OutEvaluateVector.end(); pos++)
		{
			if (FIELD_GROUP_TYPE == (*pos)->pFieldInfo->Type())
			{
				CField *pValueField = null_v;
				v_ *pValueData = (*pos)->pValue->Value((obj_ &)pValueField);
				TFieldGroup *pValueGroup = (TFieldGroup *)(obj_)*pValueData;

				if (!pValueGroup->nSize)
					continue;
			}

			v_ *pField = (*pos)->pField->Value(&OutMU);
			v_ *pValue = (*pos)->pValue->Value(pTMU);

			(*pValue) = (*pField);
		}
	}
	catch (...)
	{
		_DEL_ARR(InMU.message);
		_DEL_ARR(OutMU.message);
		
		throw;
	}

	_DEL_ARR(InMU.message);
	_DEL_ARR(OutMU.message);
}
