#ifndef _C_OPT_USE_MODULE_H_
#define _C_OPT_USE_MODULE_H_

#include "COperator.h"
#include "../Modules/CInterfaceInfo.h"

class COptUseModule : public COperator {
public:
    COptUseModule(const CInterfaceInfo *interfaceInfo);

    COptUseModule(const COptUseModule &opt);

    const COptUseModule &operator=(const COptUseModule &opt);

    virtual COperator *clone() const {
        return (COperator *) new COptUseModule(*this);
    }

    virtual ~COptUseModule();

    bool_ addInParameter(CVariable *value);

    bool_ addOutParameter(const ch_1 *fieldName, CVariable *value);

    virtual void init(const optUnit *unit);

    virtual void work(const TMessageUnit *tmu);

private:
    COptUseModule();

    void clear();

    CInterfaceInfo *_interfaceInfo;

    vectorEvaluate _inEvaluateVector;
    vectorEvaluate _outEvaluateVector;
};

#endif // _C_OPT_USE_MODULE_H_
