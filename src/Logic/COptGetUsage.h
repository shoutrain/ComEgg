#ifndef _C_OPT_GET_USAGE_H_
#define _C_OPT_GET_USAGE_H_

#include "COperator.h"

class COptGetUsage : public COperator {
public:
    COptGetUsage(const CVariable *result) : COperator(OT_GET_USAGE) {
        _result = result->clone();
    }

    virtual ~COptGetUsage() {
        _DEL(_result);
    }

    COptGetUsage(const COptGetUsage &opt) : COperator(opt) {
        _result = opt._result->clone();
    }

    const COptGetUsage &operator=(const COptGetUsage &opt) {
        if (this != &opt) {
            COperator::operator=(opt);

            _DEL(_result);
            _result = opt._result->clone();
        }

        return *this;
    }

    virtual COperator *clone() const {
        return (COperator *) new COptGetUsage(*this);
    }

    virtual void init(const optUnit *unit) {
        COperator::init(unit);

        _result->init(unit->data);
    }

    virtual void work(const TMessageUnit *tmu);

private:
    CVariable *_result;
};

#endif // _C_OPT_GET_USAGE_H_


