#ifndef _C_TRANSACTION_MANAGER_H_
#define _C_TRANSACTION_MANAGER_H_

#include "../Common/CResource.h"
#include "CTransaction.h"

#include <string>
#include <map>

using namespace std;

typedef map<string, const CTransaction *> MapTransaction;
typedef map<string, const CProcessor *>   MapProcessor;
typedef map<string, MapProcessor *>       MapProcessorCategory;

class CTransactionManager {
public:
    static CTransactionManager *instance() {
        if (_instance) {
            return _instance;
        }

        _instance = new CTransactionManager;

        return _instance;
    }

    static none_ destroy() {
        _DEL(_instance);
    }

    CData &data() {
        return _data;
    }

    none_ addTransaction(const ch_1 *transactionName,
            const CProcessor &processor,
            const size_ size);

    CTransaction *getTransaction(const ch_1 *transactionName);

    bool_ isTransactionReady(const ch_1 *transactionName) {
        if (!transactionName) {
            return false_v;
        }

        if (_transactionMap.end() != _transactionMap.find(transactionName)) {
            return true_v;
        }

        return false_v;
    }

protected:
    none_ stop();

private:
    friend class CProcessor;

    // Just CProcessor can use following three methods.
    none_ registerItem(const ch_1 *category, const ch_1 *key,
            const CProcessor &processor,
            const bool_ isCovered = false_v);

    none_ unregisterItem(const ch_1 *category, const ch_1 *key);

    CProcessor *searchItem(const ch_1 *category, const ch_1 *key);

    CTransactionManager() {
    }

    CTransactionManager(const CTransactionManager &);

    const CTransactionManager &operator=(const CTransactionManager &);

    virtual ~CTransactionManager() {
        stop();
    }

    static CTransactionManager *_instance;

    CData                _data;
    MapTransaction       _transactionMap;
    MapProcessorCategory _categoryMap;
};

#endif // _C_TRANSACTION_MANAGER_H_
