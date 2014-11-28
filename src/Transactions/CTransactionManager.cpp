#include "CTransactionManager.h"

CTransactionManager *CTransactionManager::_instance = null_v;

none_ CTransactionManager::stop() {
    for (MapTransaction::iterator pos1 = _transactionMap.begin();
         pos1 != _transactionMap.end(); pos1++) {
        assert(pos1->second);
        _DEL(pos1->second);
    }

    for (MapProcessorCategory::iterator pos2 = _categoryMap.begin();
         pos2 != _categoryMap.end(); pos2++) {
        assert(pos2->second);
        pos2->second->clear();
        _DEL(pos2->second);
    }

    _transactionMap.clear();
    _categoryMap.clear();
}

none_ CTransactionManager::addTransaction(const ch_1 *transactionName,
        const CProcessor &processor,
        const size_ size) {
    assert(transactionName && 0 != transactionName[0] || 0 <= size);

    assert(_transactionMap.end() == _transactionMap.find(transactionName));
    _transactionMap.insert(MapTransaction::value_type(transactionName,
            new CTransaction(&processor, size)));
}

CTransaction *CTransactionManager::getTransaction(const ch_1 *transactionName) {
    if (!transactionName || 0 == transactionName[0]) {
        return null_v;
    }

    MapTransaction::iterator pos = _transactionMap.find(transactionName);

    if (_transactionMap.end() != pos) {
        assert(pos->second);
        return pos->second;
    }

    return null_v;
}

none_ CTransactionManager::registerItem(const ch_1 *category,
        const ch_1 *key,
        const CProcessor &processor,
        const bool_ isCovered) {
    assert (category || 0 != category[0] || key || 0 != key[0]);

    MapProcessorCategory::iterator pos1 = _categoryMap.find(category);

    if (_categoryMap.end() != pos1) {
        assert(pos1->second);
        MapProcessor           *processorMap = pos1->second;
        MapProcessor::iterator pos2          = processorMap->find(key);

        if (processorMap->end() == pos2) {
            processorMap->insert(
                    MapProcessor::value_type(key, &processor));
        } else {
            assert(pos2->second);

            if (isCovered) {
                processorMap->erase(key);
                processorMap->insert(
                        MapProcessor::value_type(key, &processor));
            }
        }
    } else {
        MapProcessor *processorMap = new MapProcessor;

        processorMap->insert(MapProcessor::value_type(key, &processor));
        _categoryMap.insert(MapProcessorCategory::value_type(category,
                processorMap));
    }
}

none_ CTransactionManager::unregisterItem(const ch_1 *category, const ch_1 *key) {
    assert(category && 0 != category[0] && key && 0 != key[0]);

    MapProcessorCategory::iterator pos1 = _categoryMap.find(category);

    assert(_categoryMap.end() != pos1);
    assert(pos1->second);
    MapProcessor           *pProcessorMap = pos1->second;
    MapProcessor::iterator pos2           = pProcessorMap->find(key);

    assert(pProcessorMap->end() != pos2);
    assert(pos2->second);
    pProcessorMap->erase(key);

    if (0 == pProcessorMap->size()) {
        _DEL(pProcessorMap);
        _categoryMap.erase(category);
    }
}

CProcessor *CTransactionManager::searchItem(const ch_1 *category,
        const ch_1 *key) {
    assert(category && 0 != category[0] && key && 0 != key[0]);

    MapProcessorCategory::iterator pos1 = _categoryMap.find(category);

    assert(_categoryMap.end() != pos1);
    assert(pos1->second);

    MapProcessor           *pProcessorMap = pos1->second;
    MapProcessor::iterator pos2           = pProcessorMap->find(key);

    assert(pProcessorMap->end() != pos2);
    assert(pos2->second);
    return pos2->second;
}
