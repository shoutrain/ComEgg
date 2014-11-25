#ifndef _C_OPT_UNITARY_CALCULATE_H_
#define _C_OPT_UNITARY_CALCULATE_H_

#include "COperator.h"

class COptUnitaryCalculate : public COperator {
public:
    COptUnitaryCalculate(const EUnitaryCalculate opt,
            const CVariable *resultVariable,
            const CVariable *rightVariable)
            : COperator(OT_UNITARY_CALCULATE) {
        _opt            = opt;
        _resultVariable = resultVariable->clone();
        _rightVariable  = rightVariable->clone();
    }

    virtual ~COptUnitaryCalculate() {
        _DEL(_resultVariable);
        _DEL(_rightVariable);
    }

    COptUnitaryCalculate(const COptUnitaryCalculate &opt) : COperator(opt) {
        _opt            = opt._opt;
        _resultVariable = opt._resultVariable->clone();
        _rightVariable  = opt._rightVariable->clone();
    }

    const COptUnitaryCalculate &operator=(const COptUnitaryCalculate &opt) {
        if (this != &opt) {
            COperator::operator=(opt);

            _DEL(_rightVariable);
            _DEL(_resultVariable);
            _opt            = opt._opt;
            _resultVariable = opt._resultVariable->clone();
            _rightVariable  = opt._rightVariable->clone();
        }

        return *this;
    }

    virtual COperator *clone() const {
        return (COperator *) new COptUnitaryCalculate(*this);
    }

    virtual none_ init(const optUnit *unit) {
        COperator::init(unit);

        _resultVariable->init(unit->data);
        _rightVariable->init(unit->data);
    }

    virtual none_ work(const TMessageUnit *tmu);

private:
    EUnitaryCalculate _opt;
    CVariable         *_resultVariable;
    CVariable         *_rightVariable;
};

#endif // _C_OPT_UNITARY_CALCULATE_H_
