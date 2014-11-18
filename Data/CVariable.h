#ifndef CVARIABLE_H
#define CVARIABLE_H

#include "CData.h"
#include "../Network/NetworkCommon.h"

// It's not real variable, actually it's a template for variable
// used by operators
class CVariable
{
public:
	virtual CVariable *Clone() const = 0;
	virtual void Initialize(const CData *pData) = 0;
	virtual v_ *Value(const TMU *pTMU) = 0;

	// For CVarGroupDefined
	virtual v_ *Value(obj_ &) { return null_v; }
};

#endif // CVARIABLE_H
