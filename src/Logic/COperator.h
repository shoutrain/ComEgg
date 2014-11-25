#ifndef _C_OPERATOR_H_
#define _C_OPERATOR_H_

#include "LogicCommon.h"
#include "../Data/CVariable.h"

class COperator {
public:
    virtual COperator *clone() const = 0;

    EOperatorType getType() const {
        return _type;
    }

    const COperator *getParent() const {
        return _parent;
    }

    const CProcessor *getContainer() const {
        return _container;
    }

    virtual none_ reset() {
    }

    virtual none_ init(const optUnit *unit) {
        _container = unit->container;
        _parent = unit->parent;
        _data = unit->data;
    }

    virtual none_ work(const TMessageUnit *tmu) = 0;

protected:
    COperator(const EOperatorType type) {
        _type = type;
        _container = null_v;
        _parent = null_v;
        _data = null_v;
    }

    COperator(const COperator &opt) {
        _type = opt._type;
        _container = null_v;
        _parent = null_v;
        _data = null_v;
    }

    const COperator &operator=(const COperator &opt) {
        if (this != &opt) {
            _type = opt._type;
            _container = null_v;
            _parent = null_v;
            _data = null_v;
        }

        return *this;
    }

    EOperatorType _type;
    CProcessor *_container;
    COperator *_parent;
    CData *_data;

private:
    COperator();
};

#endif // _C_OPERATOR_H_
