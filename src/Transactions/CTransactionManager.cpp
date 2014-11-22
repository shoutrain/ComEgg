#include "CTransactionManager.h"

CTransactionManager *CTransactionManager::m_pInstance = null_v;

ret_ CTransactionManager::Stop()
{
	_START(STOP);

	for (map_transaction::iterator pos1 = m_TransactionMap.begin();
		 pos1 != m_TransactionMap.end(); pos1++)
	{
#ifdef _DEBUG_
		if (!pos1->second)
			_RET(ELEMENT_NULL_IN_CONTAINER);
#endif

		_DEL(pos1->second);
	}

	for (map_processor_category::iterator pos2 = m_CategoryMap.begin();
		 pos2 != m_CategoryMap.end(); pos2++)
	{
#ifdef _DEBUG_
		if (!pos2->second)
			_RET(ELEMENT_NULL_IN_CONTAINER);
#endif

		pos2->second->clear();
		_DEL(pos2->second);
	}

	m_TransactionMap.clear();
	m_CategoryMap.clear();

	_RET(SUCCESS);
}

ret_ CTransactionManager::AddTransaction(const ch_1 *pszTransactionName,
										 const CProcessor &Processor,
										 const size_ nSize)
{
	_START(ADD_TRANSACTION);

#ifdef _DEBUG_
	if (!pszTransactionName)
		_RET(PARAMETER_NULL | PARAMETER_1);

	if (0 == pszTransactionName[0])
		_RET(PARAMETER_EMPTY | PARAMETER_1);

	if (0 == size)
		_RET(PARAMETER_ERROR | PARAMETER_3);
#endif

#ifdef _DEBUG_
	map_transaction::iterator pos = m_TransactionMap.find(pszTransactionName);

	if (m_TransactionMap.end() != pos)
		_RET(ELEMENT_EXIST_IN_CONTAINER);
#endif

	CTransaction *pTransaction = new CTransaction(Processor, nSize);

	m_TransactionMap.insert(map_transaction::value_type(pszTransactionName,
														pTransaction));

	_RET(SUCCESS);
}

ret_ CTransactionManager::GetTransaction(const ch_1 *pszTransactionName,
										 CTransaction *&pTransaction)
{
	_START(GET_TRANSACTION);

#ifdef _DEBUG_
	if (!pszTransactionName)
		_RET(PARAMETER_NULL | PARAMETER_1);

	if (0 == pszTransactionName[0])
		_RET(PARAMETER_EMPTY | PARAMETER_1);

	if (pTransaction)
		_RET(PARAMETER_NOT_NULL | PARAMETER_2);
#endif

	map_transaction::iterator pos = m_TransactionMap.find(pszTransactionName);

	if (m_TransactionMap.end() != pos)
	{
#ifdef _DEBUG_
		if (!pos->second)
			_RET(ELEMENT_NULL_IN_CONTAINER);
#endif

		pTransaction = (CTransaction *)pos->second;
	}
	else
	{
		_RET(NO_ELEMENT_IN_CONTAINER);
	}

	_RET(SUCCESS);
}

ret_ CTransactionManager::Register(const ch_1 *pszCategory,
								   const ch_1 *pszKey,
								   const CProcessor *pProcessor,
								   const bool_ bIsCovered)
{
	_START(REGITSTER_PROCESSOR);

#ifdef _DEBUG_
	if (!pszCategory)
		_RET(PARAMETER_NULL | PARAMETER_1);

	if (0 == category[0])
		_RET(PARAMETER_EMPTY | PARAMETER_1);

	if (!key)
		_RET(PARAMETER_NULL | PARAMETER_2);

	if (0 == key[0])
		_RET(PARAMETER_EMPTY | PARAMETER_2);

	if (!pProcessor)
		_RET(PARAMETER_NULL | PARAMETER_3);
#endif

	map_processor_category::iterator pos = m_CategoryMap.find(pszCategory);

	if (m_CategoryMap.end() != pos)
	{
#ifdef _DEBUG_
		if (!pos->second)
			_RET(ELEMENT_NULL_IN_CONTAINER);
#endif

		map_processor *pProcessorMap = pos->second;

		map_processor::iterator pos_ = pProcessorMap->find(pszKey);

		if (pProcessorMap->end() == pos_)
		{
			pProcessorMap->insert(
				map_processor::value_type(pszKey, pProcessor));
		}
		else
		{
			if (bIsCovered)
			{
				pProcessorMap->erase(pszKey);
				pProcessorMap->insert(
					map_processor::value_type(pszKey, pProcessor));
			}
#ifdef _DEBUG_
			else
			{
				if (!pos_->second)
					_RET(ELEMENT_NULL_IN_CONTAINER);
			}
#endif
		}
	}
	else
	{
		map_processor *pProcessorMap = new map_processor;

		pProcessorMap->insert(map_processor::value_type(pszKey, pProcessor));
		m_CategoryMap.insert(map_processor_category::value_type(pszCategory,
																pProcessorMap));
	}

	_RET(SUCCESS);
}

ret_ CTransactionManager::Unregister(const ch_1 *pszCategory, const ch_1 *pszKey)
{
	_START(UNREGISTER_PROCESSOR);

#ifdef _DEBUG_
	if (!category)
		_RET(PARAMETER_NULL | PARAMETER_1);

	if (0 == category[0])
		_RET(PARAMETER_EMPTY | PARAMETER_1);

	if (!key)
		_RET(PARAMETER_NULL | PARAMETER_2);

	if (0 == key[0])
		_RET(PARAMETER_EMPTY | PARAMETER_2);
#endif

	map_processor_category::iterator pos = m_CategoryMap.find(pszCategory);

	if (m_CategoryMap.end() != pos)
	{
#ifdef _DEBUG_
		if (!pos->second)
			_RET(ELEMENT_NULL_IN_CONTAINER);
#endif

		map_processor *pProcessorMap = pos->second;

		map_processor::iterator pos_ = pProcessorMap->find(pszKey);

		if (pProcessorMap->end() != pos_)
		{
#ifdef _DEBUG_
			if (!pos_->second)
				_RET(ELEMENT_NULL_IN_CONTAINER);
#endif
			pProcessorMap->erase(pszKey);

			if (0 == pProcessorMap->size())
			{
				_DEL(pProcessorMap);
				m_CategoryMap.erase(pszCategory);
			}
		}
#ifdef _DEBUG_
		else
		{
			_RET(NO_ELEMENT_IN_CONTAINER);
		}
#endif
	}
#ifdef _DEBUG_
	else
	{
		_RET(NO_ELEMENT_IN_CONTAINER);
	}
#endif

	_RET(SUCCESS);
}

ret_ CTransactionManager::Search(const ch_1 *pszCategory,
								 const ch_1 *pszKey,
								 CProcessor *&pProcessor)
{
	_START(SEARCH_PROCESSOR);

#ifdef _DEBUG_
	if (!category)
		_RET(PARAMETER_NULL | PARAMETER_1);

	if (0 == category[0])
		_RET(PARAMETER_EMPTY | PARAMETER_1);

	if (!key)
		_RET(PARAMETER_NULL | PARAMETER_2);

	if (0 == key[0])
		_RET(PARAMETER_EMPTY | PARAMETER_2);

	if (pProcessor)
		_RET(PARAMETER_NOT_NULL | PARAMETER_3);
#endif

	map_processor_category::iterator pos = m_CategoryMap.find(pszCategory);

	if (m_CategoryMap.end() != pos)
	{
#ifdef _DEBUG_
		if (!pos->second)
			_RET(ELEMENT_NULL_IN_CONTAINER);
#endif

		map_processor *pProcessorMap = pos->second;

		map_processor::iterator pos_ = pProcessorMap->find(pszKey);

		if (pProcessorMap->end() != pos_)
		{
#ifdef _DEBUG_
			if (!pos_->second)
				_RET(ELEMENT_NULL_IN_CONTAINER);
#endif

			pProcessor = (CProcessor *)pos_->second;

			_RET(SUCCESS);
		}
	}

	_RET(NO_ELEMENT_IN_CONTAINER);
}
