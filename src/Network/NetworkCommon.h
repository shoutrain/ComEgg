#ifndef _NETWORK_COMMON_H_
#define _NETWORK_COMMON_H_

const ub_4 REV_BUFFER_MAX_SIZE = 65535;
const ub_4 IP_MAX_LENGTH = 15;

enum ENodeType {
    NONE,
    TRUNK,
	BRANCH
};

enum ENodeStatus {
    WORKING, SLEEPING
};

enum EDirection {
    IN = 1, OUT, ALL,
};

struct TMsgInfo {
    ch_1 localIP[IP_MAX_LENGTH];
    ub_2 localPort;
    ch_1 remoteIP[IP_MAX_LENGTH];
    ub_2 remotePort;
};

class CPduInfo;

struct TMessageUnit {
    CPduInfo *pduInfo;
    ub_1     *message;
    size_    size;
    TMsgInfo *msgInfo;
};

#endif // _NETWORK_COMMON_H_
