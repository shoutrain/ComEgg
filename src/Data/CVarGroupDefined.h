#ifndef _C_VAR_GROUP_DEFINED_H_
#define _C_VAR_GROUP_DEFINED_H_

#include "CVariable.h"

class CVarGroupDefined : public CVariable {
public:
    CVarGroupDefined(const ch_1 *groupName,
            const ch_1 *subName = null_v,
            const ch_1 *indexName = null_v) {
        memset(_groupName, 0, VARIABLE_NAME_LENGTH);
        memset(_indexName, 0, VARIABLE_NAME_LENGTH);
        memset(_subName, 0, VARIABLE_NAME_LENGTH);

        strncpy(_groupName, groupName, VARIABLE_NAME_LENGTH);

        if (subName) {
            strncpy(_subName, subName, VARIABLE_NAME_LENGTH);
        }

        if (indexName) {
            strncpy(_indexName, indexName, VARIABLE_NAME_LENGTH);
        }

        _field = null_v;
        _size = null_v;
        _index = null_v;
        _groupData = null_v;
    }

    virtual CVariable *clone() const;

    virtual none_ init(const CData *data);

    virtual v_ *value(const TMessageUnit *tmu);

    virtual v_ *value(obj_ &);

private:
    CVarGroupDefined();

    CVarGroupDefined(const CVarGroupDefined &);

    const CVarGroupDefined &operator=(const CVarGroupDefined &);

    ch_1 _groupName[VARIABLE_NAME_LENGTH];
    ch_1 _subName[VARIABLE_NAME_LENGTH];

    ch_1 _indexName[VARIABLE_NAME_LENGTH];
    CField *_field;
    v_ *_size;
    v_ *_index;

    v_ _value;

    TFieldGroup *_groupData;
};

#endif // _C_VAR_GROUP_DEFINED_H_
