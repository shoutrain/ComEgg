#ifndef SRC_NETWORK_CNODE_H_
#define SRC_NETWORK_CNODE_H_

#include "../Common/CGlobal.h"

class CNodeConf;

enum ENodeType {
	NONE, TRUNK, BRANCH, JOINT
};

enum ENodeStatus {
	FREE, BUSY
};

class CNode: public CGlobal {
public:
	virtual bool_ onConnect() = 0;
	virtual bool_ onMessage() = 0;
	virtual void onError() = 0;
	virtual void onClose() = 0;

	virtual b_4 write() = 0;

	ENodeType type() const {
		return _type;
	}

	ENodeStatus status() const {
		return _status;
	}

protected:
	CNode(ENodeType type) {
		_type = type;
		_status = FREE;
	}

	virtual ~CNode() {
	}

private:
	ENodeType _type;
	ENodeType _status;
};

#endif /* SRC_NETWORK_CNODE_H_ */

