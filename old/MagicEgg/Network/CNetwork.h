#ifndef CNETWORK_H
#define CNETWORK_H

#include "NetworkCommon.h"

class CNetworkHandle;
class CNetworkConf;

class CNetwork
{
public:
	CNetwork() {}

	virtual void Work() = 0;
	virtual CNetworkHandle *GetHandle() = 0;
	virtual const CNetworkConf *GetConf() const = 0;
};

#endif // CNETWORK_H

