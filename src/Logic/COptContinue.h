#ifndef _C_OPT_CONTINUE_H_
#define _C_OPT_CONTINUE_H_

#include "COperator.h"

class COptContinue : public COperator {
public:
    COptContinue() : COperator(OT_CONTINUE) {
    }

    COptContinue(const COptContinue &opt) : COperator(opt) {
    }

    const COptContinue &operator=(const COptContinue &opt) {
        if (this != &opt) {
            COperator::operator=(opt);
        }

        return *this;
    }

    virtual COperator *clone() const {
        return (COperator *) new COptContinue(*this);
    }

    virtual void work(const TMessageUnit *tmu) {
        callBreak Continue;

        throw Continue;
    }
};

#endif // _C_OPT_CONTINUE_H_
