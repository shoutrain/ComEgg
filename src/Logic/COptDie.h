#ifndef _C_OPT_DIE_H_
#define _C_OPT_DIE_H_

#include "COperator.h"
#include "../Network/CNetworkManager.h"

class COptDie : public COperator {
public:
    COptDie() : COperator(OT_DIE) {
    }

    COptDie(const COptDie &opt) : COperator(opt) {
    }

    const COptDie &operator=(const COptDie &opt) {
        if (this != &opt) {
            COperator::operator=(opt);
        }

        return *this;
    }

    virtual COperator *clone() const {
        return (COperator *) new COptDie(*this);
    }

    virtual none_ work(const TMessageUnit *tmu) {
        CNetworkManager::instance()->Exit();
    }
};

#endif // _C_OPT_DIE_H_
