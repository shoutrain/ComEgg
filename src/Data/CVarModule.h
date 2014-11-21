#ifndef _C_VAR_MODULE_H_
#define _C_VAR_MODULE_H_

#include "CVariable.h"
#include "CField.h"

class CVarModule : public CVariable {
public:
    CVarModule(const CField *field) {
        field = (CField *) field;
    }

    virtual CVariable *clone() const;

    virtual void init(const CData *data);

    virtual v_ *value(const TMessageUnit *tmu);

private:
    CVarModule();

    CVarModule(const CVarModule &);

    const CVarModule &operator=(const CVarModule &);

    CField *field;

    v_ _value;
};

#endif // _C_VAR_MODULE_H_
