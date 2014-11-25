#include "COptDualityCalculate.h"

none_ COptDualityCalculate::work(const TMessageUnit *tmu) {
    switch (_opt) {
        case EC_ADD:
            (*_resultVariable->value(tmu))
                    = (*_leftVariable->value(tmu))
                    + (*_rightVariable->value(tmu));
            return;
        case EC_SUB:
            (*_resultVariable->value(tmu))
                    = (*_leftVariable->value(tmu))
                    - (*_rightVariable->value(tmu));
            return;
        case EC_MUL:
            (*_resultVariable->value(tmu))
                    = (*_leftVariable->value(tmu))
                    * (*_rightVariable->value(tmu));
            return;
        case EC_DIV:
            (*_resultVariable->value(tmu))
                    = (*_leftVariable->value(tmu))
                    / (*_rightVariable->value(tmu));
            return;
        case EC_MOD:
            (*_resultVariable->value(tmu))
                    = (*_leftVariable->value(tmu))
                    % (*_rightVariable->value(tmu));
            return;
        case EC_AND:
            (*_resultVariable->value(tmu))
                    = (*_leftVariable->value(tmu))
                    & (*_rightVariable->value(tmu));
            return;
        case EC_OR:
            (*_resultVariable->value(tmu))
                    = (*_leftVariable->value(tmu))
                    | (*_rightVariable->value(tmu));
            return;
        case EC_XOR:
            (*_resultVariable->value(tmu))
                    = (*_leftVariable->value(tmu))
                    ^ (*_rightVariable->value(tmu));
            return;
        default:
            assert(0);
            // TODO do something let outside know
    }
}
