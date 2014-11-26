#include "CPduInfo.h"
#include "CProtocolInfo.h"

none_ CProtocolInfo::stop() {
    for (mapPdu::iterator pos1 = _pduInfoMap.begin();
         pos1 != _pduInfoMap.end(); pos1++) {
        assert(pos1->second);
        _DEL(pos1->second);
    }

    _pduInfoMap.clear();

    for (mapField::iterator pos2 = _headFieldMap.begin();
         pos2 != _headFieldMap.end(); pos2++) {
        assert(pos2->second);
        _DEL(pos2->second);
    }

    _headFieldMap.clear();

    _field    = null_v;
    _curField = null_v;
}

none_ CProtocolInfo::addHeadField(const TField &field,
        const ch_1 *groupName) {
    assert(field.name && 0 != field.name[0]);

    CField *localField                    = null_v;
    CField *groupField                    = null_v;
    ch_1   name[VARIABLE_NAME_LENGTH * 2] = {0};

    if (groupName && 0 != groupName[0]) {
        groupField = getHeadField(groupName);
        assert(groupField);
        sprintf(name, "%s.%s", groupName, field.name);
    }
    else {
        sprintf(name, "%s", field.name);
    }

    // Check if there is a field which name is same as the field's name,
    // in the map.
    assert(_headFieldMap.end() == _headFieldMap.find(name));

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

            assert (0 == field.size && 0 == field.sizeName[0]);
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
            const CField *pSizeField = getHeadField(field.sizeName);
            assert(pSizeField);

            localField = new CFieldGroup(name, pSizeField);
        }
            break;
        default:
            assert(0);
    }

    if (!groupField) {
        if (_curField) {
            _curField->attach(localField);
        } else {
            _field = localField;
        }

        _curField = localField;
    }
    else {
        groupField->setSubField(localField);
    }

    _headFieldMap.insert(mapField::value_type(name, localField));
}

CField *CProtocolInfo::getHeadField(const ch_1 *name) {
    assert(name && 0 != name[0]);

    mapField::iterator pos = _headFieldMap.find(name);

    assert(_headFieldMap.end() != pos);
    assert(pos->second);
    return pos->second;
}

none_ CProtocolInfo::addPdu(const ch_1 *name,
        CPduInfo *&pduInfo) {
    assert(name && 0 != name[0] && !pduInfo);

    pduInfo = new CPduInfo(_field);
    _pduInfoMap.insert(mapPdu::value_type(name, pduInfo));
}

CPduInfo *CProtocolInfo::getPdu(const ch_1 *name) {
    assert(name && 0 != name[0]);

    mapPdu::iterator pos = _pduInfoMap.find(name);

    if (_pduInfoMap.end() != pos) {
        assert(pos->second);
        return pos->second;
    }

    return null_v;
}
