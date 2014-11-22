#ifndef _C_OPT_CONFIG_GROUP_H_
#define _C_OPT_CONFIG_GROUP_H_

#include "COperator.h"

class COptConfigGroup : public COperator {
public:
    COptConfigGroup(const CVariable *group, const CVariable *size)
            : COperator(OT_CONFIG_GROUP) {
        _group = group->clone();
        _size = group->clone();
    }

    virtual ~COptConfigGroup() {
        _DEL(_group);
        _DEL(_size);
    }

    COptConfigGroup(const COptConfigGroup &opt) : COperator(opt) {
        _group = opt._group->clone();
        _size = opt._group->clone();
    }

    const COptConfigGroup &operator=(const COptConfigGroup &opt) {
        if (this != &opt) {
            COperator::operator=(opt);

            _DEL(_group);
            _DEL(_size);
            _group = opt._group->clone();
            _size = opt._group->clone();
        }

        return *this;
    }

    virtual COperator *clone() const {
        return (COperator *) new COptConfigGroup(*this);
    }

    virtual void init(const optUnit *unit) {
        COperator::init(unit);

        _group->init(unit->data);
        _size->init(unit->data);
    }

    virtual void work(const TMessageUnit *tmu);

private:
    CVariable *_group;
    CVariable *_size;
};

#endif // _C_OPT_CONFIG_GROUP_H_


