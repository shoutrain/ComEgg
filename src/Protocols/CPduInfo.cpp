#include "CPduInfo.h"

none_ CPduInfo::start(const CField *headField) {
    _field = null_v;
    _curField = null_v;

    if (headField) {
        _field = headField->clone(null_v, null_v);
    }

    CField *p = _field;

    while (p) {
        if (FIELD_GROUP_TYPE == p->type()) {
            CField *q = p->getSubField();

            while (q) {
                ch_1 name[VARIABLE_NAME_LENGTH * 2] = {0};

                sprintf(name, "%s.%s", p->name(), q->name());
                _fieldMap.insert(mapField::value_type(name, q));
                q = q->getNextField();
            }
        }

        _curField = p;
        _fieldMap.insert(mapField::value_type(p->name(), p));
        p = p->getNextField();
    }
}

none_ CPduInfo::stop() {
    for (mapField::iterator pos = _fieldMap.begin(); pos != _fieldMap.end();
         pos++) {
        _DEL(pos->second);
    }

    _fieldMap.clear();
    _field = null_v;
    _curField = null_v;
}

none_ CPduInfo::addField(const TField &field, const ch_1 *groupName) {
    assert(field.name && 0 != field.name[0]);

    CField *singleField                   = null_v;
    CField *groupField                    = null_v;
    ch_1   name[VARIABLE_NAME_LENGTH * 2] = {0};

    if (groupName && 0 != groupName[0]) {
        groupField = getField(groupName);
        assert(groupField);
        sprintf(name, "%s.%s", groupName, field.name);
    } else {
        sprintf(name, "%s", field.name);
    }

    // Check if there is a field which name is same as the field's name,
    // in the map.
    assert(_fieldMap.end() == _fieldMap.find(name));

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
            singleField = new CFieldNumber(name, type, groupField);
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
            singleField = new CFieldNumber(name, type, groupField);
        }
            break;
        case FIELD_STRING_STYLE: {
            assert(0 != field.size && 0 == field.sizeName[0]);
            singleField = new CFieldString(name, field.size, groupField);
        }
            break;
        case FIELD_GROUP_STYLE: {
            assert(0 == field.size && 0 != field.sizeName[0]);
            CField *sizeField = getField(field.sizeName);
            assert(sizeField);

            singleField = new CFieldGroup(name, sizeField);
        }
            break;
        default:
            assert(0);
    }

    if (!groupField) {
        if (_curField) {
            _curField->attach(singleField);
        } else {
            _field = singleField;
        }

        _curField = singleField;
    } else {
        groupField->setSubField(singleField);
    }

    _fieldMap.insert(mapField::value_type(name, singleField));
}

CField *CPduInfo::getField(const ch_1 *name) {
    assert(name && 0 != name[0]);

    mapField::const_iterator pos = _fieldMap.find(name);

    if (_fieldMap.end() == pos) {
        return null_v;
    }

    return pos->second;
}
