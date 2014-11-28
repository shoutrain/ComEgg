#ifndef _C_NODE_H_
#define _C_NODE_H_

#include "NetworkCommon.h"

class CNodeConf;

class CNode : public CBase {
public:
    CNode(bool_ isAutoStart, ENetworkType type) {
        _isAutoStart = isAutoStart;
        _type        = type;
    }

    virtual ~CNode() {
    }

    virtual none_ work() = 0;

    virtual none_ sleep() = 0;

    virtual CNetworkConf *getConf() const = 0;

    bool_ isAutoStart() const {
        return _isAutoStart;
    }

    ENetworkType getType() const {
        return _type;
    }

private:
    bool_        _isAutoStart;
    ENetworkType _type;
};

#endif // _C_NODE_H_

