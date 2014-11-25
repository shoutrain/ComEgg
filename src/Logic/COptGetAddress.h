#ifndef _C_OPT_GET_ADDRESS_H_
#define _C_OPT_GET_ADDRESS_H_

#include "COperator.h"
#include "../Transactions/CTransactionManager.h"

class COptGetAddress : public COperator {
public:
    COptGetAddress(const CVariable *ip,
            const CVariable *port,
            bool_ remote = true_v)
            : COperator(OT_GET_ADDRESS) {
        _ip = ip->clone();
        _port = port->clone();
        _remote = remote;
    }

    virtual ~COptGetAddress() {
        _DEL(_ip);
        _DEL(_port);
    }

    COptGetAddress(const COptGetAddress &opt) : COperator(opt) {
        _ip = opt._ip->clone();
        _port = opt._port->clone();
        _remote = opt._remote;
    }

    const COptGetAddress &operator=(const COptGetAddress &opt) {
        if (this != &opt) {
            _DEL(_ip);
            _DEL(_port);
            _ip = opt._ip->clone();
            _port = opt._port->clone();
            _remote = opt._remote;
        }

        return *this;
    }

    virtual COperator *clone() const {
        return (COperator *) new COptGetAddress(*this);
    }

    virtual none_ init(const optUnit *unit) {
        COperator::init(unit);

        _ip->init(unit->data);
        _port->init(unit->data);
    }

    virtual none_ work(const TMessageUnit *tmu);

private:
    bool_ _remote;

    CVariable *_ip;
    CVariable *_port;
};

#endif // _C_OPT_GET_ADDRESS_H_
