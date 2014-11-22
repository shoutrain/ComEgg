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
        if (null_v == pFieldInfo->getGroupField())
		{
			pEvaluate = new TEvaluate;

            pEvaluate->fieldInfo = pFieldInfo;
            pEvaluate->field = null_v;
            pEvaluate->value = null_v;

			m_InEvaluateVector.push_back(pEvaluate);
		}

        pFieldInfo = (CField *) pFieldInfo->getNextField();
	}

	m_pInterfaceInfo->GetOutStruct(pFieldInfo);

	while (pFieldInfo)
	{
        if (null_v == pFieldInfo->getGroupField())
		{
			pEvaluate = new TEvaluate;

            pEvaluate->fieldInfo = pFieldInfo;
            pEvaluate->field = null_v;
            pEvaluate->value = null_v;
			
			m_OutEvaluateVector.push_back(pEvaluate);
		}

        pFieldInfo = (CField *) pFieldInfo->getNextField();
	}
}

COptUseModule::COptUseModule(const COptUseModule &opt): COperator(opt)
{
	m_pInterfaceInfo = opt.m_pInterfaceInfo;

    for (vectorEvaluate::const_iterator pos = opt.m_InEvaluateVector.begin();
		pos != opt.m_InEvaluateVector.end(); pos++)
	{
		TEvaluate *pEvaluate = new TEvaluate;

		memset(pEvaluate, 0, sizeof(TEvaluate));
        pEvaluate->fieldInfo = (*pos)->fieldInfo;

        if ((*pos)->field)
            pEvaluate->field = (*pos)->field->Clone();

        if ((*pos)->value)
            pEvaluate->value = (*pos)->value->Clone();

		m_InEvaluateVector.push_back(pEvaluate);
	}

    for (vectorEvaluate::const_iterator pos_ = opt.m_OutEvaluateVector.begin();
		pos_ != opt.m_OutEvaluateVector.end(); pos_++)
	{
		TEvaluate *pEvaluate = new TEvaluate;

		memset(pEvaluate, 0, sizeof(TEvaluate));
        pEvaluate->fieldInfo = (*pos_)->fieldInfo;

        if ((*pos_)->field)
            pEvaluate->field = (*pos_)->field->Clone();

        if ((*pos_)->value)
            pEvaluate->value = (*pos_)->value->Clone();

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

        for (vectorEvaluate::const_iterator pos
				 = opt.m_InEvaluateVector.begin();
			 pos != opt.m_InEvaluateVector.end(); pos++)
		{
			TEvaluate *pEvaluate = new TEvaluate;

			memset(pEvaluate, 0, sizeof(TEvaluate));
            pEvaluate->fieldInfo = (*pos)->fieldInfo;

            if ((*pos)->field)
                pEvaluate->field = (*pos)->field->Clone();

            if ((*pos)->value)
                pEvaluate->value = (*pos)->value->Clone();

			m_InEvaluateVector.push_back(pEvaluate);
		}

        for (vectorEvaluate::const_iterator pos_
				 = opt.m_OutEvaluateVector.begin();
			 pos_ != opt.m_OutEvaluateVector.end(); pos_++)
		{
			TEvaluate *pEvaluate = new TEvaluate;

			memset(pEvaluate, 0, sizeof(TEvaluate));
            pEvaluate->fieldInfo = (*pos_)->fieldInfo;

            if ((*pos_)->field)
                pEvaluate->field = (*pos_)->field->Clone();

            if ((*pos_)->value)
                pEvaluate->value = (*pos_)->value->Clone();

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

    for (vectorEvaluate::iterator pos = m_InEvaluateVector.begin();
		 pos != m_InEvaluateVector.end(); pos++)
	{
        _DEL((*pos)->field);
        _DEL((*pos)->value);
		_DEL(*pos);
	}

    for (vectorEvaluate::iterator pos = m_OutEvaluateVector.begin();
		 pos != m_OutEvaluateVector.end(); pos++)
	{
        _DEL((*pos)->field);
        _DEL((*pos)->value);
		_DEL(*pos);
	}

	m_InEvaluateVector.clear();
	m_OutEvaluateVector.clear();
}

void COptUseModule::init(const optUnit *unit)
{
    COperator::init(unit);

    for (vectorEvaluate::iterator pos = m_InEvaluateVector.begin();
        pos != m_InEvaluateVector.end(); pos++)
    {
        if ((*pos)->field)
            (*pos)->field->Initialize(unit->data);

        if ((*pos)->value)
            (*pos)->value->Initialize(unit->data);
    }

    for (vectorEvaluate::iterator pos_ = m_OutEvaluateVector.begin();
        pos_ != m_OutEvaluateVector.end(); pos_++)
    {
        if ((*pos_)->field)
            (*pos_)->field->Initialize(unit->data);

        if ((*pos_)->value)
            (*pos_)->value->Initialize(unit->data);
    }
}

bool_ COptUseModule::AddInParameter(CAutoVar *pValue)
{
#ifdef _DEBUG_
	if (!m_pInterfaceInfo)
		return false_v;

	if (!value)
		return false_v;
#endif

    vectorEvaluate::iterator pos;

	for (pos = m_InEvaluateVector.begin();
		 pos != m_InEvaluateVector.end(); pos++)
	{
        if (!(*pos)->field || !(*pos)->value)
		{
            (*pos)->field = (CAutoVar *) new CVarModule((*pos)->fieldInfo);
            (*pos)->value = pValue->Clone();

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

	if (!value)
		return false_v;
#endif

	CField *pFieldInfo = null_v;

	if (SUCCESS != _ERR(m_pInterfaceInfo->GetOutField(pszFieldName, pFieldInfo)))
		return false_v;

    vectorEvaluate::iterator pos;

	for (pos = m_OutEvaluateVector.begin();
		 pos != m_OutEvaluateVector.end(); pos++)
	{
        if ((*pos)->fieldInfo == pFieldInfo)
		{
            if ((*pos)->field || (*pos)->value)
				return false_v;

			break;
		}
	}

	if (m_OutEvaluateVector.end() == pos)
		return false_v;

    (*pos)->field = (CAutoVar *) new CVarModule(pFieldInfo);
    (*pos)->value = pValue->Clone();

	return true_v;
}

void COptUseModule::work(const TMessageUnit *tmu)
{
	size_ nSize = 0;

    for (vectorEvaluate::const_iterator pos = m_InEvaluateVector.begin();
		 pos != m_InEvaluateVector.end(); pos++)
	{
        if (FIELD_GROUP_TYPE == (*pos)->fieldInfo->type())
		{
			// If it's Group, check if it's available.
            if ((*pos)->field && (*pos)->value)
			{
				obj_ Temp;
				bool_ bIsCountSize = false_v;

				 // If ture, Defined Group
                if ((*pos)->value->Value(Temp))
					bIsCountSize = true_v;
				// If ture, Network Group
                else if ((*pos)->fieldInfo->size(tmu->message, tmu->size))
					bIsCountSize = true_v;

				if (bIsCountSize)
				{
					try
					{
                        nSize += (*pos)->value->Value(tmu)->size();
					}
					catch (...)
					{
						throw;
					}
				}
			}
		}
        else // if (null_v == (*pos)->fieldInfo->getGroupField())
		{
            nSize += (*pos)->fieldInfo->getUnitSize();
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
        for (vectorEvaluate::const_iterator pos = m_InEvaluateVector.begin();
			 pos != m_InEvaluateVector.end(); pos++)
		{
            v_ *pField = (*pos)->field->Value(&InMU);
            v_ *pValue = (*pos)->value->Value(tmu);

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
        for (vectorEvaluate::const_iterator pos = m_OutEvaluateVector.begin();
			 pos != m_OutEvaluateVector.end(); pos++)
		{
            if ((*pos)->field && (*pos)->value)
			{
                if (FIELD_GROUP_TYPE == (*pos)->fieldInfo->type() &&
					// It must be CFieldGroup(Module), check if it's available.
                            (*pos)->fieldInfo->size(OutMU.message, OutMU.size))
				{
					try
					{
                        v_ *pField = (*pos)->field->Value(&OutMU);
						CField *pValueField = null_v;
						v_ *pValueData =
                                (*pos)->value->Value((obj_ &) pValueField);
						TFieldGroup *pValueGroup =
							(TFieldGroup *)(obj_)*pValueData;

                        if (pValueGroup->size && pValueGroup->data)
						{
                            _DEL_ARR(pValueGroup->data);
                            pValueGroup->size = 0;
						}

                        pValueGroup->size = pField->size();

                        if (pValueGroup->size) // should be true
						{
                            pValueGroup->data = new ub_1[pValueGroup->size];
                            memset(pValueGroup->data, 0, pValueGroup->size);
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

        for (vectorEvaluate::const_iterator pos = m_OutEvaluateVector.begin();
			 pos != m_OutEvaluateVector.end(); pos++)
		{
            if (FIELD_GROUP_TYPE == (*pos)->fieldInfo->type())
			{
				CField *pValueField = null_v;
                v_ *pValueData = (*pos)->value->Value((obj_ &) pValueField);
				TFieldGroup *pValueGroup = (TFieldGroup *)(obj_)*pValueData;

                if (!pValueGroup->size)
					continue;
			}

            v_ *pField = (*pos)->field->Value(&OutMU);
            v_ *pValue = (*pos)->value->Value(tmu);

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
