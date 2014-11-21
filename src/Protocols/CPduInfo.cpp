#include "CPduInfo.h"

ret_ CPduInfo::Start(const CField *pHeadField)
{
	_START(START);

	m_pField = null_v;
	m_pCurField = null_v;

	if (pHeadField)
        m_pField = (CField *) pHeadField->clone(null_v, null_v);

	CField *p = m_pField;
		 
	while (p)
	{
        if (FIELD_GROUP_TYPE == p->type())
		{
            CField *q = (CField *) p->getSubField();

			while (q)
			{
				ch_1 sName[VARIABLE_NAME_LENGTH * 2] = {0};

                sprintf(sName, "%s.%s", p->name(), q->name());
                m_FieldMap.insert(mapField::value_type(sName, q));

                q = (CField *) q->getNextField();
			}
		}

		m_pCurField = p;
        m_FieldMap.insert(mapField::value_type(p->name(), p));

        p = (CField *) p->getNextField();
	}

	_RET(SUCCESS);
}

ret_ CPduInfo::Stop()
{
	_START(STOP);

    for (mapField::iterator pos = m_FieldMap.begin(); pos != m_FieldMap.end();
		 pos++)
	{
#ifdef _DEBUG_
		if (!pos->second)
			_RET(ELEMENT_NULL_IN_CONTAINER);
#endif
		_DEL(pos->second);
	}

	m_FieldMap.clear();
	m_pField = null_v;
	m_pCurField = null_v;

	_RET(SUCCESS);
}

ret_ CPduInfo::AddField(const TField &Field, const ch_1 *pszGroupName)
{
	_START(ADD_FIELD);

#ifdef _DEBUG_
	if (!Field.name ||	0 == Field.name[0])
		_RET(PARAMETER_ERROR | PARAMETER_1);
#endif

	ret_ Ret;
	CField *pField = null_v;
	CField *pGroupField = null_v;
	ch_1 sName[VARIABLE_NAME_LENGTH * 2] = {0};

	if (pszGroupName && 0 != pszGroupName[0])
	{
		Ret = _ERR(GetField(pszGroupName, pGroupField));

#ifdef _DEBUG_
		if (SUCCESS != _ERR(Ret))
			_RET_BY(Ret);
#endif

        sprintf(sName, "%s.%s", pszGroupName, Field.name);
	}
	else
	{
        sprintf(sName, "%s", Field.name);
	}

	// Check if there is a field which name is same as the field's name,
	// in the map.
	if (m_FieldMap.end() != m_FieldMap.find(sName))
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

		pField = new CFieldNumber(sName, Type, pGroupField);
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

		pField = new CFieldNumber(sName, Type, pGroupField);
	}
	break;
	case FIELD_STRING_STYLE:
	{
#ifdef _DEBUG_
		if (0 == Field.size ||	0 != Field.sizeName[0])
			_RET(PARAMETER_ERROR | PARAMETER_1);
#endif

        pField = new CFieldString(sName, Field.size, pGroupField);
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

        Ret = _ERR(GetField(Field.sizeName, pSizeField));

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

    m_FieldMap.insert(mapField::value_type(sName, pField));

	_RET(SUCCESS);
}

ret_ CPduInfo::GetField(const ch_1 *pszName, CField *&pField)
{
	_START(GET_FIELD);

#ifdef _DEBUG_
	if (!pszName)
		_RET(PARAMETER_NULL | PARAMETER_1);

	if (0 == pszName[0])
		_RET(PARAMETER_EMPTY | PARAMETER_1);

	if (pField)
		_RET(PARAMETER_NOT_NULL | PARAMETER_2);
#endif

    mapField::const_iterator pos = m_FieldMap.find(pszName);

#ifdef _DEBUG_
	if (m_FieldMap.end() != pos)
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

ret_ CPduInfo::GetStruct(CField *&pField)
{
	_START(GET_STRUCT);

#ifdef _DEBUG_
	if (pField)
		_RET(PARAMETER_NOT_NULL | PARAMETER_1);
#endif

	pField = m_pField;

	_RET(SUCCESS);
}
