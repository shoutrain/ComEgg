#include "CVarGroupDefined.h"

CVariable *CVarGroupDefined::clone() const {
    return (CVariable *) new CVarGroupDefined(_groupName,
            _subName,
            _indexName);
}

none_ CVarGroupDefined::init(const CData *data) {
    _groupData = null_v;
    _field = (CField *) (obj_) *data->value(_groupName,
            _subName,
            _groupData);
    _index = data->value(_indexName);

    const CField *parentField = _field->getGroupField();

    if (parentField) {
        _size = data->value(parentField->getSizeName());
    } else {
        _size = data->value(_field->getSizeName());
    }
}

v_ *CVarGroupDefined::value(const TMessageUnit *tmu) {
    _value.clear();

    if (!_groupData || !_groupData->size || !_groupData->data) {
        v_ tmp;

        _value = tmp;

        return &_value;
    }

    size_ index = 0;
    size_ offset = 0;

    if (_index) {
        index = (size_) *_index;
    }

    if (FIELD_GROUP_STYLE == (GET_FIELD_STYLE & _field->type())) {
        offset = _field->offset((size_) *_size,
                _groupData->size,
                index);
    } else {
        offset = _field->offset(_groupData->data,
                _groupData->size,
                index);
    }

    switch (_field->type()) {
        case FIELD_B_1_TYPE:
            _value = (b_1 *) (_groupData->data + offset);
            break;
        case FIELD_UB_1_TYPE:
            _value = (ub_1 *) (_groupData->data + offset);
            break;
        case FIELD_B_2_TYPE:
            _value = (b_2 *) (_groupData->data + offset);
            break;
        case FIELD_UB_2_TYPE:
            _value = (ub_2 *) (_groupData->data + offset);
            break;
        case FIELD_B_4_TYPE:
            _value = (b_4 *) (_groupData->data + offset);
            break;
        case FIELD_UB_4_TYPE:
            _value = (ub_4 *) (_groupData->data + offset);
            break;
        case FIELD_B_8_TYPE:
            _value = (b_8 *) (_groupData->data + offset);
            break;
        case FIELD_UB_8_TYPE:
            _value = (ub_8 *) (_groupData->data + offset);
            break;
        case FIELD_FB_4_TYPE:
            _value = (fb_4 *) (_groupData->data + offset);
            break;
        case FIELD_FB_8_TYPE:
            _value = (fb_8 *) (_groupData->data + offset);
            break;
        case FIELD_STR_TYPE: {
            v_ tmp((const ch_1 *) (_groupData->data + offset),
                    _field->size());

            _value = tmp;
        }
            break;
        case FIELD_GROUP_TYPE: {
            if (index) {
                v_ tmp((obj_ *) &(_groupData->data),
                        offset,
                        _field->getUnitSize());

                _value = tmp;
            }
            else {
                v_ tmp((obj_ *) &(_groupData->data), 0, _groupData->size);

                _value = tmp;
            }
        }
            break;
        default:
            assert(0);
            logError("Wrong type in CVarGroupDefined::value");
            return null_v;
    }

    return &_value;
}

v_ *CVarGroupDefined::value(obj_ &parameter) {
    if (parameter || !_groupData || !_field) {
        assert(0);
        logError("Wrong type in CVarGroupDefined::value");
        return null_v;
    }

    parameter = (obj_) _field;

    v_ tmp((obj_) _groupData);

    _value.clear();
    _value = tmp;

    return &_value;
}
