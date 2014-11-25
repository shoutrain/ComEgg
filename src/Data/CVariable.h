#ifndef _C_VARIABLE_H_
#define _C_VARIABLE_H_

#include "CData.h"
#include "../Network/NetworkCommon.h"

// It's not real variable, actually it's a template for variable
// used by operators
class CVariable
{
public:
    virtual CVariable *clone() const = 0;

    virtual none_ init(const CData *data) = 0;

    virtual v_ *value(const TMessageUnit *tmu) = 0;

	// For CVarGroupDefined
    virtual v_ *value(obj_ &) {
        return null_v;
    }
};

#endif // _C_VARIABLE_H_
