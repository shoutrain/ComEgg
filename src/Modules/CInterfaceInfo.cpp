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

none_ CInterfaceInfo::addInField(const TField &field, const ch_1 *groupName) {
    assert(field.name && 0 != field.name[0]);

    CField *localField = null_v;
    CField *groupField = null_v;
    ch_1 name[VARIABLE_NAME_LENGTH * 2] = {0};

    if (groupName && 0 != groupName[0]) {
        groupField = getInField(groupName);
        assert(groupField);
        sprintf(name, "%s.%s", groupName, field.name);
    } else {
        sprintf(name, "%s", field.name);
    }

    // Check if there is a localField which name is same as the localField's name,
    // in the map.
    assert(_inFieldMap.end() == _inFieldMap.find(name));

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
            }

            assert(0 == field.size && 0 == field.sizeName[0]);
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
            }

            assert(0 == field.size && 0 == field.sizeName[0]);
            localField = new CFieldNumber(name, type, groupField);
        }
            break;
        case FIELD_STRING_STYLE: {
            assert(0 != field.size && 0 == field.sizeName[0]);
            localField = new CFieldString(name, field.size, groupField);
        }
            break;
        case FIELD_GROUP_STYLE: {
            assert(0 == field.size && 0 != field.sizeName[0]);
            CField *sizeField = getInField(field.sizeName);
            assert(sizeField);

            localField = new CFieldGroup(name, sizeField);
        }
            break;
        default:
            assert(0);
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
}

none_ CInterfaceInfo::addOutField(const TField &field, const ch_1 *groupName) {
    assert(field.name && 0 != field.name[0]);

    CField *localField = null_v;
    CField *groupField = null_v;
    ch_1 name[VARIABLE_NAME_LENGTH * 2] = {0};

    if (groupName && 0 != groupName[0]) {
        groupField = getOutField(groupName);
        assert(groupField);
        sprintf(name, "%s.%s", groupName, field.name);
    } else {
        sprintf(name, "%s", field.name);
    }

    // Check if there is a field which name is same as the field's name,
    // in the map.
    assert(_outFieldMap.end() == _outFieldMap.find(name));

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
            }

            assert(0 == field.size && 0 == field.sizeName[0]);
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
            }

            assert(0 == field.size && 0 == field.sizeName[0]);
            localField = new CFieldNumber(name, type, groupField);
        }
            break;
        case FIELD_STRING_STYLE: {
            assert(0 != field.size && 0 == field.sizeName[0]);
            localField = new CFieldString(name, field.size, groupField);
        }
            break;
        case FIELD_GROUP_STYLE: {
            assert(0 == field.size && 0 != field.sizeName[0]);
            CField *sizeField = getOutField(field.sizeName);
            assert(sizeField);

            localField = new CFieldGroup(name, sizeField);
        }
            break;
        default:
            assert(0);
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
}

CField *CInterfaceInfo::getInField(const ch_1 *name) {
    assert(name && 0 != name[0]);

    mapField::iterator pos = _inFieldMap.find(name);

    if (_inFieldMap.end() != pos) {
        assert(pos->second);
        return pos->second;
    }

    return null_v;
}

CField *CInterfaceInfo::getOutField(const ch_1 *name) {
    assert(name && 0 != name[0]);

    mapField::iterator pos = _outFieldMap.find(name);

    if (_outFieldMap.end() != pos) {
        assert(pos->second);
        return pos->second;
    }

    return null_v;
}
