#ifndef _C_OPT_BREAK_H_
#define _C_OPT_BREAK_H_

#include "COperator.h"

class COptBreak : public COperator {
public:
    COptBreak() : COperator(OT_BREAK) {
    }

    COptBreak(const COptBreak &opt) : COperator(opt) {
    }

    const COptBreak &operator=(const COptBreak &opt) {
        if (this != &opt) {
            COperator::operator=(opt);
        }

        return *this;
    }

    virtual COperator *clone() const {
        return (COperator *) new COptBreak(*this);
    }

    virtual void work(const TMessageUnit *tmu) {
        callBreak Break;

        throw Break;
    }
};

#endif // _C_OPT_BREAK_H_
