#ifndef _C_EXPRESSION_H_
#define _C_EXPRESSION_H_

class CExpression {
public:
    virtual CExpression *clone() const = 0;

    virtual void init(const optUnit *unit) = 0;

    virtual bool_ evaluate(const TMessageUnit *tmu) const = 0;
};

#endif // _C_EXPRESSION_H_

