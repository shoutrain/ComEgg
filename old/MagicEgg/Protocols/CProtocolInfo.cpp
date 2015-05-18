#include "CProtocolInfo.h"
#include "CPDUInfo.h"

#include "stdio.h"

ret_ CProtocolInfo::Stop()
{
	for (map_pdu::iterator pos1 = m_PDUInfoMap.begin();
		 pos1 != m_PDUInfoMap.end(); pos1++)
	{
#ifdef _DEBUG_
		if (!pos1->second)
			return ELEMENT_NULL_IN_CONTAINER;
#endif
		_DEL(pos1->second);
	}

	m_PDUInfoMap.clear();

	for (map_field::iterator pos2 = m_HeadFieldMap.begin();
		 pos2 != m_HeadFieldMap.end(); pos2++)
	{
#ifdef _DEBUG_
			if (!pos2->second)
				return ELEMENT_NULL_IN_CONTAINER;
#endif
			_DEL(pos2->second);
	}

	m_HeadFieldMap.clear();

	m_pField = null_v;
	m_pCurField = null_v;

	return SUCCESS;
}

ret_ CProtocolInfo::AddHeadField(const TField &Field, 
								 const ch_1 *pszGroupName)
{
#ifdef _DEBUG_
	if (!Field.sName ||	0 == Field.sName[0])
		return PARAMETER_ERROR | PARAMETER_1;
#endif

	ret_ Ret;
	CField *pField = null_v;
	CField *pGroupField = null_v;
	ch_1 szName[VARIABLE_NAME_LENGTH * 2] = {0};

	if (pszGroupName && 0 != pszGroupName[0])
	{
		Ret = GetHeadField(pszGroupName, pGroupField);

#ifdef _DEBUG_
		if (SUCCESS != Ret)
			return Ret;
#endif

		sprintf(szName, "%s.%s", pszGroupName, Field.sName);
	}
	else
	{
		sprintf(szName, "%s", Field.sName);
	}

	// Check if there is a field which name is same as the field's name,
	// in the map.
	if (m_HeadFieldMap.end() != m_HeadFieldMap.find(szName))
		return (ELEMENT_EXIST_IN_CONTAINER);
	
	switch (Field.Style)
	{
	case FIELD_NORMAL_STYLE:
	{
		EFieldType Type;

		if (1 == Field.nLength && Field.IsSigned)
			Type = FIELD_B_1_TYPE;
		else if (1 == Field.nLength && !Field.IsSigned)
			Type = FIELD_UB_1_TYPE;
		else if (2 == Field.nLength && Field.IsSigned)
			Type = FIELD_B_2_TYPE;
		else if (2 == Field.nLength && !Field.IsSigned)
			Type = FIELD_UB_2_TYPE;
		else if (4 == Field.nLength && Field.IsSigned)
			Type = FIELD_B_4_TYPE;
		else if (4 == Field.nLength && !Field.IsSigned)
			Type = FIELD_UB_4_TYPE;
		else if (8 == Field.nLength && Field.IsSigned)
			Type = FIELD_B_8_TYPE;
		else if (8 == Field.nLength && !Field.IsSigned)
			Type = FIELD_UB_8_TYPE;
#ifdef _DEBUG_
		else
			return PARAMETER_ERROR | PARAMETER_1;

		if (0 != Field.nSize ||	0 != Field.sSizeName[0])
			return PARAMETER_ERROR | PARAMETER_1;
#endif

		pField = new CFieldNumber(szName, Type, pGroupField);
	}
	break;
	case FIELD_FLOAT_STYLE:
	{
		EFieldType Type;

		if (4 == Field.nLength)
			Type = FIELD_FB_4_TYPE;
		else if (8 == Field.nLength)
			Type = FIELD_FB_8_TYPE;
#ifdef _DEBUG_
		else
			return PARAMETER_ERROR | PARAMETER_1;

		if (0 != Field.nSize ||	0 != Field.sSizeName[0])
			return PARAMETER_ERROR | PARAMETER_1;
#endif

		pField = new CFieldNumber(szName, Type, pGroupField);
	}
	break;
	case FIELD_STRING_STYLE:
	{
#ifdef _DEBUG_
		if (0 == Field.nSize ||	0 != Field.sSizeName[0])
			return PARAMETER_ERROR | PARAMETER_1;
#endif

		pField = new CFieldString(szName, Field.nSize, pGroupField);
	}
	break;
	case FIELD_GROUP_STYLE:
	{
#ifdef _DEBUG_
		if (0 != Field.nSize)
			return PARAMETER_ERROR | PARAMETER_1;

		if (0 == Field.sSizeName[0])
			return PARAMETER_ERROR | PARAMETER_1;
#endif
		
		CField *pSizeField = null_v;

		Ret = GetHeadField(Field.sSizeName, pSizeField);

#ifdef _DEBUG_
		if (SUCCESS != Ret)
			return Ret;
#endif
				
		pField = new CFieldGroup(szName, pSizeField);
	}
	break;
#ifdef _DEBUG_
	default:
		return PARAMETER_TYPE_ERROR | PARAMETER_1;
#endif
	}

	if (!pGroupField)
	{
		if (m_pCurField)
			m_pCurField->Attach(pField);
		else
			m_pField = pField;
	}
	else
	{
		pGroupField->SetSubField(pField);
	}

	m_pCurField = pField;
	m_HeadFieldMap.insert(map_field::value_type(szName, pField));

	return SUCCESS;
}

ret_ CProtocolInfo::GetHeadField(const ch_1 *pszName, CField *&pField)
{
#ifdef _DEBUG_
	if (!pszName)
		return PARAMETER_NULL | PARAMETER_1;

	if (0 == pszName[0])
		return PARAMETER_EMPTY | PARAMETER_1;

	if (pField)
		return PARAMETER_NOT_NULL | PARAMETER_2;
#endif

	map_field::iterator pos = m_HeadFieldMap.find(pszName);

#ifdef _DEBUG_
	if (m_HeadFieldMap.end() != pos)
	{
		if (pos->second)
#endif
			pField = (CField *)pos->second;

#ifdef _DEBUG_
		else
			return ELEMENT_NULL_IN_CONTAINER;
	}
	else
	{
		return NO_ELEMENT_IN_CONTAINER;
	}
#endif

	return SUCCESS;
}

ret_ CProtocolInfo::AddPDU(const ch_1 *pszName, 
						   CPDUInfo *&pPDUInfo)
{
#ifdef _DEBUG_
	if (!pszName)
		return (PARAMETER_NULL | PARAMETER_1);

	if (0 == pszName[0])
		return (PARAMETER_EMPTY | PARAMETER_1);

	if (pPDUInfo)
		return (PARAMETER_NOT_NULL | PARAMETER_2);

	// pPDUInfo should be valid, no check code here.
#endif

	pPDUInfo = new CPDUInfo(m_pField);
	m_PDUInfoMap.insert(map_pdu::value_type(pszName, pPDUInfo));

	return (SUCCESS);
}

ret_ CProtocolInfo::GetPDU(const ch_1 *pszName, CPDUInfo *&pPDUInfo)
{
#ifdef _DEBUG_
	if (!pszName)
		return (PARAMETER_NULL | PARAMETER_1);

	if (0 == pszName[0])
		return (PARAMETER_EMPTY | PARAMETER_1);

	if (pPDUInfo)
		return (PARAMETER_NOT_NULL | PARAMETER_2);
#endif

	map_pdu::iterator pos = m_PDUInfoMap.find(pszName);

#ifdef _DEBUG_
	if (m_PDUInfoMap.end() != pos)
	{
		if (pos->second)
#endif
			pPDUInfo = (CPDUInfo *)pos->second;

#ifdef _DEBUG_
		else
			return (ELEMENT_NULL_IN_CONTAINER);
	}
	else
	{
		return (NO_ELEMENT_IN_CONTAINER);
	}
#endif

	return (SUCCESS);
}
