#ifndef _C_EXP_VAR_UNITARY_H_
#define _C_EXP_VAR_UNITARY_H_

#include "CExpression.h"

class CExpVarUnitary : public CExpression {
public:
    CExpVarUnitary(const CVariable *variable) {
        _variable = variable->clone();
    }

    virtual ~CExpVarUnitary() {
        _DEL(_variable);
    }

    CExpVarUnitary(const CExpVarUnitary &exp) {
        _variable = exp._variable->clone();
    }

    const CExpVarUnitary &operator=(const CExpVarUnitary &exp) {
        if (this != &exp) {
            _DEL(_variable);

            _variable = exp._variable->clone();
        }

        return *this;
    }

    virtual CExpression *clone() const {
        return (CExpression *) new CExpVarUnitary(*this);
    }

    virtual none_ init(const optUnit *unit) {
        _variable->init(unit->data);
    }

    virtual bool_ evaluate(const TMessageUnit *tmu) const {
        bool_ result = false_v;
        v_ value(*_variable->value(tmu));
        eht_ style = (eht_) _STYLE(value.getType());

        switch (style) {
            case NORMAL_STYLE:
            case FLOAT_STYLE:
                result = (0 == (b_4) value) ? false_v : true_v;
                break;
            case STRING_STYLE: {
                const ch_1 *psz = (const ch_1 *) value;

                if (null_v == psz || 0 == psz[0]) {
                    result = false_v;
                } else {
                    result = true_v;
                }
            }
                break;
            case OBJECT_STYLE: {
                const obj_ p = (const obj_) value;

                if (null_v == p) {
                    result = false_v;
                } else {
                    result = true_v;
                }
            }
                break;
        }


        return result;
    }

private:
    CExpVarUnitary();

    CVariable *_variable;
};

#endif // _C_EXP_VAR_UNITARY_H_

