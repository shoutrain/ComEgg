#ifndef _C_OPT_FORWARD_H_
#define _C_OPT_FORWARD_H_

#include "COperator.h"
#include "../Transactions/CTransactionManager.h"

class COptForward : public COperator {
public:
    COptForward(const CVariable *object = null_v) : COperator(OT_FORWARD) {
        _object = null_v;
        _ip = null_v;
        _port = null_v;

        _sendType = TCP_SEND;

        if (object) {
            _object = object->clone();
        }
    }

    COptForward(b_4 sign/*No meaning*/,
            const CVariable *ip = null_v,
            const CVariable *port = null_v)
            : COperator(OT_SEND) {
        _object = null_v;
        _ip = null_v;
        _port = null_v;

        _sendType = UDP_SEND;

        if (ip && port) {
            _ip = ip->clone();
            _port = port->clone();
        }
    }

    virtual ~COptForward() {
        _DEL(_object);
        _DEL(_ip);
        _DEL(_port);
    }

    COptForward(const COptForward &opt) : COperator(opt) {
        _object = null_v;
        _ip = null_v;
        _port = null_v;

        _sendType = opt._sendType;

        if (TCP_SEND == _sendType) {
            _object = opt._object->clone();
        } else {
            _ip = opt._ip->clone();
            _port = opt._port->clone();
        }
    }

    const COptForward &operator=(const COptForward &opt) {
        if (this != &opt) {
            COperator::operator=(opt);

            _DEL(_object);
            _DEL(_ip);
            _DEL(_port);

            _sendType = opt._sendType;

            if (TCP_SEND == _sendType) {
                _object = opt._object->clone();
            }
            else {
                _ip = opt._ip->clone();
                _port = opt._port->clone();
            }
        }

        return *this;
    }

    virtual COperator *clone() const {
        return (COperator *) new COptForward(*this);
    }


    virtual none_ init(const optUnit *unit) {
        COperator::init(unit);

        if (TCP_SEND == _sendType) {
            _object->init(unit->data);
        } else {
            _ip->init(unit->data);
            _port->init(unit->data);
        }
    }

    virtual none_ work(const TMessageUnit *tmu);

private:
    enum {
        TCP_SEND,
        UDP_SEND
    } _sendType;

    CVariable *_object;
    CVariable *_ip;
    CVariable *_port;
};

#endif // COPT_FORWARD_H
