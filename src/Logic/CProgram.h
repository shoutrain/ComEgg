#ifndef _C_PROGRAM_H_
#define _C_PROGRAM_H_

#include "COperator.h"

class CProgram : public COperator {
public:
    CProgram(const CData *data = null_v) : COperator(OT_PROGRAM) {
        if (data) {
            _ornData = *data;
            _data    = *data;
        }
    }

    CProgram(const CProgram &opt);

    const CProgram &operator=(const CProgram &opt);

    virtual COperator *clone() const {
        return (COperator *) new CProgram(*this);
    }

    virtual bool_ addOperator(const COperator *opt);

    virtual none_ setData(const CData &data) {
        _ornData = data;
        _data    = data;
    }

    virtual CData &data() {
        return _data;
    }

    virtual none_ reset();

    virtual none_ init(const optUnit *unit);

    virtual none_ work(const TMessageUnit *tmu);

protected:
    CProgram(const EOperatorType type, const CData *data = null_v)
            : COperator(type) {
        if (data) {
            _ornData = *data;
            _data    = *data;
        }
    }

    virtual none_ clear();

    vectorOpt _optVector;

    CData _ornData;
    CData _data;
};

#endif // _C_PROGRAM_H_

