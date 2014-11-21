#include "CRegister.h"

CRegister *CRegister::m_pInstance = null_v;

ret_ CRegister::Stop()
{
	_START(STOP);

	for (map_category::iterator pos = m_CategoryMap.begin(); 
		 pos != m_CategoryMap.end(); pos++)
	{
#ifdef _DEBUG_
		if (!pos->second)
			_RET(ELEMENT_NULL_IN_CONTAINER);
#endif

        for (mapVariable::iterator pos_ = pos->second->begin();
			pos_ != pos->second->end(); pos_++)
		{
#ifdef _DEBUG_
			if (!pos_->second)
				_RET(ELEMENT_NULL_IN_CONTAINER);
#endif

			_DEL(pos_->second);
		}

		pos->second->clear();
		_DEL(pos->second);
	}

	m_CategoryMap.clear();

	_RET(SUCCESS);
}

ret_ CRegister::Register(const ch_1 *pszCategory, 
						 const ch_1 *pszKey, 
						 const v_ *pVariable, 
						 const bool_ bIsCovered)
{
	_START(REGITSTER);

#ifdef _DEBUG_
	if (!pszCategory)
		_RET(PARAMETER_NULL | PARAMETER_1);

	if (0 == pszCategory[0])
		_RET(PARAMETER_EMPTY | PARAMETER_1);

	if (!pszKey)
		_RET(PARAMETER_NULL | PARAMETER_2);

	if (0 == pszKey[0])
		_RET(PARAMETER_EMPTY | PARAMETER_2);

	if (!pVariable)
		_RET(PARAMETER_NULL | PARAMETER_3);
#endif

	map_category::iterator pos = m_CategoryMap.find(pszCategory);

	if (m_CategoryMap.end() != pos)
	{
#ifdef _DEBUG_
		if (!pos->second)
			_RET(ELEMENT_NULL_IN_CONTAINER);
#endif

        mapVariable::iterator pos_ = pos->second->find(pszKey);

		if (pos->second->end() != pos_)
		{
#ifdef _DEBUG_
			if (!pos_->second)
				_RET(ELEMENT_NULL_IN_CONTAINER);
#endif

			if (bIsCovered)
			{
				_DEL(pos_->second);
				pos->second->erase(pszKey);

				try
				{
					v_ *pNewVariable = new v_(*pVariable);

					pos->second->insert(
                            mapVariable::value_type(pszKey, pNewVariable));
				}
				catch (...)
				{
					_RET(DEFINE_VARIABLE_FAILURE);
				}
			}
		}
		else
		{
			try
			{
				v_ *pNewVariable = new v_(*pVariable);

				pos->second->insert(
                        mapVariable::value_type(pszKey, pNewVariable));
			}
			catch (...)
			{
				_RET(DEFINE_VARIABLE_FAILURE);
			}
		}
	}
	else
	{
        mapVariable *pVarialbeMap = new mapVariable;

		try
		{
			v_ *pNewVariable = new v_(*pVariable);

			pVarialbeMap->insert(
                    mapVariable::value_type(pszKey, pNewVariable));
		}
		catch (...)
		{
			_DEL(pVarialbeMap);

			_RET(DEFINE_VARIABLE_FAILURE);
		}

		m_CategoryMap.insert(
			map_category::value_type(pszCategory, pVarialbeMap));
	}

	_RET(SUCCESS);
}

ret_ CRegister::Unregister(const ch_1 *pszCategory, const ch_1 *pszKey)
{
	_START(UNREGISTER);

#ifdef _DEBUG_
	if (!pszCategory)
		_RET(PARAMETER_NULL | PARAMETER_1);

	if (0 == pszCategory[0])
		_RET(PARAMETER_EMPTY | PARAMETER_1);

	if (!pszKey)
		_RET(PARAMETER_NULL | PARAMETER_2);

	if (0 == pszKey[0])
		_RET(PARAMETER_EMPTY | PARAMETER_2);
#endif

	map_category::iterator pos = m_CategoryMap.find(pszCategory);

	if (m_CategoryMap.end() != pos)
	{
#ifdef _DEBUG_
		if (!pos->second)
			_RET(ELEMENT_NULL_IN_CONTAINER);
#endif

        mapVariable::iterator pos_ = pos->second->find(pszKey);

		if (pos->second->end() != pos_)
		{
#ifdef _DEBUG_
			if (!pos_->second)
				_RET(ELEMENT_NULL_IN_CONTAINER);
#endif

			_DEL(pos_->second);
			pos->second->erase(pszKey);

			if (0 == pos->second->size())
			{
				_DEL(pos->second);
				m_CategoryMap.erase(pszCategory);
			}
		}
	}

	_RET(SUCCESS);
}

ret_ CRegister::Search(const ch_1 *pszCategory, const ch_1 *pszKey, v_ *&pVariable)
{
	_START(SEARCH);

#ifdef _DEBUG_
	if (!pszCategory)
		_RET(PARAMETER_NULL | PARAMETER_1);

	if (0 == pszCategory[0])
		_RET(PARAMETER_EMPTY | PARAMETER_1);

	if (!pszKey)
		_RET(PARAMETER_NULL | PARAMETER_2);

	if (0 == pszKey[0])
		_RET(PARAMETER_EMPTY | PARAMETER_2);

	if (pVariable)
		_RET(PARAMETER_NOT_NULL | PARAMETER_3);
#endif

	map_category::iterator pos = m_CategoryMap.find(pszCategory);

	if (m_CategoryMap.end() != pos)
	{
#ifdef _DEBUG_
		if (!pos->second)
			_RET(ELEMENT_NULL_IN_CONTAINER);
#endif

        mapVariable::iterator pos_ = pos->second->find(pszKey);

		if (pos->second->end() != pos_)
		{
#ifdef _DEBUG_
			if (!pos_->second)
				_RET(ELEMENT_NULL_IN_CONTAINER);
#endif

			pVariable = pos_->second;

			_RET(SUCCESS);
		}
	}

	_RET(NO_ELEMENT_IN_CONTAINER);
}
