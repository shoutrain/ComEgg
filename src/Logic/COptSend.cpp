#include "COptSend.h"

#include "../Transactions/CProcessor.h"
#include "../Data/CVarNetwork.h"

COptSend::COptSend(const CPduInfo *pduInfo,
        const CVariable *destination)
        : COperator(OT_SEND) {
    _destination = null_v;
    _ip = null_v;
    _port = null_v;

    _sendType = TCP_SEND;
    _pduInfo = (CPduInfo *) pduInfo;

    if (_destination) {
        _destination = destination->clone();
    }

    CField *fieldInfo = _pduInfo->getStruct();
    TEvaluate *evaluate = null_v;

    while (fieldInfo) {
        if (null_v == fieldInfo->getGroupField()) {
            evaluate = new TEvaluate;

            evaluate->fieldInfo = fieldInfo;
            evaluate->field = null_v;
            evaluate->value = null_v;

            _evaluateVector.push_back(evaluate);
        }

        fieldInfo = (CField *) fieldInfo->getNextField();
    }
}

COptSend::COptSend(b_4 sign/*No meaning*/,
        const CPduInfo *pduInfo,
        const CVariable *ip,
        const CVariable *port)
        : COperator(OT_SEND) {
    _destination = null_v;
    _ip = null_v;
    _port = null_v;

    _sendType = UDP_SEND;
    _pduInfo = (CPduInfo *) pduInfo;

    if (_ip) {
        _ip = ip->clone();
    }

    if (_port) {
        _port = port->clone();
    }

    CField *fieldInfo = _pduInfo->getStruct();
    TEvaluate *evaluate = new TEvaluate;

    while (fieldInfo) {
        if (null_v == fieldInfo->getGroupField()) {
            evaluate->fieldInfo = fieldInfo;
            evaluate->field = null_v;
            evaluate->value = null_v;

            _evaluateVector.push_back(evaluate);
        }

        fieldInfo = (CField *) fieldInfo->getNextField();
    }
}

COptSend::COptSend(const COptSend &opt) : COperator(opt) {
    _destination = null_v;
    _ip = null_v;
    _port = null_v;

    _pduInfo = opt._pduInfo;
    _sendType = opt._sendType;

    if (TCP_SEND == _sendType && opt._destination) {
        _destination = opt._destination->clone();
    } else if (UDP_SEND == _sendType && opt._ip && opt._port) {
        _ip = opt._ip->clone();
        _port = opt._port->clone();
    }

    for (vectorEvaluate::const_iterator pos = opt._evaluateVector.begin();
         pos != opt._evaluateVector.end(); pos++) {
        TEvaluate *evaluate = new TEvaluate;

        memset(evaluate, 0, sizeof(TEvaluate));
        evaluate->fieldInfo = (*pos)->fieldInfo;

        if ((*pos)->field) {
            evaluate->field = (*pos)->field->clone();
        }

        if ((*pos)->value) {
            evaluate->value = (*pos)->value->clone();
        }

        _evaluateVector.push_back(evaluate);
    }
}

const COptSend &COptSend::operator=(const COptSend &opt) {
    if (this != &opt) {
        COperator::operator=(opt);

        clear();

        _pduInfo = opt._pduInfo;
        _sendType = opt._sendType;

        if (TCP_SEND == _sendType && opt._destination) {
            _destination = opt._destination->clone();
        } else if (UDP_SEND == _sendType && opt._ip && opt._port) {
            _ip = opt._ip->clone();
            _port = opt._port->clone();
        }

        for (vectorEvaluate::const_iterator pos = opt._evaluateVector.begin();
             pos != opt._evaluateVector.end(); pos++) {
            TEvaluate *evaluate = new TEvaluate;

            memset(evaluate, 0, sizeof(TEvaluate));
            evaluate->fieldInfo = (*pos)->fieldInfo;

            if ((*pos)->field) {
                evaluate->field = (*pos)->field->clone();
            }

            if ((*pos)->value) {
                evaluate->value = (*pos)->value->clone();
            }

            _evaluateVector.push_back(evaluate);
        }
    }

    return *this;
}

COptSend::~COptSend() {
    clear();
}

none_ COptSend::clear() {
    _pduInfo = null_v;
    _sendType = NONE_SEND;

    _DEL(_destination);
    _DEL(_ip);
    _DEL(_port);

    for (vectorEvaluate::iterator pos = _evaluateVector.begin();
         pos != _evaluateVector.end(); pos++) {
        _DEL((*pos)->field);
        _DEL((*pos)->value);
        _DEL(*pos);
    }

    _evaluateVector.clear();
}

none_ COptSend::init(const optUnit *unit) {
    COperator::init(unit);

    for (vectorEvaluate::iterator pos = _evaluateVector.begin();
         pos != _evaluateVector.end(); pos++) {
        if ((*pos)->field) {
            (*pos)->field->init(unit->data);
        }

        if ((*pos)->value) {
            (*pos)->value->init(unit->data);
        }
    }

    if (TCP_SEND == _sendType && _destination) {
        _destination->init(unit->data);
    } else if (UDP_SEND == _sendType && _ip && _port) {
        _ip->init(unit->data);
        _port->init(unit->data);
    }
}

bool_ COptSend::addEvaluate(const ch_1 *fieldName,
        const CVariable *value) {
    if (!_pduInfo || (!fieldName || 0 == fieldName[0]) || !value) {
        return false_v;
    }

    CField *fieldInfo = _pduInfo->getField(fieldName);

    if (null_v == fieldInfo) {
        return false_v;
    }

    vectorEvaluate::iterator pos;

    for (pos = _evaluateVector.begin();
         pos != _evaluateVector.end(); pos++) {
        if ((*pos)->fieldInfo == fieldInfo) {
            if ((*pos)->field || (*pos)->value) {
                return false_v;
            }

            break;
        }
    }

    if (_evaluateVector.end() == pos) {
        return false_v;
    }

    (*pos)->field = (CVariable *) new CVarNetwork(fieldInfo);
    (*pos)->value = value->clone();

    return true_v;
}

none_ COptSend::work(const TMessageUnit *tmu) {
    size_ size = 0;

    for (vectorEvaluate::const_iterator pos = _evaluateVector.begin();
         pos != _evaluateVector.end(); pos++) {
        if (FIELD_GROUP_TYPE == (*pos)->fieldInfo->type()) {
            // If it's Group, check if it's available.
            if ((*pos)->field && (*pos)->value) {
                obj_ temp = null_v;
                bool_ isCountSize = false_v;

                // If ture, Defined Group
                if ((*pos)->value->value(temp)) {
                    isCountSize = true_v;
                } else if ((*pos)->fieldInfo->size(tmu->message, tmu->size)) {
                    // If ture, Network Group
                    isCountSize = true_v;
                }

                if (isCountSize) {
                    size += (*pos)->value->value(tmu)->size();
                }
            }
        } else {
            // if (null_v == (*pos)->fieldInfo->getGroupField())
            size += (*pos)->fieldInfo->getUnitSize();
        }
    }

    TMessageUnit mu;

    mu.size = size;
    mu.message = new ub_1[mu.size];
    mu.pduInfo = _pduInfo;
    memset(mu.message, 0, mu.size);

    TMsgInfo *msgInfo = ((TMessageUnit *) tmu)->msgInfo;
    TMsgInfo localMsgInfo;
    const CProcessor *processor = getContainer();

    if (!processor) {
        assert(0);
        // TODO do something to tell outside
        _DEL_ARR(mu.message);
        return;
    }

    for (vectorEvaluate::const_iterator pos = _evaluateVector.begin();
         pos != _evaluateVector.end(); pos++) {
        if ((*pos)->field && (*pos)->value) {
            if (FIELD_GROUP_TYPE == (*pos)->fieldInfo->type()) if (0 == (*pos)->value->value(tmu)->size()) {
                continue;
            }

            v_ *field = (*pos)->field->value(&mu);
            v_ *value = (*pos)->value->value(tmu);

            (*field) = (*value);
        }
    }

    if (TCP_SEND == _sendType && _destination) {
        v_ *value = _destination->value(tmu);

        processor = (CProcessor *) (obj_) *value;
    } else if (UDP_SEND == _sendType && _ip && _port) {
        v_ *ip = _ip->value(tmu);
        v_ *port = _port->value(tmu);

        memset(&localMsgInfo, 0, sizeof(TMsgInfo));
        strncpy(localMsgInfo.localIP, msgInfo->localIP, IP_MAX_LENGTH);
        localMsgInfo.localPort = msgInfo->localPort;
        strncpy(localMsgInfo.remoteIP, (const ch_1 *) *ip, IP_MAX_LENGTH);
        localMsgInfo.remotePort = (ub_2) *port;

        msgInfo = &localMsgInfo;
    }

    if (0 != ((CProcessor *) processor)->Send(_pduInfo,
            mu.message,
            mu.size,
            msgInfo)) {
        assert(0);
        // TODO do something to tell outside
        _DEL_ARR(mu.message);
        return;
    }

    _DEL_ARR(mu.message);
}
