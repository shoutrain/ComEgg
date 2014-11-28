#include "CData.h"

CData::CData(const CData &data) {
    for (MapVariable::const_iterator pos = data._variableMap.begin();
         pos != data._variableMap.end(); pos++) {
        v_ *p = new v_(*(pos->second));

        _variableMap.insert(MapVariable::value_type(pos->first, p));
    }

    for (MapData::const_iterator pos_ = data._dataMap.begin();
         pos_ != data._dataMap.end(); pos_++) {
        TFieldGroup *newData = new TFieldGroup;

        memset(newData, 0, sizeof(TFieldGroup));
        _dataMap.insert(MapData::value_type(pos_->first, newData));

        if (pos_->second->size && pos_->second->data) {
            newData->size = pos_->second->size;
            newData->data = new ub_1[pos_->second->size];
        }
    }
}

const CData &CData::operator=(const CData &data) {
    if (&data != this) {
        clear();

        for (MapVariable::const_iterator pos = data._variableMap.begin();
             pos != data._variableMap.end(); pos++) {
            v_ *p = new v_(*(pos->second));

            _variableMap.insert(MapVariable::value_type(pos->first, p));
        }

        for (MapData::const_iterator pos_ = data._dataMap.begin();
             pos_ != data._dataMap.end(); pos_++) {
            TFieldGroup *newData = new TFieldGroup;

            memset(newData, 0, sizeof(TFieldGroup));
            _dataMap.insert(MapData::value_type(pos_->first, newData));

            if (pos_->second->size && pos_->second->data) {
                newData->size = pos_->second->size;
                newData->data = new ub_1[pos_->second->size];
            }
        }
    }

    return *this;
}

bool_ CData::define(const ch_1 *name, evt_ type) {
    if (_variableMap.end() != _variableMap.find(name)) {
        return false_v;
    }

    v_ *var = null_v;

    switch (type) {
        case B_1: {
            b_1 v = 0;
            var = new v_(v);
        }
            break;
        case UB_1: {
            ub_1 v = 0;
            var = new v_(v);
        }
            break;
        case B_2: {
            b_2 v = 0;
            var = new v_(v);
        }
            break;
        case UB_2: {
            ub_2 v = 0;
            var = new v_(v);
        }
            break;
        case B_4: {
            b_4 v = 0;
            var = new v_(v);
        }
            break;
        case UB_4: {
            ub_4 v = 0;
            var = new v_(v);
        }
            break;
        case B_8: {
            b_8 v = 0;
            var = new v_(v);
        }
            break;
        case UB_8: {
            ub_8 v = 0;
            var = new v_(v);
        }
            break;
        case FB_4: {
            fb_4 v = 0;
            var = new v_(v);
        }
            break;
        case FB_8: {
            fb_8 v = 0;
            var = new v_(v);
        }
            break;
        case STR:
            var = new v_("", 0);
            break;
        case OBJ: {
            obj_ v = null_v;
            var = new v_(v);
        }
            break;
        default:
            return false_v;
    }

    _variableMap.insert(MapVariable::value_type(name, var));

    return true_v;
}

bool_ CData::define(const ch_1 *name, evt_ type, b_4 data) {
    if (_variableMap.end() != _variableMap.find(name)) {
        return false_v;
    }

    v_ *var = null_v;

    switch (type) {
        case B_1:
            var = new v_((b_1) data);
            break;
        case UB_1:
            var = new v_((ub_1) data);
            break;
        case B_2:
            var = new v_((b_2) data);
            break;
        case UB_2:
            var = new v_((ub_2) data);
            break;
        case B_4:
            var = new v_((b_4) data);
            break;
        case UB_4:
            var = new v_((ub_4) data);
            break;
        default:
            return false_v;
    }

    _variableMap.insert(MapVariable::value_type(name, var));

    return true_v;
}

bool_ CData::define(const ch_1 *name, b_8 data) {
    if (_variableMap.end() != _variableMap.find(name)) {
        return false_v;
    }

    v_ *var = new v_(data);

    _variableMap.insert(MapVariable::value_type(name, var));

    return true_v;
}

bool_ CData::define(const ch_1 *name, ub_8 data) {
    if (_variableMap.end() != _variableMap.find(name)) {
        return false_v;
    }

    v_ *var = new v_(data);

    _variableMap.insert(MapVariable::value_type(name, var));

    return true_v;
}

bool_ CData::define(const ch_1 *name, fb_4 data) {
    if (_variableMap.end() != _variableMap.find(name)) {
        return false_v;
    }

    v_ *var = new v_(data);

    _variableMap.insert(MapVariable::value_type(name, var));

    return true_v;
}

bool_ CData::define(const ch_1 *name, fb_8 data) {
    if (_variableMap.end() != _variableMap.find(name)) {
        return false_v;
    }

    v_ *var = new v_(data);

    _variableMap.insert(MapVariable::value_type(name, var));

    return true_v;
}

bool_ CData::define(const ch_1 *name, const ch_1 *value) {
    if (_variableMap.end() != _variableMap.find(name)) {
        return false_v;
    }

    v_ *var = new v_((const ch_1 *) value, 0);

    _variableMap.insert(MapVariable::value_type(name, var));

    return true_v;
}

bool_ CData::define(const ch_1 *name, obj_ object) {
    if (_variableMap.end() != _variableMap.find(name)) {
        return false_v;
    }

    v_ *var = new v_(object);

    _variableMap.insert(MapVariable::value_type(name, var));

    return true_v;
}

bool_ CData::define(const CFieldGroupDefined *fieldGroup) {
    if (!fieldGroup) {
        return false_v;
    }

    v_ *size = value(fieldGroup->getSizeName());

    if (!size) {
        return false_v;
    }

    if (_variableMap.end() != _variableMap.find(fieldGroup->name())) {
        return false_v;
    }

    _variableMap.insert(MapVariable::value_type(fieldGroup->name(),
            new v_((obj_) fieldGroup)));

    TFieldGroup *groupData = new TFieldGroup;

    memset(groupData, 0, sizeof(TFieldGroup));
    _dataMap.insert(MapData::value_type(fieldGroup->name(),
            groupData));

    size_ n = (size_) *size;

    if (n) {
        groupData->size = n;
        groupData->data = new ub_1[groupData->size];
        memset(groupData->data, 0, groupData->size);
    }

    const CField *field = fieldGroup->getSubField();

    while (field) {
        ch_1 name[VARIABLE_NAME_LENGTH * 2] = {0};

        sprintf(name, "%s.%s", fieldGroup->name(), field->name());

        if (_variableMap.end() != _variableMap.find(name)) {
            return false_v;
        }

        _variableMap.insert(MapVariable::value_type(name,
                new v_((obj_) field)));
        field = field->getNextField();
    }

    return true_v;
}

v_ *CData::value(const ch_1 *name) const {
    MapVariable::const_iterator pos = _variableMap.find(name);

    if (_variableMap.end() != pos) {
        return pos->second;
    } else if (_parent) {
        return _parent->value(name);
    } else {
        return null_v;
    }
}

v_ *CData::value(const ch_1 *groupName,
        const ch_1 *subName,
        TFieldGroup *&data) const {
    if (!groupName || 0 == groupName[0] || data) {
        return null_v;
    }

    ch_1 name[VARIABLE_NAME_LENGTH * 2] = {0};

    if (!subName || 0 == subName[0]) {
        strncpy(name, groupName, VARIABLE_NAME_LENGTH);
    } else {
        sprintf(name, "%s.%s", groupName, subName);
    }

    MapVariable::const_iterator pos = _variableMap.find(name);

    if (_variableMap.end() != pos) {
        MapData::const_iterator pos_ = _dataMap.find(groupName);

        if (_dataMap.end() != pos_) {
            data = pos_->second;

            return pos->second;
        } else {
            return null_v;
        }
    } else if (_parent) {
        return _parent->value(groupName, subName, data);
    } else {
        return null_v;
    }
}

none_ CData::clear() {
    for (MapVariable::iterator pos = _variableMap.begin();
         pos != _variableMap.end(); pos++) {
        _DEL(pos->second);
    }

    for (MapData::iterator pos_ = _dataMap.begin();
         pos_ != _dataMap.end(); pos_++) {
        if (pos_->second->size && pos_->second->data) {
            _DEL_ARR(pos_->second->data);
            pos_->second->size = 0;
        }

        _DEL(pos_->second);
    }

    _variableMap.clear();
    _dataMap.clear();
}
