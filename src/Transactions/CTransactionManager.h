#ifndef CTRANSACTION_MANAGER_H
#define CTRANSACTION_MANAGER_H

#include "../Tools/CResource.h"
#include "CTransaction.h"

#include <string>
#include <map>

using namespace std;

typedef map<string, const CTransaction *>	map_transaction;

typedef map<string, const CProcessor *>		map_processor;
typedef map<string, map_processor *>		map_processor_category;

class CTransactionManager: public CBaseClass
{
public:
	static CTransactionManager *Instance()
	{
		if (m_pInstance)
			return m_pInstance;

		m_pInstance = new CTransactionManager;

		return m_pInstance;
	}

    static none_ Destory()
	{
		_DEL(m_pInstance);
	}

	CData &Data()
	{
		return m_Data;
	}

	ret_ AddTransaction(const ch_1 *pszTransactionName, 
						const CProcessor &Processor, 
						const size_ nSize);
	ret_ GetTransaction(const ch_1 *pszTransactionName, 
						CTransaction *&pTransaction);

	bool_ IsTransactionReady(const ch_1 *pszTransactionName)
	{
		if (!pszTransactionName)
			return false_v;

		if (m_TransactionMap.end() != m_TransactionMap.find(pszTransactionName))
			return true_v;

		return false_v;
	}

protected:
	ret_ Stop();

private:
	friend class CProcessor;

	// Just CProcessor can use following three methods.
	ret_ Register(const ch_1 *pszCategory, const ch_1 *pszKey, const CProcessor *pProcessor,
				  const bool_ bIsCovered = false_v);
	ret_ Unregister(const ch_1 *pszCategory, const ch_1 *pszKey);
	ret_ Search(const ch_1 *pszCategory, const ch_1 *pszKey, CProcessor *&pProcessor);

	CTransactionManager(): CBaseClass(CTRANSACTIONMANAGER) {}

	CTransactionManager(const CTransactionManager &);
	const CTransactionManager &operator =(const CTransactionManager &);

	virtual ~CTransactionManager()
	{
		Stop();
	}

	static CTransactionManager	*m_pInstance;

	CData m_Data;
	map_transaction m_TransactionMap;
	map_processor_category m_CategoryMap;
};

#endif // CTRANSACTION_MANAGER_H
