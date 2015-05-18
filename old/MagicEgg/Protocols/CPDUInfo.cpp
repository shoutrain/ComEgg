#include "CPDUInfo.h"

#include "stdio.h"

ret_ CPDUInfo::Start(const CField *pHeadField)
{
	m_pField = null_v;
	m_pCurField = null_v;

	if (pHeadField)
		m_pField = (CField *)pHeadField->Clone(null_v, null_v);

	CField *p = m_pField;
		 
	while (p)
	{
		if (FIELD_GROUP_TYPE == p->Type())
		{
			CField *q = (CField *)p->GetSubField();

			while (q)
			{
				ch_1 sName[VARIABLE_NAME_LENGTH * 2] = {0};

				sprintf(sName, "%s.%s", p->Name(), q->Name());
				m_FieldMap.insert(map_field::value_type(sName, q));

				q = (CField *)q->GetNextField();
			}
		}

		m_pCurField = p;
		m_FieldMap.insert(map_field::value_type(p->Name(), p));

		p = (CField *)p->GetNextField();
	}

	return SUCCESS;
}

ret_ CPDUInfo::Stop()
{
	for (map_field::iterator pos = m_FieldMap.begin(); 
		 pos != m_FieldMap.end(); pos++)
	{
#ifdef _DEBUG_
		if (!pos->second)
			return ELEMENT_NULL_IN_CONTAINER;
#endif
		_DEL(pos->second);
	}

	m_FieldMap.clear();
	m_pField = null_v;
	m_pCurField = null_v;

	return SUCCESS;
}

ret_ CPDUInfo::AddField(const TField &Field, const ch_1 *pszGroupName)
{
#ifdef _DEBUG_
	if (!Field.sName ||	0 == Field.sName[0])
		return PARAMETER_ERROR | PARAMETER_1;
#endif

	ret_ Ret;
	CField *pField = null_v;
	CField *pGroupField = null_v;
	ch_1 sName[VARIABLE_NAME_LENGTH * 2] = {0};

	if (pszGroupName && 0 != pszGroupName[0])
	{
		Ret = GetField(pszGroupName, pGroupField);

#ifdef _DEBUG_
		if (SUCCESS != (Ret))
			return Ret;
#endif

		sprintf(sName, "%s.%s", pszGroupName, Field.sName);
	}
	else
	{
		sprintf(sName, "%s", Field.sName);
	}

	// Check if there is a field which name is same as the field's name,
	// in the map.
	if (m_FieldMap.end() != m_FieldMap.find(sName))
		return ELEMENT_EXIST_IN_CONTAINER;
	
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

		pField = new CFieldNumber(sName, Type, pGroupField);
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

		pField = new CFieldNumber(sName, Type, pGroupField);
	}
	break;
	case FIELD_STRING_STYLE:
	{
#ifdef _DEBUG_
		if (0 == Field.nSize ||	0 != Field.sSizeName[0])
			return PARAMETER_ERROR | PARAMETER_1;
#endif

		pField = new CFieldString(sName, Field.nSize, pGroupField);
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

		Ret = GetField(Field.sSizeName, pSizeField);

#ifdef _DEBUG_
		if (SUCCESS != (Ret))
			return Ret;
#endif
				
		pField = new CFieldGroup(sName, pSizeField);
	}
	break;
#ifdef _DEBUG_
	default:
		return PARAMETER_ERROR | PARAMETER_1;
#endif
	}

	if (!pGroupField)
	{
		if (m_pCurField)
			m_pCurField->Attach(pField);
		else
			m_pField = pField;

		m_pCurField = pField;
	}
	else
	{
		pGroupField->SetSubField(pField);
	}

	m_FieldMap.insert(map_field::value_type(sName, pField));

	return SUCCESS;
}

ret_ CPDUInfo::GetField(const ch_1 *pszName, CField *&pField) 
{
#ifdef _DEBUG_
	if (!pszName)
		return PARAMETER_NULL | PARAMETER_1;

	if (0 == pszName[0])
		return PARAMETER_EMPTY | PARAMETER_1;

	if (pField)
		return PARAMETER_NOT_NULL | PARAMETER_2;
#endif

	map_field::const_iterator pos = m_FieldMap.find(pszName);

#ifdef _DEBUG_
	if (m_FieldMap.end() != pos)
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

ret_ CPDUInfo::GetStruct(CField *&pField)
{
#ifdef _DEBUG_
	if (pField)
		return PARAMETER_NOT_NULL | PARAMETER_1;
#endif

	pField = m_pField;

	return SUCCESS;
}
