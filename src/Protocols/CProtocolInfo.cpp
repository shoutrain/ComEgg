#include "CPduInfo.h"
#include "CProtocolInfo.h"

ret_ CProtocolInfo::Stop()
{
	_START(STOP);

	for (map_pdu::iterator pos1 = m_PDUInfoMap.begin();
		 pos1 != m_PDUInfoMap.end(); pos1++)
	{
#ifdef _DEBUG_
		if (!pos1->second)
			_RET(ELEMENT_NULL_IN_CONTAINER);
#endif
		_DEL(pos1->second);
	}

	m_PDUInfoMap.clear();

    for (mapField::iterator pos2 = m_HeadFieldMap.begin();
		 pos2 != m_HeadFieldMap.end(); pos2++)
	{
#ifdef _DEBUG_
			if (!pos2->second)
				_RET(ELEMENT_NULL_IN_CONTAINER);
#endif
			_DEL(pos2->second);
	}

	m_HeadFieldMap.clear();

	m_pField = null_v;
	m_pCurField = null_v;

	_RET(SUCCESS);
}

ret_ CProtocolInfo::AddHeadField(const TField &Field, 
								 const ch_1 *pszGroupName)
{
	_START(ADD_HEAD_FIELD);

#ifdef _DEBUG_
	if (!Field.name ||	0 == Field.name[0])
		_RET(PARAMETER_ERROR | PARAMETER_1);

#endif

	ret_ Ret;
	CField *pField = null_v;
	CField *pGroupField = null_v;
	ch_1 szName[VARIABLE_NAME_LENGTH * 2] = {0};

	if (pszGroupName && 0 != pszGroupName[0])
	{
		Ret = _ERR(GetHeadField(pszGroupName, pGroupField));

#ifdef _DEBUG_
		if (SUCCESS != _ERR(Ret))
			_RET_BY(Ret);
#endif

        sprintf(szName, "%s.%s", pszGroupName, Field.name);
	}
	else
	{
        sprintf(szName, "%s", Field.name);
	}

	// Check if there is a field which name is same as the field's name,
	// in the map.
	if (m_HeadFieldMap.end() != m_HeadFieldMap.find(szName))
		_RET(ELEMENT_EXIST_IN_CONTAINER);

    switch (Field.style)
	{
	case FIELD_NORMAL_STYLE:
	{
		EFieldType Type;

        if (1 == Field.length && Field.isSigned)
			Type = FIELD_B_1_TYPE;
        else if (1 == Field.length && !Field.isSigned)
			Type = FIELD_UB_1_TYPE;
        else if (2 == Field.length && Field.isSigned)
			Type = FIELD_B_2_TYPE;
        else if (2 == Field.length && !Field.isSigned)
			Type = FIELD_UB_2_TYPE;
        else if (4 == Field.length && Field.isSigned)
			Type = FIELD_B_4_TYPE;
        else if (4 == Field.length && !Field.isSigned)
			Type = FIELD_UB_4_TYPE;
        else if (8 == Field.length && Field.isSigned)
			Type = FIELD_B_8_TYPE;
        else if (8 == Field.length && !Field.isSigned)
			Type = FIELD_UB_8_TYPE;
#ifdef _DEBUG_
		else
			_RET(PARAMETER_ERROR | PARAMETER_1);

		if (0 != Field.size ||	0 != Field.sizeName[0])
			_RET(PARAMETER_ERROR | PARAMETER_1);
#endif

		pField = new CFieldNumber(szName, Type, pGroupField);
	}
	break;
	case FIELD_FLOAT_STYLE:
	{
		EFieldType Type;

        if (4 == Field.length)
			Type = FIELD_FB_4_TYPE;
        else if (8 == Field.length)
			Type = FIELD_FB_8_TYPE;
#ifdef _DEBUG_
		else
			_RET(PARAMETER_ERROR | PARAMETER_1);

		if (0 != Field.size ||	0 != Field.sizeName[0])
			_RET(PARAMETER_ERROR | PARAMETER_1);
#endif

		pField = new CFieldNumber(szName, Type, pGroupField);
	}
	break;
	case FIELD_STRING_STYLE:
	{
#ifdef _DEBUG_
		if (0 == Field.size ||	0 != Field.sizeName[0])
			_RET(PARAMETER_ERROR | PARAMETER_1);
#endif

        pField = new CFieldString(szName, Field.size, pGroupField);
	}
	break;
	case FIELD_GROUP_STYLE:
	{
#ifdef _DEBUG_
		if (0 != Field.size)
			_RET(PARAMETER_ERROR | PARAMETER_1);

		if (0 == Field.sizeName[0])
			_RET(PARAMETER_ERROR | PARAMETER_1);
#endif
		
		CField *pSizeField = null_v;

        Ret = _ERR(GetHeadField(Field.sizeName, pSizeField));

#ifdef _DEBUG_
		if (SUCCESS != _ERR(Ret))
			_RET_BY(Ret);
#endif
				
		pField = new CFieldGroup(szName, pSizeField);
	}
	break;
#ifdef _DEBUG_
	default:
		_RET(PARAMETER_TYPE_ERROR | PARAMETER_1);
#endif
	}

	if (!pGroupField)
	{
		if (m_pCurField)
            m_pCurField->attach(pField);
		else
			m_pField = pField;

		m_pCurField = pField;
	}
	else
	{
        pGroupField->setSubField(pField);
	}

    m_HeadFieldMap.insert(mapField::value_type(szName, pField));

	_RET(SUCCESS);
}

ret_ CProtocolInfo::GetHeadField(const ch_1 *pszName, CField *&pField)
{
	_START(GET_HEAD_FIELD);

#ifdef _DEBUG_
	if (!pszName)
		_RET(PARAMETER_NULL | PARAMETER_1);

	if (0 == pszName[0])
		_RET(PARAMETER_EMPTY | PARAMETER_1);

	if (pField)
		_RET(PARAMETER_NOT_NULL | PARAMETER_2);
#endif

    mapField::iterator pos = m_HeadFieldMap.find(pszName);

#ifdef _DEBUG_
	if (m_HeadFieldMap.end() != pos)
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

ret_ CProtocolInfo::AddPDU(const ch_1 *pszName,
        CPduInfo *&pPDUInfo)
{
	_START(ADD_PDU);

#ifdef _DEBUG_
	if (!pszName)
		_RET(PARAMETER_NULL | PARAMETER_1);

	if (0 == pszName[0])
		_RET(PARAMETER_EMPTY | PARAMETER_1);

	if (pPDUInfo)
		_RET(PARAMETER_NOT_NULL | PARAMETER_2);

	// pPDUInfo should be valid, no check code here.
#endif

    pPDUInfo = new CPduInfo(m_pField);
	m_PDUInfoMap.insert(map_pdu::value_type(pszName, pPDUInfo));

	_RET(SUCCESS);
}

ret_ CProtocolInfo::GetPDU(const ch_1 *pszName, CPduInfo *&pPDUInfo)
{
	_START(GET_PDU);

#ifdef _DEBUG_
	if (!pszName)
		_RET(PARAMETER_NULL | PARAMETER_1);

	if (0 == pszName[0])
		_RET(PARAMETER_EMPTY | PARAMETER_1);

	if (pPDUInfo)
		_RET(PARAMETER_NOT_NULL | PARAMETER_2);
#endif

	map_pdu::iterator pos = m_PDUInfoMap.find(pszName);

#ifdef _DEBUG_
	if (m_PDUInfoMap.end() != pos)
	{
		if (pos->second)
#endif
    pPDUInfo = (CPduInfo *) pos->second;

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
