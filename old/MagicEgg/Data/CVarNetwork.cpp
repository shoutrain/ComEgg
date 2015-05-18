#include "CVarNetwork.h"

CVariable *CVarNetwork::Clone() const
{
	return (CVariable *)new CVarNetwork(m_pField, m_szIndexName);
}

void CVarNetwork::Initialize(const CData *pData)
{
	m_pIndex = pData->Value(m_szIndexName);
}

v_ *CVarNetwork::Value(const TMU *pTMU)
{
	try
	{
		size_ nIndex = 0;

		if (m_pIndex)
			nIndex = (size_)*m_pIndex;

		size_ nOffset = m_pField->Offset(pTMU->pMessage,
										 pTMU->nSize,
										 nIndex);

		m_Value.clear();

		switch (m_pField->Type())
		{
		case FIELD_B_1_TYPE:
			m_Value = (b_1 *)(pTMU->pMessage + nOffset);
			break;
		case FIELD_UB_1_TYPE:
			m_Value = (ub_1 *)(pTMU->pMessage + nOffset);
			break;
		case FIELD_B_2_TYPE:
			m_Value = (b_2 *)(pTMU->pMessage + nOffset);
			break;
		case FIELD_UB_2_TYPE:
			m_Value = (ub_2 *)(pTMU->pMessage + nOffset);
			break;
		case FIELD_B_4_TYPE:
			m_Value = (b_4 *)(pTMU->pMessage + nOffset);
			break;
		case FIELD_UB_4_TYPE:
			m_Value = (ub_4 *)(pTMU->pMessage + nOffset);
			break;
		case FIELD_B_8_TYPE:
			m_Value = (b_8 *)(pTMU->pMessage + nOffset);
			break;
		case FIELD_UB_8_TYPE:
			m_Value = (ub_8 *)(pTMU->pMessage + nOffset);
			break;
		case FIELD_FB_4_TYPE:
			m_Value = (fb_4 *)(pTMU->pMessage + nOffset);
			break;
		case FIELD_FB_8_TYPE:
			m_Value = (fb_8 *)(pTMU->pMessage + nOffset);
			break;
		case FIELD_STR_TYPE:
		{
			v_ tmp((const ch_1 *)(pTMU->pMessage + nOffset), 
				   m_pField->Size(pTMU->pMessage, pTMU->nSize));

			m_Value = tmp;
		}
		break;
		case FIELD_GROUP_TYPE:
		{
			if (nIndex)
			{
				v_ tmp((obj_ *)&(pTMU->pMessage),
					   nOffset,
					   m_pField->GetUnitSize());

				m_Value = tmp;
			}
			else
			{
				v_ tmp((obj_ *)&(pTMU->pMessage),
					   nOffset,
					   m_pField->Size(pTMU->pMessage, pTMU->nSize));

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
