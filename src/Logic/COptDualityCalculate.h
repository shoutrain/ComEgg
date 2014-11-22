#ifndef _C_OPT_DUALITY_CALCULATE_H_
#define _C_OPT_DUALITY_CALCULATE_H_

#include "COperator.h"

class COptDualityCalculate : public COperator {
public:
    COptDualityCalculate(const CVariable *leftVariable,
            const EDualityCalculate opt,
            const CVariable *rightVariable,
            const CVariable *resultVariable)
            : COperator(OT_DUALITY_CALCULATE) {
        _leftVariable = leftVariable->clone();
        _opt = opt;
        _rightVariable = rightVariable->clone();
        _resultVariable = resultVariable->clone();
    }

    virtual ~COptDualityCalculate() {
        _DEL(_leftVariable);
        _DEL(_rightVariable);
        _DEL(_resultVariable);
    }

    COptDualityCalculate(const COptDualityCalculate &opt) : COperator(opt) {
        _leftVariable = opt._leftVariable->clone();
        _opt = opt._opt;
        _rightVariable = opt._rightVariable->clone();
        _resultVariable = opt._resultVariable->clone();
    }

    const COptDualityCalculate &operator=(const COptDualityCalculate &opt) {
        if (this != &opt) {
            COperator::operator=(opt);

            _DEL(_leftVariable);
            _DEL(_rightVariable);
            _DEL(_resultVariable);
            _leftVariable = opt._leftVariable->clone();
            _opt = opt._opt;
            _rightVariable = opt._rightVariable->clone();
            _resultVariable = opt._resultVariable->clone();
        }

        return *this;
    }

    virtual COperator *clone() const {
        return (COperator *) new COptDualityCalculate(*this);
    }

    virtual void init(const optUnit *unit) {
        COperator::init(unit);

        _leftVariable->init(unit->data);
        _rightVariable->init(unit->data);
        _resultVariable->init(unit->data);
    }

    virtual void work(const TMessageUnit *tmu);

private:
    CVariable *_leftVariable;
    EDualityCalculate _opt;
    CVariable *_rightVariable;
    CVariable *_resultVariable;
};

#endif // _C_OPT_DUALITY_CALCULATE_H_
