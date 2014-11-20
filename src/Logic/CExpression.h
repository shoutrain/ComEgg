#ifndef CEXPRESSION_H
#define CEXPRESSION_H

class CExpression
{
public:
	virtual CExpression *Clone() const = 0;

	virtual void Initialize(const opt_unit *pUnit) = 0;
	virtual bool_ Evaluate(const TMessageUnit *pTMU) const = 0;
};

#endif // CEXPRESSION_H

