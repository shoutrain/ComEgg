#ifndef _C_OPT_IF_H_
#define _C_OPT_IF_H_

#include "CProgram.h"
#include "CExpression.h"

class CProgramIf : public CProgram {
public:
    CProgramIf(const CData *data = null_v) : CProgram(OT_IF, data) {
    };

    virtual ~CProgramIf() {
        clear();
    }

    CProgramIf(const CProgramIf &opt);

    const CProgramIf &operator=(const CProgramIf &opt);

    virtual COperator *clone() const {
        return (COperator *) new CProgramIf(*this);
    }

    virtual bool_ addOperator(const COperator *opt);

    bool_ addExpression(const CExpression *expression);

    virtual void init(const optUnit *unit);

    virtual void work(const TMessageUnit *tmu);

private:
    void clear();

    vectorExp _expVector;
};

#endif // _C_OPT_IF_H_
