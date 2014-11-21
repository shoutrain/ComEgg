#ifndef _C_VAR_SOLID_DEFINED_H_
#define _C_VAR_SOLID_DEFINED_H_

#include "CVariable.h"

class CVarSolidDefined : public CVariable {
public:
    CVarSolidDefined(const ch_1 *name) {
        memset(_name, 0, VARIABLE_NAME_LENGTH);
        strncpy(_name, name, VARIABLE_NAME_LENGTH);
        _value = null_v;
    }

    virtual CVariable *clone() const;

    virtual void init(const CData *data);

    virtual v_ *value(const TMessageUnit *tmu);

private:
    CVarSolidDefined();

    CVarSolidDefined(const CVarSolidDefined &);

    const CVarSolidDefined &operator=(const CVarSolidDefined &);

    ch_1 _name[VARIABLE_NAME_LENGTH];
    v_ *_value;
};

#endif // _C_VAR_SOLID_DEFINED_H_
