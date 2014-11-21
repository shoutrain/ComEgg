#ifndef _C_FIELD_H_
#define _C_FIELD_H_

#include "DataCommon.h"

#include <set>

using namespace std;

class CField;

typedef set<const CField *> setField;

class CField {
public:
    virtual CField *clone(const CField *groupField,
            const CField *firstField) const {
        return null_v;
    }

    virtual ~CField() {
    }

    EFieldType type() const {
        return _type;
    }

    const ch_1 *name() const {
        return _name;
    }

    void attach(const CField *field) {
        ((CField *) field)->setPrevField(this);
        setNextField(field);
    }

    // For field in group
    const CField *getGroupField() const {
        return _groupField;
    }

    // for group
    void setSubField(const CField *field) {
        CField *rollField = (CField *) field;
        size_ size = 0;

        while (rollField) {
            size += rollField->getUnitSize();
            rollField = (CField *) rollField->getNextField();
        }

        if (!_subField) {
            _subField = (CField *) field;
            _unitSize = size;
        } else {
            rollField = (CField *) _subField;

            while (rollField->getNextField()) {
                rollField = (CField *) rollField->getNextField();
            }

            rollField->attach((CField *) field);
            _unitSize += size;
        }
    }

    // for group
    const CField *getSubField() const {
        return _subField;
    }

    void setPrevField(const CField *field) {
        _prevField = (CField *) field;
    }

    void setNextField(const CField *field) {
        _nextField = (CField *) field;
    }

    const CField *getNextField() const {
        return _nextField;
    }

    size_ getUnitSize() const {
        return _unitSize;
    }

    // For network
    virtual size_ size(const ub_1 *block = null_v,
            size_ blockSize = 0) const {
        return 0;
    }

    // For network
    virtual size_ offset(const ub_1 *block,
            size_ blockSize,
            size_ index = 0) const {
        return 0;
    }

    // For defined
    virtual const ch_1 *getSizeName() const {
        return null_v;
    }

    // For defined
    virtual size_ offset(size_ size,
            size_ blockSize,
            size_ index = 0) const {
        return 0;
    }

protected:
    CField(const ch_1 *name, EFieldType type) {
        strncpy(_name, name, VARIABLE_NAME_LENGTH);
        _type = type;
        _unitSize = 0;
        _groupField = null_v;
        _subField = null_v;
        _prevField = null_v;
        _nextField = null_v;
    }

    ch_1 _name[VARIABLE_NAME_LENGTH];
    EFieldType _type;

    size_ _unitSize;

    // If it's independent field, this variable is null_v;
    // If it's field in group, this variable indicates the parent group.
    CField *_groupField;

    // If it's independent field, this variable is null_v;
    // If it's group field, this variable is the first children field;
    CField *_subField;

    CField *_prevField;
    CField *_nextField;

private:
    CField();

    CField(const CField &);

    const CField &operator=(const CField &);
};

#endif // _C_FIELD_H_
