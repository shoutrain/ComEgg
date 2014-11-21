#ifndef _C_FIELD_NUMBER_H_
#define _C_FIELD_NUMBER_H_

#include "CField.h"

// For style of normal and float
class CFieldNumber : public CField {
public:
    CFieldNumber(const ch_1 *name,
            EFieldType type,
            const CField *groupField = null_v)
            : CField(name, type) {
        _groupField = (CField *) groupField;
        _unitSize = _LEN(_type);
    }

    virtual CField *clone(const CField *groupField,
            const CField *firstField) const {
        CFieldNumber *field = new CFieldNumber(_name,
                _type,
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
    CFieldNumber();

    CFieldNumber(const CFieldNumber &);

    const CFieldNumber &operator=(const CFieldNumber &);
};

#endif // _C_FIELD_NUMBER_H_
