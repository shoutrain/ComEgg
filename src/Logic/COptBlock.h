#ifndef _C_OPT_BLOCK_H_
#define _C_OPT_BLOCK_H_

#include "COperator.h"

class COptBlock : public COperator {
public:
    COptBlock() : COperator(OT_BLOCK) {
    }

    COptBlock(const COptBlock &opt) : COperator(opt) {
    }

    const COptBlock &operator=(const COptBlock &opt) {
        if (this != &opt) {
            COperator::operator=(opt);
        }

        return *this;
    }

    virtual COperator *clone() const {
        return (COperator *) new COptBlock(*this);
    }

    virtual none_ work(const TMessageUnit *tmu) {
        callBlock Block;

        throw Block;
    }
};

#endif // _C_OPT_BLOCK_H_
