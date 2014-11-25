#ifndef _C_EXP_NOT_H_
#define _C_EXP_NOT_H_

#include "CExpression.h"

class CExpNot : CExpression {
public:
    CExpNot(const CExpression *exp) {
        _exp = exp->clone();
    }

    virtual ~CExpNot() {
        _DEL(_exp);
    }

    CExpNot(const CExpNot &exp) {
        _exp = exp._exp->clone();
    }

    const CExpNot &operator=(const CExpNot &exp) {
        if (this != &exp) {
            _DEL(_exp);

            _exp = exp._exp->clone();
        }

        return *this;
    }

    virtual CExpression *clone() const {
        return (CExpression *) new CExpNot(*this);
    }

    virtual none_ init(const optUnit *unit) {
        _exp->init(unit);
    }

    virtual bool_ evaluate(const TMessageUnit *tmu) const {
        return (bool_) !_exp->evaluate(tmu);
    }

private:
    CExpNot();

    CExpression *_exp;
};

#endif // CEXP_OR_H

