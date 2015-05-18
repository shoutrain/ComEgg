#include "CInterfaceInfo.h"

#include "../Data/CFieldNumber.h"
#include "../Data/CFieldString.h"
#include "../Data/CFieldGroup.h"

ret_ CInterfaceInfo::Stop()
{
	_START(STOP);

	for (map_field::iterator pos1 = m_InFieldMap.begin(); 
		 pos1 != m_InFieldMap.end();
		 pos1++)
	{
#ifdef _DEBUG_
		if (!pos1->second)
			_RET(ELEMENT_NULL_IN_CONTAINER);
#endif
		_DEL(pos1->second);
	}

	for (map_field::iterator pos2 = m_OutFieldMap.begin(); 
		 pos2 != m_OutFieldMap.end();
		 pos2++)
	{
#ifdef _DEBUG_
		if (!pos2->second)
			_RET(ELEMENT_NULL_IN_CONTAINER);
#endif
		_DEL(pos2->second);
	}

	m_InFieldMap.clear();
	m_OutFieldMap.clear();
	m_pInField = null_v;
	m_pInCurField = null_v;
	m_pOutField = null_v;
	m_pOutCurField = null_v;

	_RET(SUCCESS);
}

ret_ CInterfaceInfo::AddInField(const TField &Field, const ch_1 *pszGroupName)
{
	_START(ADD_IN_FIELD);

#ifdef _DEBUG_
	if (!Field.sName ||	0 == Field.sName[0])
		_RET(PARAMETER_ERROR | PARAMETER_1);
#endif

	ret_ Ret;
	CField *pField = null_v;
	CField *pGroupField = null_v;
	ch_1 sName[VARIABLE_NAME_LENGTH * 2] = {0};

	if (pszGroupName && 0 != pszGroupName[0])
	{
		Ret = _ERR(GetInField(pszGroupName, pGroupField));

#ifdef _DEBUG_
		if (SUCCESS != _ERR(Ret))
			_RET_BY(Ret);
#endif

		sprintf(sName, "%s.%s", pszGroupName, Field.sName);
	}
	else
	{
		sprintf(sName, "%s", Field.sName);
	}

	// Check if there is a field which name is same as the field's name,
	// in the map.
	if (m_InFieldMap.end() != m_InFieldMap.find(sName))
		_RET(ELEMENT_EXIST_IN_CONTAINER);
	
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
			_RET(PARAMETER_ERROR | PARAMETER_1);

		if (0 != Field.nSize ||	0 != Field.sSizeName[0])
			_RET(PARAMETER_ERROR | PARAMETER_1);
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
			_RET(PARAMETER_ERROR | PARAMETER_1);

		if (0 != Field.nSize ||	0 != Field.sSizeName[0])
			_RET(PARAMETER_ERROR | PARAMETER_1);
#endif

		pField = new CFieldNumber(sName, Type, pGroupField);
	}
	break;
	case FIELD_STRING_STYLE:
	{
#ifdef _DEBUG_
		if (0 == Field.nSize ||	0 != Field.sSizeName[0])
			_RET(PARAMETER_ERROR | PARAMETER_1);
#endif

		pField = new CFieldString(sName, Field.nSize, pGroupField);
	}
	break;
	case FIELD_GROUP_STYLE:
	{
#ifdef _DEBUG_
		if (0 != Field.nSize)
			_RET(PARAMETER_ERROR | PARAMETER_1);

		if (0 == Field.sSizeName[0])
			_RET(PARAMETER_ERROR | PARAMETER_1);
#endif
		
		CField *pSizeField = null_v;

		Ret = _ERR(GetInField(Field.sSizeName, pSizeField));

#ifdef _DEBUG_
		if (SUCCESS != _ERR(Ret))
			_RET_BY(Ret);
#endif
				
		pField = new CFieldGroup(sName, pSizeField);
	}
	break;
#ifdef _DEBUG_
	default:
		_RET(PARAMETER_TYPE_ERROR | PARAMETER_1);
#endif
	}

	if (!pGroupField)
	{
		if (m_pInCurField)
			m_pInCurField->Attach(pField);
		else
			m_pInField = pField;

		m_pInCurField = pField;
	}
	else
	{
		pGroupField->SetSubField(pField);
	}

	m_InFieldMap.insert(map_field::value_type(sName, pField));

	_RET(SUCCESS);
}

ret_ CInterfaceInfo::AddOutField(const TField &Field, const ch_1 *pszGroupName)
{
	_START(ADD_OUT_FIELD);

#ifdef _DEBUG_
	if (!Field.sName ||	0 == Field.sName[0])
		_RET(PARAMETER_ERROR | PARAMETER_1);
#endif

	ret_ Ret;
	CField *pField = null_v;
	CField *pGroupField = null_v;
	ch_1 sName[VARIABLE_NAME_LENGTH * 2] = {0};

	if (pszGroupName && 0 != pszGroupName[0])
	{
		Ret = _ERR(GetOutField(pszGroupName, pGroupField));

#ifdef _DEBUG_
		if (SUCCESS != _ERR(Ret))
			_RET_BY(Ret);
#endif

		sprintf(sName, "%s.%s", pszGroupName, Field.sName);
	}
	else
	{
		sprintf(sName, "%s", Field.sName);
	}

	// Check if there is a field which name is same as the field's name,
	// in the map.
	if (m_OutFieldMap.end() != m_OutFieldMap.find(sName))
		_RET(ELEMENT_EXIST_IN_CONTAINER);

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
			_RET(PARAMETER_ERROR | PARAMETER_1);

		if (0 != Field.nSize ||	0 != Field.sSizeName[0])
			_RET(PARAMETER_ERROR | PARAMETER_1);
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
			_RET(PARAMETER_ERROR | PARAMETER_1);

		if (0 != Field.nSize ||	0 != Field.sSizeName[0])
			_RET(PARAMETER_ERROR | PARAMETER_1);
#endif

		pField = new CFieldNumber(sName, Type, pGroupField);
	}
	break;
	case FIELD_STRING_STYLE:
	{
#ifdef _DEBUG_
		if (0 == Field.nSize ||	0 != Field.sSizeName[0])
			_RET(PARAMETER_ERROR | PARAMETER_1);
#endif

		pField = new CFieldString(sName, Field.nSize, pGroupField);
	}
	break;
	case FIELD_GROUP_STYLE:
	{
#ifdef _DEBUG_
		if (0 != Field.nSize)
			_RET(PARAMETER_ERROR | PARAMETER_1);

		if (0 == Field.sSizeName[0])
			_RET(PARAMETER_ERROR | PARAMETER_1);
#endif

		CField *pSizeField = null_v;

		Ret = _ERR(GetOutField(Field.sSizeName, pSizeField));

#ifdef _DEBUG_
		if (SUCCESS != _ERR(Ret))
			_RET_BY(Ret);
#endif

		pField = new CFieldGroup(sName, pSizeField);
	}
	break;
#ifdef _DEBUG_
	default:
		_RET(PARAMETER_TYPE_ERROR | PARAMETER_1);
#endif
	}

	if (!pGroupField)
	{
		if (m_pOutCurField)
			m_pOutCurField->Attach(pField);
		else
			m_pOutField = pField;

		m_pOutCurField = pField;
	}
	else
	{
		pGroupField->SetSubField(pField);
	}

	m_pOutCurField = pField;
	m_OutFieldMap.insert(map_field::value_type(sName, pField));

	_RET(SUCCESS);
}

ret_ CInterfaceInfo::GetInField(const ch_1 *pszName, 
								CField *&pField)
{
	_START(GET_IN_FIELD);

#ifdef _DEBUG_
	if (!pszName)
		_RET(PARAMETER_NULL | PARAMETER_1);

	if (0 == pszName[0])
		_RET(PARAMETER_EMPTY | PARAMETER_1);

	if (pField)
		_RET(PARAMETER_NOT_NULL | PARAMETER_2);
#endif

	map_field::iterator pos = m_InFieldMap.find(pszName);

#ifdef _DEBUG_
	if (m_InFieldMap.end() != pos)
	{
		if (pos->second)
#endif
			pField = (CField *)pos->second;

#ifdef _DEBUG_
		else
			_RET(ELEMENT_NULL_IN_CONTAINER);
	}
	else
	{
		_RET(NO_ELEMENT_IN_CONTAINER);
	}
#endif

	_RET(SUCCESS);
}

ret_ CInterfaceInfo::GetOutField(const ch_1 *pszName, 
								 CField *&pField)
{
	_START(GET_OUT_FIELD);

#ifdef _DEBUG_
	if (!pszName)
		_RET(PARAMETER_NULL | PARAMETER_1);

	if (0 == pszName[0])
		_RET(PARAMETER_EMPTY | PARAMETER_1);

	if (pField)
		_RET(PARAMETER_NOT_NULL | PARAMETER_2);
#endif

	map_field::iterator pos = m_OutFieldMap.find(pszName);

#ifdef _DEBUG_
	if (m_OutFieldMap.end() != pos)
	{
		if (pos->second)
#endif
			pField = (CField *)pos->second;

#ifdef _DEBUG_
		else
			_RET(ELEMENT_NULL_IN_CONTAINER);
	}
	else
	{
		_RET(NO_ELEMENT_IN_CONTAINER);
	}
#endif

	_RET(SUCCESS);
}

ret_ CInterfaceInfo::GetInStruct(CField *&pField)
{
	_START(GET_IN_STRUCT);
#ifdef _DEBUG_
	if (pField)
		_RET(PARAMETER_NOT_NULL | PARAMETER_1);
#endif

	pField = m_pInField;

	_RET(SUCCESS);
}

ret_ CInterfaceInfo::GetOutStruct(CField *&pField)
{
	_START(GET_OUT_STRUCT);
#ifdef _DEBUG_
	if (pField)
		_RET(PARAMETER_NOT_NULL | PARAMETER_1);
#endif

	pField = m_pOutField;

	_RET(SUCCESS);
}
