#ifndef _C_EXP_OR_H_
#define _C_EXP_OR_H_

#include "CExpression.h"

class CExpOr : CExpression {
public:
    CExpOr(const CExpression *leftExp, const CExpression *rightExp) {
        _leftExp = leftExp->clone();
        _rightExp = rightExp->clone();
    }


    virtual ~CExpOr() {
        _DEL(_leftExp);
        _DEL(_rightExp);
    }

    CExpOr(const CExpOr &exp) {
        _leftExp = exp._leftExp->clone();
        _rightExp = exp._rightExp->clone();
    }

    const CExpOr &operator=(const CExpOr &exp) {
        if (this != &exp) {
            _DEL(_leftExp);
            _DEL(_rightExp);
            _leftExp = exp._leftExp->clone();
            _rightExp = exp._rightExp->clone();
        }

        return *this;
    }

    virtual CExpression *clone() const {
        return (CExpression *) new CExpOr(*this);
    }

    virtual void init(const optUnit *unit) {
        _leftExp->init(unit);
        _rightExp->init(unit);
    }

    virtual bool_ evaluate(const TMessageUnit *tmu) const {
        return (bool_) (_leftExp->evaluate(tmu)
                || _rightExp->evaluate(tmu));
    }

private:
    CExpOr();

    CExpression *_leftExp;
    CExpression *_rightExp;
};

#endif // _C_EXP_OR_H_


