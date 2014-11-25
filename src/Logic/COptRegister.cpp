#include "COptRegister.h"

none_ COptRegister::work(const TMessageUnit *tmu) {
    v_ *category = _category->value(tmu);
    v_ *key = _key->value(tmu);

    if (!category || !key) {
        assert(0);
        // TODO do something to tell outside
        return;
    }

    if (STR != category->getType() || STR != key->getType()) {
        assert(0);
        // TODO do something to tell outside
        return;
    }

    v_ *obj = _object->value(tmu);

    if (obj) {
        if (OBJ != obj->getType()) {
            obj_ p = (obj_) (*obj);
            CProcessor *processor = (CProcessor *) p;

            if (!processor) {
                assert(0);
                // TODO do something to tell outside
                return;
            }

            if (0 != processor->registerItem(
                    (const ch_1 *) *category,
                    (const ch_1 *) *key, _isCovered)) {
                assert(0);
                // TODO do something to tell outside
            }
        } else {
            if (CRegister::instance()->registerItem(
                    (const ch_1 *) *category,
                    (const ch_1 *) *key,
                    obj,
                    _isCovered)) {
                assert(0);
                // TODO do something to tell outside
            }
        }
    } else {
        CProcessor *processor = (CProcessor *) getContainer();

        if (!processor) {
            assert(0);
            // TODO do something to tell outside
            return;
        }

        if (0 != processor->registerItem(
                (const ch_1 *) *category,
                (const ch_1 *) *key,
                _isCovered)) {
            assert(0);
            // TODO do something to tell outside
        }
    }
}
