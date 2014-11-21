#ifndef _C_FIELD_GROUP_DEFINED_H_
#define _C_FIELD_GROUP_DEFINED_H_

#include "CField.h"

// For style of defined group
class CFieldGroupDefined : public CField {
public:
    CFieldGroupDefined(const ch_1 *name, const ch_1 *sizeName)
            : CField(name, FIELD_GROUP_TYPE) {
        memset(_sizeName, 0, VARIABLE_NAME_LENGTH);
        strncpy(_sizeName, sizeName, VARIABLE_NAME_LENGTH);
    }

    virtual CField *clone(const CField *pGroupField,
            const CField *pFirstField) const {
        CFieldGroupDefined *pField = new CFieldGroupDefined(_name,
                _sizeName);

        if (_subField)
            pField->setSubField(_subField->clone(this, null_v));

        return pField;
    }

    virtual const ch_1 *getSizeName() const {
        return _sizeName;
    }

    virtual size_ offset(size_ size,
            size_ blockSize,
            size_ index = 0) const;

protected:
    ch_1 _sizeName[VARIABLE_NAME_LENGTH];

private:
    CFieldGroupDefined();

    CFieldGroupDefined(const CFieldGroupDefined &);

    const CFieldGroupDefined &operator=(const CFieldGroupDefined &);
};

#endif // _C_FIELD_GROUP_DEFINED_H_
