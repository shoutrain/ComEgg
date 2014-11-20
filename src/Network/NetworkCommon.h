#ifndef _NETWORK_COMMON_H_
#define _NETWORK_COMMON_H_

#include "../Common/CBase.h"

const ub_4 REV_BUFFER_MAX_SIZE = 65535;
const ub_4 IP_MAX_LENGTH = 16;
const ub_4 IP_MAX_LENGTH_SIGN = IP_MAX_LENGTH - 1;

enum ENetworkStatus {
	WORKING, SLEEPING
};

enum EDirection {
	DIRECTION_IN = 1, DIRECTION_OUT, DIRECTION_ALL,
};

enum ENetworkType {
	NETWORK_NONE,
	NETWORK_ACCEPTOR,
	NETWORK_CONNECTOR,
	NETWORK_RECEIVER,
	NETWORK_SENDER
};

struct TMsgInfo {
	ch_1 localIP[IP_MAX_LENGTH];
	ub_2 localPort;
	ch_1 remoteIP[IP_MAX_LENGTH];
	ub_2 remotePort;
};

class CPDUInfo;

struct TMessageUnit {
	CPDUInfo *pduInfo;
	ub_1 *message;
	size_ size;
	TMsgInfo *msgInfo;
};

#endif // _NETWORK_COMMON_H_
