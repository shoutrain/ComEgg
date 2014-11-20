#ifndef CVARIABLE_H
#define CVARIABLE_H

#include "CData.h"
#include "../Network/NetworkCommon.h"

// It's not real variable, actually it's a template for variable
// used by operators
class CAutoVar
{
public:
	virtual CAutoVar *Clone() const = 0;
	virtual void Initialize(const CData *pData) = 0;
	virtual v_ *Value(const TMessageUnit *pTMU) = 0;

	// For CVarGroupDefined
	virtual v_ *Value(obj_ &) { return null_v; }
};

#endif // CVARIABLE_H
