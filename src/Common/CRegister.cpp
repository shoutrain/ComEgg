#include "CRegister.h"

CRegister *CRegister::_instance = null_v;

none_ CRegister::stop() {
    for (MapCategory::iterator pos1 = _categoryMap.begin();
         pos1 != _categoryMap.end(); pos1++) {
        assert(pos1->second);

        for (MapVariable::iterator pos2 = pos1->second->begin();
             pos2 != pos1->second->end(); pos2++) {
            assert(pos2->second);
            _DEL(pos2->second);
        }

        pos1->second->clear();
        _DEL(pos1->second);
    }

    _categoryMap.clear();
}

v_ *CRegister::searchItem(const ch_1 *category, const ch_1 *key) {
    assert(category && 0 != category[0]);
    assert(key && 0 != key[0]);

    MapCategory::iterator pos1 = _categoryMap.find(category);

    if (_categoryMap.end() != pos1) {
        assert(pos1->second);
        MapVariable::iterator pos2 = pos1->second->find(key);

        if (pos1->second->end() != pos2) {
            assert(pos2->second);
            return pos2->second;
        }
    }

    return null_v;
}

b_4 CRegister::registerItem(const ch_1 *category,
        const ch_1 *key,
        const v_ *variable,
        const bool_ isCovered) {
    assert(category && 0 != category[0]);
    assert(key && 0 != key[0]);
    assert(variable);

    MapCategory::iterator pos1 = _categoryMap.find(category);

    if (_categoryMap.end() != pos1) {
        assert(pos1->second);
        MapVariable::iterator pos2 = pos1->second->find(key);

        if (pos1->second->end() != pos2) {
            assert(pos2->second);

            if (isCovered) {
                _DEL(pos2->second);
                pos1->second->erase(key);

                v_ *newVariable = new v_(*variable);

                pos1->second->insert(
                        MapVariable::value_type(key, newVariable));
            } else {
                return 1;
            }
        } else {
            v_ *newVariable = new v_(*variable);

            pos1->second->insert(
                    MapVariable::value_type(key, newVariable));
        }
    } else {
        MapVariable *variableMap = new MapVariable;
        v_          *newVariable = new v_(*variable);

        variableMap->insert(
                MapVariable::value_type(key, newVariable));
        _categoryMap.insert(
                MapCategory::value_type(category, variableMap));
    }

    return 0;
}

none_ CRegister::unregisterItem(const ch_1 *category, const ch_1 *key) {
    assert(category && 0 != category[0]);
    assert(key && 0 != key[0]);

    MapCategory::iterator pos1 = _categoryMap.find(category);

    if (_categoryMap.end() != pos1) {
        assert(pos1->second);

        MapVariable::iterator pos2 = pos1->second->find(key);

        if (pos1->second->end() != pos2) {
            assert(pos2->second);
            _DEL(pos2->second);
            pos1->second->erase(key);

            if (0 == pos1->second->size()) {
                _DEL(pos1->second);
                _categoryMap.erase(category);
            }
        }
    }
}
