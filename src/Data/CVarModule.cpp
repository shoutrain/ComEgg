#include "CVarModule.h"

CVariable *CVarModule::clone() const {
    return (CVariable *) new CVarModule(field);
}

void CVarModule::init(const CData *data) {
}

v_ *CVarModule::value(const TMessageUnit *tmu) {
    size_ nOffset = field->offset(tmu->message,
            tmu->size);

    _value.clear();

    switch (field->type()) {
        case FIELD_B_1_TYPE:
            _value = (b_1 *) (tmu->message + nOffset);
            break;
        case FIELD_UB_1_TYPE:
            _value = (ub_1 *) (tmu->message + nOffset);
            break;
        case FIELD_B_2_TYPE:
            _value = (b_2 *) (tmu->message + nOffset);
            break;
        case FIELD_UB_2_TYPE:
            _value = (ub_2 *) (tmu->message + nOffset);
            break;
        case FIELD_B_4_TYPE:
            _value = (b_4 *) (tmu->message + nOffset);
            break;
        case FIELD_UB_4_TYPE:
            _value = (ub_4 *) (tmu->message + nOffset);
            break;
        case FIELD_B_8_TYPE:
            _value = (b_8 *) (tmu->message + nOffset);
            break;
        case FIELD_UB_8_TYPE:
            _value = (ub_8 *) (tmu->message + nOffset);
            break;
        case FIELD_FB_4_TYPE:
            _value = (fb_4 *) (tmu->message + nOffset);
            break;
        case FIELD_FB_8_TYPE:
            _value = (fb_8 *) (tmu->message + nOffset);
            break;
        case FIELD_STR_TYPE: {
            v_ tmp((const ch_1 *) (tmu->message + nOffset), field->size());

            _value = tmp;
        }
            break;
        case FIELD_GROUP_TYPE: {
            v_ tmp((obj_ *) &tmu->message,
                    nOffset,
                    field->size(tmu->message, tmu->size));

            _value = tmp;
        }
            break;
        default:
            assert(0);
            logError("Wrong type in CVarModule::value");
            return null_v;
    }

    return &_value;
}
