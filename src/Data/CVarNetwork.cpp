#include "CVarNetwork.h"

CVariable *CVarNetwork::clone() const {
    return (CVariable *) new CVarNetwork(_field, _indexName);
}

none_ CVarNetwork::init(const CData *data) {
    _index = data->value(_indexName);
}

v_ *CVarNetwork::value(const TMessageUnit *tmu) {
    size_ index = 0;

    if (_index) {
        index = (size_) *_index;
    }

    size_ offset = _field->offset(tmu->message,
            tmu->size,
            index);

    _value.clear();

    switch (_field->type()) {
        case FIELD_B_1_TYPE:
            _value = (b_1 *) (tmu->message + offset);
            break;
        case FIELD_UB_1_TYPE:
            _value = (ub_1 *) (tmu->message + offset);
            break;
        case FIELD_B_2_TYPE:
            _value = (b_2 *) (tmu->message + offset);
            break;
        case FIELD_UB_2_TYPE:
            _value = (ub_2 *) (tmu->message + offset);
            break;
        case FIELD_B_4_TYPE:
            _value = (b_4 *) (tmu->message + offset);
            break;
        case FIELD_UB_4_TYPE:
            _value = (ub_4 *) (tmu->message + offset);
            break;
        case FIELD_B_8_TYPE:
            _value = (b_8 *) (tmu->message + offset);
            break;
        case FIELD_UB_8_TYPE:
            _value = (ub_8 *) (tmu->message + offset);
            break;
        case FIELD_FB_4_TYPE:
            _value = (fb_4 *) (tmu->message + offset);
            break;
        case FIELD_FB_8_TYPE:
            _value = (fb_8 *) (tmu->message + offset);
            break;
        case FIELD_STR_TYPE: {
            v_ tmp((const ch_1 *) (tmu->message + offset),
                    _field->size(tmu->message, tmu->size));

            _value = tmp;
        }
            break;
        case FIELD_GROUP_TYPE: {
            if (index) {
                v_ tmp((obj_ *) &(tmu->message),
                        offset,
                        _field->getUnitSize());

                _value = tmp;
            }
            else {
                v_ tmp((obj_ *) &(tmu->message),
                        offset,
                        _field->size(tmu->message, tmu->size));

                _value = tmp;
            }
        }
            break;
        default:
            assert(0);
            log_error("Wrong type in CVarNetwork::value");
            return null_v;
    }

    return &_value;
}
