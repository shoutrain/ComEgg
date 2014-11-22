#ifndef _C_OPT_NETWORK_WAKE_UP_H_
#define _C_OPT_NETWORK_WAKE_UP_H_

#include "COperator.h"

class COptNetworkWakeUp : public COperator {
public:
    COptNetworkWakeUp(const CVariable *networkName,
            const CVariable *result)
            : COperator(OT_NETWORK_WAKE_UP) {
        _networkName = networkName->clone();
        _result = result->clone();
    }

    virtual ~COptNetworkWakeUp() {
        _DEL(_networkName);
        _DEL(_result);
    }

    COptNetworkWakeUp(const COptNetworkWakeUp &opt) : COperator(opt) {
        _networkName = opt._networkName->clone();
        _result = opt._result->clone();
    }

    const COptNetworkWakeUp &operator=(const COptNetworkWakeUp &opt) {
        if (this != &opt) {
            COperator::operator=(opt);

            _DEL(_networkName);
            _DEL(_result);
            _networkName = opt._networkName->clone();
            _result = opt._result->clone();
        }

        return *this;
    }

    virtual COperator *clone() const {
        return (COperator *) new COptNetworkWakeUp(*this);
    }

    virtual void init(const optUnit *unit) {
        COperator::init(unit);

        _networkName->init(unit->data);
        _result->init(unit->data);
    }

    virtual void work(const TMessageUnit *tmu);

private:
    CVariable *_networkName;
    CVariable *_result;
};

#endif // _C_OPT_NETWORK_WAKE_UP_H_


