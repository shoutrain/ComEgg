#ifndef _C_FIELD_STRING_H_
#define _C_FIELD_STRING_H_

#include "CField.h"

// For style of string
class CFieldString : public CField {
public:
    CFieldString(const ch_1 *name,
            size_ size,
            const CField *groupField = null_v)
            : CField(name, FIELD_STR_TYPE) {
        _unitSize = size;
        _groupField = (CField *) groupField;
    }

    virtual CField *clone(const CField *groupField,
            const CField *firstField) const {
        CFieldString *field = new CFieldString(_name,
                _unitSize,
                groupField);

        if (!firstField) {
            firstField = field;
        }

        if (_nextField) {
            field->attach(_nextField->clone(groupField, field));
        }

        return field;
    }

    virtual size_ size(const ub_1 *block = null_v,
            size_ blockSize = 0) const {
        return _unitSize;
    }

    virtual size_ offset(const ub_1 *block,
            size_ blockSize,
            size_ index = 0) const;

private:
    CFieldString();

    CFieldString(const CFieldString &);

    const CFieldString &operator=(const CFieldString &);
};

#endif // _C_FIELD_STRING_H_
