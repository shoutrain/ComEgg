#include "COptUnitaryCalculate.h"

none_ COptUnitaryCalculate::work(const TMessageUnit *tmu) {
    switch (_opt) {
        case UC_EQL:
            (*_resultVariable->value(tmu)) =
                    (*_rightVariable->value(tmu));
            return;
        case UC_NEG:
            (*_resultVariable->value(tmu)) =
                    -(*_rightVariable->value(tmu));
            return;
        case UC_OBV:
            (*_resultVariable->value(tmu)) =
                    ~(*_rightVariable->value(tmu));
            return;
        case UC_NOT:
            (*_resultVariable->value(tmu)) =
                    v_(!(*_rightVariable->value(tmu)));
            return;
        default:
            assert(0);
            // TODO do something to tell outside
    }
}
