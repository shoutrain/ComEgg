#include "CInterfaceInfo.h"

#include "../Data/CFieldNumber.h"
#include "../Data/CFieldString.h"
#include "../Data/CFieldGroup.h"

none_ CInterfaceInfo::stop() {
    for (mapField::iterator pos1 = _inFieldMap.begin();
         pos1 != _inFieldMap.end();
         pos1++) {
        assert(pos1->second);
        _DEL(pos1->second);
    }

    for (mapField::iterator pos2 = _outFieldMap.begin();
         pos2 != _outFieldMap.end();
         pos2++) {
        assert(pos2->second);
        _DEL(pos2->second);
    }

    _inFieldMap.clear();
    _outFieldMap.clear();
    _inField = null_v;
    _inCurField = null_v;
    _outField = null_v;
    _outCurField = null_v;
}

b_4 CInterfaceInfo::addInField(const TField &field, const ch_1 *groupName) {
    if (!field.name || 0 == field.name[0]) {
        assert(0);
        return 1;
    }

    CField *localField = null_v;
    CField *groupField = null_v;
    ch_1 name[VARIABLE_NAME_LENGTH * 2] = {0};

    if (groupName && 0 != groupName[0]) {
        groupField = getInField(groupName);

        if (null_v == groupField) {
            assert(0);
            return 2;
        }

        sprintf(name, "%s.%s", groupName, field.name);
    } else {
        sprintf(name, "%s", field.name);
    }

    // Check if there is a localField which name is same as the localField's name,
    // in the map.
    if (_inFieldMap.end() != _inFieldMap.find(name)) {
        assert(0);
        return 3;
    }

    switch (field.style) {
        case FIELD_NORMAL_STYLE: {
            EFieldType type;

            if (1 == field.length && field.isSigned) {
                type = FIELD_B_1_TYPE;
            } else if (1 == field.length && !field.isSigned) {
                type = FIELD_UB_1_TYPE;
            } else if (2 == field.length && field.isSigned) {
                type = FIELD_B_2_TYPE;
            } else if (2 == field.length && !field.isSigned) {
                type = FIELD_UB_2_TYPE;
            } else if (4 == field.length && field.isSigned) {
                type = FIELD_B_4_TYPE;
            } else if (4 == field.length && !field.isSigned) {
                type = FIELD_UB_4_TYPE;
            } else if (8 == field.length && field.isSigned) {
                type = FIELD_B_8_TYPE;
            } else if (8 == field.length && !field.isSigned) {
                type = FIELD_UB_8_TYPE;
            } else {
                assert(0);
                return 4;
            }

            if (0 != field.size || 0 != field.sizeName[0]) {
                assert(0);
                return 5;
            }

            localField = new CFieldNumber(name, type, groupField);
        }
            break;
        case FIELD_FLOAT_STYLE: {
            EFieldType type;

            if (4 == field.length) {
                type = FIELD_FB_4_TYPE;
            } else if (8 == field.length) {
                type = FIELD_FB_8_TYPE;
            } else {
                assert(0);
                return 6;
            }

            if (0 != field.size || 0 != field.sizeName[0]) {
                assert(0);
                return 7;
            }

            localField = new CFieldNumber(name, type, groupField);
        }
            break;
        case FIELD_STRING_STYLE: {
            if (0 == field.size || 0 != field.sizeName[0]) {
                assert(0);
                return 8;
            }

            localField = new CFieldString(name, field.size, groupField);
        }
            break;
        case FIELD_GROUP_STYLE: {
            if (0 != field.size || 0 == field.sizeName[0]) {
                assert(0);
                return 9;
            }

            CField *sizeField = getInField(field.sizeName);
            assert(sizeField);

            localField = new CFieldGroup(name, sizeField);
        }
            break;
        default:
            assert(0);
            return 10;
    }

    if (!groupField) {
        if (_inCurField) {
            _inCurField->attach(localField);
        } else {
            _inField = localField;
        }

        _inCurField = localField;
    } else {
        groupField->setSubField(localField);
    }

    _inFieldMap.insert(mapField::value_type(name, localField));

    return 0;
}

b_4 CInterfaceInfo::addOutField(const TField &field, const ch_1 *groupName) {
    if (!field.name || 0 == field.name[0]) {
        assert(0);
        return 1;
    }

    CField *localField = null_v;
    CField *groupField = null_v;
    ch_1 name[VARIABLE_NAME_LENGTH * 2] = {0};

    if (groupName && 0 != groupName[0]) {
        groupField = getOutField(groupName);

        if (null_v == groupField) {
            assert(0);
            return 2;
        }

        sprintf(name, "%s.%s", groupName, field.name);
    } else {
        sprintf(name, "%s", field.name);
    }

    // Check if there is a field which name is same as the field's name,
    // in the map.
    if (_outFieldMap.end() != _outFieldMap.find(name)) {
        assert(0);
        return 3;
    }

    switch (field.style) {
        case FIELD_NORMAL_STYLE: {
            EFieldType type;

            if (1 == field.length && field.isSigned) {
                type = FIELD_B_1_TYPE;
            } else if (1 == field.length && !field.isSigned) {
                type = FIELD_UB_1_TYPE;
            } else if (2 == field.length && field.isSigned) {
                type = FIELD_B_2_TYPE;
            } else if (2 == field.length && !field.isSigned) {
                type = FIELD_UB_2_TYPE;
            } else if (4 == field.length && field.isSigned) {
                type = FIELD_B_4_TYPE;
            } else if (4 == field.length && !field.isSigned) {
                type = FIELD_UB_4_TYPE;
            } else if (8 == field.length && field.isSigned) {
                type = FIELD_B_8_TYPE;
            } else if (8 == field.length && !field.isSigned) {
                type = FIELD_UB_8_TYPE;
            } else {
                assert(0);
                return 4;
            }

            if (0 != field.size || 0 != field.sizeName[0]) {
                assert(0);
                return 5;
            }

            localField = new CFieldNumber(name, type, groupField);
        }
            break;
        case FIELD_FLOAT_STYLE: {
            EFieldType type;

            if (4 == field.length) {
                type = FIELD_FB_4_TYPE;
            } else if (8 == field.length) {
                type = FIELD_FB_8_TYPE;

            } else {
                assert(0);
                return 6;
            }

            if (0 != field.size || 0 != field.sizeName[0]) {
                assert(0);
                return 7;
            }

            localField = new CFieldNumber(name, type, groupField);
        }
            break;
        case FIELD_STRING_STYLE: {
            if (0 == field.size || 0 != field.sizeName[0]) {
                assert(0);
                return 8;
            }

            localField = new CFieldString(name, field.size, groupField);
        }
            break;
        case FIELD_GROUP_STYLE: {
            if (0 == field.size || 0 != field.sizeName[0]) {
                assert(0);
                return 9;
            }

            CField *sizeField = getOutField(field.sizeName);
            assert(sizeField);

            localField = new CFieldGroup(name, sizeField);
        }
            break;
        default:
            assert(0);
            return 10;
    }

    if (!groupField) {
        if (_outCurField) {
            _outCurField->attach(localField);
        } else {
            _outField = localField;
        }

        _outCurField = localField;
    } else {
        groupField->setSubField(localField);
    }

    _outCurField = localField;
    _outFieldMap.insert(mapField::value_type(name, localField));

    return 0;
}

CField *CInterfaceInfo::getInField(const ch_1 *name) {
    if (!name || 0 == name[0]) {
        assert(0);
        return null_v;
    }

    mapField::iterator pos = _inFieldMap.find(name);

    if (_inFieldMap.end() != pos) {
        assert(pos->second);
        return pos->second;
    }

    return null_v;
}

CField *CInterfaceInfo::getOutField(const ch_1 *name) {
    if (!name || 0 == name[0]) {
        assert(0);
        return null_v;
    }

    mapField::iterator pos = _outFieldMap.find(name);

    if (_outFieldMap.end() != pos) {
        assert(pos->second);
        return pos->second;
    }

    return null_v;
}
