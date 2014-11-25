#ifndef _C_EXP_AND_H_
#define _C_EXP_AND_H_

#include "CExpression.h"

class CExpAnd : CExpression {
public:
    CExpAnd(const CExpression *leftExp, const CExpression *rightExp) {
        _leftExp = leftExp->clone();
        _rightExp = rightExp->clone();
    }

    virtual ~CExpAnd() {
        _DEL(_leftExp);
        _DEL(_rightExp);
    }

    CExpAnd(const CExpAnd &exp) {
        _leftExp = exp._leftExp->clone();
        _rightExp = exp._rightExp->clone();
    }

    const CExpAnd &operator=(const CExpAnd &exp) {
        if (this != &exp) {
            _DEL(_leftExp);
            _DEL(_rightExp);

            _leftExp = exp._leftExp->clone();
            _rightExp = exp._rightExp->clone();
        }

        return *this;
    }

    virtual CExpression *clone() const {
        return (CExpression *) new CExpAnd(*this);
    }

    virtual none_ init(const optUnit *unit) {
        _leftExp->init(unit);
        _rightExp->init(unit);
    }

    virtual bool_ evaluate(const TMessageUnit *tmu) const {
        return (bool_) (_leftExp->evaluate(tmu)
                && _rightExp->evaluate(tmu));
    }

private:
    CExpAnd();

    CExpression *_leftExp;
    CExpression *_rightExp;
};

#endif // _C_EXP_AND_H_


