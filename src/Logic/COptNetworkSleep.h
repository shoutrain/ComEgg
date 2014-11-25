#ifndef _C_OPT_NETWORK_SLEEP_H_
#define _C_OPT_NETWORK_SLEEP_H_

#include "COperator.h"

class COptNetworkSleep : public COperator {
public:
    COptNetworkSleep(const CVariable *networkName,
            const CVariable *result)
            : COperator(OT_NETWORK_SLEEP) {
        _networkName = networkName->clone();
        _result = result->clone();
    }

    virtual ~COptNetworkSleep() {
        _DEL(_networkName);
        _DEL(_result);
    }

    COptNetworkSleep(const COptNetworkSleep &opt) : COperator(opt) {
        _networkName = opt._networkName->clone();
        _result = opt._result->clone();
    }

    const COptNetworkSleep &operator=(const COptNetworkSleep &opt) {
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
        return (COperator *) new COptNetworkSleep(*this);
    }

    virtual none_ init(const optUnit *unit) {
        COperator::init(unit);

        _networkName->init(unit->data);
        _result->init(unit->data);
    }

    virtual none_ work(const TMessageUnit *tmu);

private:
    CVariable *_networkName;
    CVariable *_result;
};

#endif // _C_OPT_NETWORK_SLEEP_H_



