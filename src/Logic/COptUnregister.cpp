#include "COptUnregister.h"

none_ COptUnregister::work(const TMessageUnit *tmu) {
    v_ *category = _category->value(tmu);
    v_ *key      = _key->value(tmu);

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

    v_ *object = CRegister::instance()->searchItem((const ch_1 *) *category,
            (const ch_1 *) *key);

    if (null_v != object) {
        if (OBJ == object->getType()) {
            obj_       obj        = (obj_) (*object);
            CProcessor *processor = (CProcessor *) obj;

            if (!processor) {
                assert(0);
                // TODO do something to tell outside
                return;
            }

            if (0 != processor->Unregister((const ch_1 *) *category,
                    (const ch_1 *) *key)) {
                assert(0);
                // TODO do something to tell outside
            }
        } else {
            if (0 !=
                    CRegister::instance()->unregisterItem(
                            (const ch_1 *) *category, (const ch_1 *) *key)) {
                assert(0);
                // TODO do something to tell outside
            }
        }
    } else {
        assert(0);
        // TODO do something to tell outside
    }
}
