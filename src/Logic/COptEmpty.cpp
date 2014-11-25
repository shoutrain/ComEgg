#include "COptEmpty.h"

#include "../Data/CVarGroupDefined.h"

none_ COptEmpty::work(const TMessageUnit *tmu) {
    CField *field = null_v;
    v_ *p = _variable->value((obj_ &) field);

    if (p) {
        TFieldGroup *fieldGroup = (TFieldGroup *) (obj_) *p;

        if (fieldGroup->size && fieldGroup->data) {
            _DEL_ARR(fieldGroup->data);
            fieldGroup->size = 0;
        }
    }

    p = _variable->value(tmu);
    p->empty();
}



