#include "CVarGroupDefined.h"

CAutoVar *CVarGroupDefined::Clone() const
{
	return (CAutoVar *)new CVarGroupDefined(m_szGroupName,
										     m_szSubName,
										     m_szIndexName);
}

void CVarGroupDefined::Initialize(const CData *pData)
{
	m_pGroupData = null_v;
	m_pField = (CField *)(obj_)*pData->Value(m_szGroupName,
											 m_szSubName,
											 m_pGroupData);
	m_pIndex = pData->Value(m_szIndexName);

	const CField *pParentField = m_pField->GetGroupField();

	if (pParentField)
		m_pSize = pData->Value(pParentField->GetSizeName());
	else
		m_pSize = pData->Value(m_pField->GetSizeName());
}

v_ *CVarGroupDefined::Value(const TMessageUnit *pTMU)
{
	m_Value.clear();
	
	if (!m_pGroupData || !m_pGroupData->nSize || !m_pGroupData->pData)
	{
		v_ tmp;
		
		m_Value = tmp;

		return &m_Value;
	}

	try
	{
		size_ nIndex = 0;
		size_ nOffset = 0;

		if (m_pIndex)
			nIndex = (size_)*m_pIndex;

		if (FIELD_GROUP_STYLE == (GET_FIELD_STYLE & m_pField->Type()))
		{
			nOffset = m_pField->Offset((size_)*m_pSize,
									   m_pGroupData->nSize,
									   nIndex);
		}
		else
		{
			nOffset = m_pField->Offset(m_pGroupData->pData,
									   m_pGroupData->nSize,
									   nIndex);
		}

		switch (m_pField->Type())
		{
		case FIELD_B_1_TYPE:
			m_Value = (b_1 *)(m_pGroupData->pData + nOffset);
			break;
		case FIELD_UB_1_TYPE:
			m_Value = (ub_1 *)(m_pGroupData->pData + nOffset);
			break;
		case FIELD_B_2_TYPE:
			m_Value = (b_2 *)(m_pGroupData->pData + nOffset);
			break;
		case FIELD_UB_2_TYPE:
			m_Value = (ub_2 *)(m_pGroupData->pData + nOffset);
			break;
		case FIELD_B_4_TYPE:
			m_Value = (b_4 *)(m_pGroupData->pData + nOffset);
			break;
		case FIELD_UB_4_TYPE:
			m_Value = (ub_4 *)(m_pGroupData->pData + nOffset);
			break;
		case FIELD_B_8_TYPE:
			m_Value = (b_8 *)(m_pGroupData->pData + nOffset);
			break;
		case FIELD_UB_8_TYPE:
			m_Value = (ub_8 *)(m_pGroupData->pData + nOffset);
			break;
		case FIELD_FB_4_TYPE:
			m_Value = (fb_4 *)(m_pGroupData->pData + nOffset);
			break;
		case FIELD_FB_8_TYPE:
			m_Value = (fb_8 *)(m_pGroupData->pData + nOffset);
			break;
		case FIELD_STR_TYPE:
		{
			v_ tmp((const ch_1 *)(m_pGroupData->pData + nOffset), 
					m_pField->Size());

			m_Value = tmp;
		}
		break;
		case FIELD_GROUP_TYPE:
		{
			if (nIndex)
			{
				v_ tmp((obj_ *)&(m_pGroupData->pData), 
					   nOffset,
					   m_pField->GetUnitSize());

				m_Value = tmp;
			}
			else
			{
				v_ tmp((obj_ *)&(m_pGroupData->pData), 0, m_pGroupData->nSize);

				m_Value = tmp;
			}
		}
		break;
		default:
			throw FIELD_TYPE_ERROR;
		}
	}
	catch (...)
	{
		throw;
	}

	return &m_Value;
}

v_ *CVarGroupDefined::Value(obj_ &Parameter)
{
	if (Parameter || !m_pGroupData || !m_pField)
		throw FIELD_DATA_NULL;

	Parameter = (obj_)m_pField;

	v_ tmp((obj_)m_pGroupData);

	m_Value.clear();
	m_Value = tmp;

	return &m_Value;
}
