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

    virtual void setData(const CData &data) {
        _ornData = data;
        _data    = data;
    }

    virtual CData &data() {
        return _data;
    }

    virtual void reset();

    virtual void init(const optUnit *unit);

    virtual void work(const TMessageUnit *tmu);

protected:
    CProgram(const EOperatorType type, const CData *data = null_v)
            : COperator(type) {
        if (data) {
            _ornData = *data;
            _data    = *data;
        }
    }

    virtual void clear();

    vectorOpt _optVector;

    CData _ornData;
    CData _data;
};

#endif // _C_PROGRAM_H_

