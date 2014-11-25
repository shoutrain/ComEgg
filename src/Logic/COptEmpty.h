#ifndef _C_OPT_EMPTY_H_
#define _C_OPT_EMPTY_H_

#include "COperator.h"

class COptEmpty : public COperator {
public:

    COptEmpty(const CVariable *pVariable)
            : COperator(OT_EMPTY) {
        _variable = pVariable->clone();
    }

    virtual ~COptEmpty() {
        _DEL(_variable);
    }

    COptEmpty(const COptEmpty &opt) : COperator(opt) {
        _variable = opt._variable->clone();
    }

    const COptEmpty &operator=(const COptEmpty &opt) {
        if (this != &opt) {
            COperator::operator=(opt);

            _DEL(_variable);
            _variable = opt._variable->clone();
        }

        return *this;
    }

    virtual COperator *clone() const {
        return (COperator *) new COptEmpty(*this);
    }

    virtual none_ init(const optUnit *unit) {
        COperator::init(unit);

        _variable->init(unit->data);
    }

    virtual none_ work(const TMessageUnit *tmu);

private:
    CVariable *_variable;
};

#endif // _C_OPT_EMPTY_H_


