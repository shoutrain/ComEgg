#ifndef _C_OPT_SEND_H_
#define _C_OPT_SEND_H_

#include "COperator.h"
#include "../Protocols/CPduInfo.h"

class COptSend : public COperator {
public:
    COptSend(const CPduInfo *pduInfo,
            const CVariable *destination = null_v);

    COptSend(b_4 sign,
            const CPduInfo *pduInfo,
            const CVariable *ip = null_v,
            const CVariable *port = null_v);

    COptSend(const COptSend &opt);

    const COptSend &operator=(const COptSend &opt);

    virtual COperator *clone() const {
        return (COperator *) new COptSend(*this);
    }

    virtual ~COptSend();

    bool_ addEvaluate(const ch_1 *fieldName, const CVariable *value);

    virtual none_ init(const optUnit *unit);

    virtual none_ work(const TMessageUnit *tmu);

private:
    COptSend();

    none_ clear();

    CPduInfo *_pduInfo;
    vectorEvaluate _evaluateVector;

    enum {
        NONE_SEND,
        TCP_SEND,
        UDP_SEND
    } _sendType;

    CVariable *_destination;
    CVariable *_ip;
    CVariable *_port;
};

#endif // _C_OPT_SEND_H_
