#ifndef _C_OPT_SPLIT_H_
#define _C_OPT_SPLIT_H_

#include "COperator.h"

class COptSplit : public COperator {
public:
    COptSplit(const CVariable *environment,
            const CVariable *result)
            : COperator(OT_SPLIT) {
        _environment = environment->clone();
        _result = result->clone();
    }

    virtual ~COptSplit() {
        _DEL(_environment);
        _DEL(_result);
    }

    COptSplit(const COptSplit &opt) : COperator(opt) {
        _environment = opt._environment->clone();
        _result = opt._result->clone();
    }

    const COptSplit &operator=(const COptSplit &opt) {
        if (this != &opt) {
            COperator::operator=(opt);

            _DEL(_environment);
            _DEL(_result);
            _environment = opt._environment->clone();
            _result = opt._result->clone();
        }

        return *this;
    }

    virtual COperator *clone() const {
        return (COperator *) new COptSplit(*this);
    }

    virtual void init(const optUnit *unit) {
        COperator::init(unit);

        _environment->init(unit->data);
        _result->init(unit->data);
    }

    virtual void work(const TMessageUnit *tmu);

private:
    CVariable *_environment;
    CVariable *_result;
};

#endif // _C_OPT_SPLIT_H_


