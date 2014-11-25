#include "COptSearch.h"

none_ COptSearch::work(const TMessageUnit *tmu) {
    v_ *category = m_pCategory->value(tmu);
    v_ *key = m_pKey->value(tmu);
    v_ *obj = m_pObject->value(tmu);

    if (!category || !key || !obj) {
        assert(0);
        // TODO do something to tell outsider
        return;
    }

    if (STR != category->getType() || STR != key->getType()) {
        assert(0);
        // TODO do something to tell outsider
        return;
    }

    v_ *object = CRegister::instance()->searchItem(
            (const ch_1 *) *category,
            (const ch_1 *) *key);

    if (null_v != object) {
        *obj = *object;
    }
}
