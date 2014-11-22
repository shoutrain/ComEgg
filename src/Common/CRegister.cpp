#include "CRegister.h"

CRegister *CRegister::_instance = null_v;

b_4 CRegister::stop() {
    for (mapCategory::iterator pos = _categoryMap.begin();
         pos != _categoryMap.end(); pos++) {
        if (!pos->second) {
            assert(0);
            return -1;
        }

        for (mapVariable::iterator pos_ = pos->second->begin();
             pos_ != pos->second->end(); pos_++) {
            if (!pos_->second) {
                assert(0);
                return -2;
            }

            _DEL(pos_->second);
        }

        pos->second->clear();
        _DEL(pos->second);
    }

    _categoryMap.clear();

    return 0;
}

b_4 CRegister::registerItem(const ch_1 *category,
        const ch_1 *key,
        const v_ *variable,
        const bool_ isCovered) {
    if (!category || 0 == category[0] || !key || 0 == key[0] || !variable) {
        assert(0);
        return -1;
    }

    mapCategory::iterator pos = _categoryMap.find(category);

    if (_categoryMap.end() != pos) {
        if (!pos->second) {
            assert(0);
            return -2;
        }

        mapVariable::iterator pos_ = pos->second->find(key);

        if (pos->second->end() != pos_) {
            if (!pos_->second) {
                return -3;
            }

            if (isCovered) {
                _DEL(pos_->second);
                pos->second->erase(key);

                v_ *newVariable = new v_(*variable);

                pos->second->insert(
                        mapVariable::value_type(key, newVariable));
            }
        } else {
            v_ *newVariable = new v_(*variable);

            pos->second->insert(
                    mapVariable::value_type(key, newVariable));
        }
    } else {
        mapVariable *varialbeMap = new mapVariable;
        v_ *pNewVariable = new v_(*variable);

        varialbeMap->insert(
                mapVariable::value_type(key, pNewVariable));
        _categoryMap.insert(
                mapCategory::value_type(category, varialbeMap));
    }

    return 0;
}

b_4 CRegister::unregisterItem(const ch_1 *category, const ch_1 *key) {
    if (!category || 0 == category[0] || !key || 0 == key[0]) {
        assert(0);
        return -1;
    }

    mapCategory::iterator pos = _categoryMap.find(category);

    if (_categoryMap.end() != pos) {
        if (!pos->second) {
            assert(0);
            return -2;
        }

        mapVariable::iterator pos_ = pos->second->find(key);

        if (pos->second->end() != pos_) {
            if (!pos_->second) {
                assert(0);
                return -3;
            }

            _DEL(pos_->second);
            pos->second->erase(key);

            if (0 == pos->second->size()) {
                _DEL(pos->second);
                _categoryMap.erase(category);
            }
        }
    }

    return 0;
}

v_ *CRegister::searchItem(const ch_1 *category, const ch_1 *key) {
    if (!category || 0 == category[0] || !key || 0 == key[0]) {
        assert(0);
        return null_v;
    }

    mapCategory::iterator pos = _categoryMap.find(category);

    if (_categoryMap.end() != pos) {
        if (!pos->second) {
            assert(0);
            return null_v;
        }

        mapVariable::iterator pos_ = pos->second->find(key);

        if (pos->second->end() != pos_) {
            if (!pos_->second) {
                assert(0);
                return null_v;
            }

            return pos_->second;
        }
    }

    return null_v;
}
