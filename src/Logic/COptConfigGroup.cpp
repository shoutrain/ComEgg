#include "COptConfigGroup.h"

#include "../Data/CVarGroupDefined.h"

none_ COptConfigGroup::work(const TMessageUnit *tmu) {
    CField *field = null_v;
    v_ *groupData = null_v;
    TFieldGroup *fieldGroup = null_v;
    v_ *size = null_v;

    groupData = _group->value((obj_ &) field);
    fieldGroup = (TFieldGroup *) (obj_) *groupData;
    size = _size->value(tmu);

    if (fieldGroup->size && fieldGroup->data) {
        _DEL_ARR(fieldGroup->data);
        fieldGroup->size = 0;
    }

    fieldGroup->size = field->getUnitSize() * ((size_) *size);
    fieldGroup->data = new ub_1[fieldGroup->size];
    memset(fieldGroup->data, 0, fieldGroup->size);
}



