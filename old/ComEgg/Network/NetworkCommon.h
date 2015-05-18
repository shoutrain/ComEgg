#ifndef NETWORK_COMMON_H
#define NETWORK_COMMON_H

#include "../Common/CBaseClass.h"

#include <ace/Reactor.h>
#include <ace/Acceptor.h>
#include <ace/SOCK_Acceptor.h>
#include <ace/Connector.h>
#include <ace/SOCK_Connector.h>
#include <ace/Svc_Handler.h>
#include <ace/Synch.h>
#include <ace/Thread.h>
#include <ace/SOCK_Dgram.h>

typedef ACE_Singleton<ACE_Reactor, ACE_Null_Mutex> Reactor;

const ub_4 REV_BUFFER_MAX_SIZE	= 65535;

const ub_4 IP_MAX_LENGTH		= 16;
const ub_4 IP_MAX_LENGTH_SIGN	= IP_MAX_LENGTH - 1;

enum ENetworkStatus
{
	WORKING,
	SLEEPING
};

enum EDirection
{
	DIRECTION_IN = 1,
	DIRECTION_OUT,
	DIRECTION_ALL,
};

enum ENetworkType
{
	NETWORK_NONE,
	NETWORK_ACCEPTOR,
	NETWORK_CONNECTOR,
	NETWORK_RECEIVER,
	NETWORK_SENDER
};

struct TMsgInfo
{
	ch_1	sLocalIP[IP_MAX_LENGTH];
	ub_2	nLocalPort;
	ch_1	sRemoteIP[IP_MAX_LENGTH];
	ub_2	nRemotePort;
};

class CPDUInfo;

struct TMU // Message Unit
{
	CPDUInfo	*pPDUInfo;
	ub_1		*pMessage;
	size_		nSize;
	TMsgInfo	*pMsgInfo;
};

#endif // NETWORK_COMMON_H
