#ifndef _C_EXP_VAR_DUALITY_H_
#define _C_EXP_VAR_DUALITY_H_

#include "CExpression.h"

class CExpVarDuality : public CExpression {
public:
    CExpVarDuality(const CVariable *leftVar,
            const ECompareCalculate ecc,
            const CVariable *rightVar) {
        _leftVar = leftVar->clone();
        _ecc = ecc;
        _rightVar = rightVar->clone();
    }

    virtual ~CExpVarDuality() {
        _DEL(_leftVar);
        _DEL(_rightVar);
    }

    CExpVarDuality(const CExpVarDuality &exp) {
        _leftVar = exp._leftVar->clone();
        _ecc = exp._ecc;
        _rightVar = exp._rightVar->clone();
    }

    const CExpVarDuality &operator=(const CExpVarDuality &exp) {
        if (this != &exp) {
            _DEL(_leftVar);
            _DEL(_rightVar);
            _leftVar = exp._leftVar->clone();
            _ecc = exp._ecc;
            _rightVar = exp._rightVar->clone();
        }

        return *this;
    }

    virtual CExpression *clone() const {
        return (CExpression *) new CExpVarDuality(*this);
    }

    virtual none_ init(const optUnit *unit) {
        _leftVar->init(unit->data);
        _rightVar->init(unit->data);
    }

    virtual bool_ evaluate(const TMessageUnit *tmu) const {
        bool_ result = false_v;
        v_ leftValue(*_leftVar->value(tmu));
        v_ rightValue(*_rightVar->value(tmu));

        switch (_ecc) {
            case CC_EQ:
                result = (bool_) (leftValue == rightValue);
                break;
            case CC_GL:
                result = (bool_) (leftValue != rightValue);
                break;
            case CC_GT:
                result = (bool_) (leftValue > rightValue);
                break;
            case CC_GE:
                result = (bool_) (leftValue >= rightValue);
                break;
            case CC_LS:
                result = (bool_) (leftValue < rightValue);
                break;
            case CC_LE:
                result = (bool_) (leftValue <= rightValue);
                break;
        }

        return result;
    }

private:
    CExpVarDuality();

    CVariable *_leftVar;
    ECompareCalculate _ecc;
    CVariable *_rightVar;
};

#endif // _C_EXP_VAR_DUALITY_H_

