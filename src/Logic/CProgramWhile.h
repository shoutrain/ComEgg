#ifndef _C_OPT_WHILE_H_
#define _C_OPT_WHILE_H_

#include "CProgram.h"
#include "CExpression.h"

class CProgramWhile : public CProgram {
public:
    CProgramWhile(bool_ judgeHead,
            const CExpression *expression,
            const CData *data = null_v)
            : CProgram(OT_WHILE, data) {
        _judgeHead  = judgeHead;
        _expression = expression->clone();
    }

    virtual ~CProgramWhile() {
        clear();
    }

    CProgramWhile(const CProgramWhile &opt) : CProgram(opt) {
        _judgeHead  = opt._judgeHead;
        _expression = opt._expression->clone();
    }

    const CProgramWhile &operator=(const CProgramWhile &opt) {
        if (this != &opt) {
            clear();

            CProgram::operator=(opt);

            _judgeHead  = opt._judgeHead;
            _expression = opt._expression->clone();
        }

        return *this;
    }

    virtual COperator *clone() const {
        return (COperator *) new CProgramWhile(*this);
    }

    virtual void init(const optUnit *unit) {
        CProgram::init(unit);

        optUnit ou;

        memcpy(&ou, unit, sizeof(optUnit));
        ou.data   = &_data;
        ou.parent = this;

        _expression->init(&ou);
    }

    virtual void work(const TMessageUnit *tmu);

private:
    CProgramWhile();

    void clear() {
        CProgram::clear();

        _DEL(_expression);
    }

    bool_       _judgeHead;
    CExpression *_expression;
};

#endif // _C_OPT_WHILE_H_
