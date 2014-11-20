#ifndef _C_NETWORK_H_
#define _C_NETWORK_H_

#include "NetworkCommon.h"

class CNetworkConf;

class CNetwork: public CBase {
public:
	CNetwork(bool_ isAutoStart, ENetworkType type) {
		_isAutoStart = isAutoStart;
		_type = type;
	}

	virtual ~CNetwork() {
	}

	virtual none_ work() = 0;
	virtual none_ sleep() = 0;

	virtual const CNetworkConf *getConf() const = 0;

	bool_ isAutoStart() const {
		return _isAutoStart;
	}

	ENetworkType getType() const {
		return _type;
	}

private:
	bool_ _isAutoStart;
	ENetworkType _type;
};

#endif // _CNETWORK_H_

