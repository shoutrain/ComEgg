#ifndef _C_FIELD_GROUP_H_
#define _C_FIELD_GROUP_H_

#include "CField.h"

// For style of group on network
class CFieldGroup : public CField {
public:
    CFieldGroup(const ch_1 *name, const CField *sizeField)
            : CField(name, FIELD_GROUP_TYPE) {
        _sizeField = (CField *) sizeField;
    }

    virtual CField *clone(const CField *groupField,
            const CField *firstField) const {
        if (!firstField || !_sizeField) {
            return null_v;
        }

        CField *sizeField = (CField *) firstField;

        while (sizeField) {
            if (strncmp(sizeField->name(),
                    _sizeField->name(),
                    VARIABLE_NAME_LENGTH)) {
                break;
            }

            sizeField = (CField *) sizeField->getNextField();
        }

        CFieldGroup *field = new CFieldGroup(_name, sizeField);

        if (_nextField) {
            field->attach(_nextField->clone(null_v, firstField));
        }

        if (_subField) {
            field->setSubField(_subField->clone(field, null_v));
        }

        return field;
    }

    virtual size_ size(const ub_1 *block = null_v,
            size_ blockSize = 0) const;

    virtual size_ offset(const ub_1 *block,
            size_ blockSize,
            size_ index = 0) const;

protected:
    CField *_sizeField;

private:
    CFieldGroup();

    CFieldGroup(const CFieldGroup &);

    const CFieldGroup &operator=(const CFieldGroup &);
};

#endif // _C_FIELD_GROUP_H_
