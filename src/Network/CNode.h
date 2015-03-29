#ifndef SRC_NETWORK_CNODE_H_
#define SRC_NETWORK_CNODE_H_

#include "../Common/CGlobal.h"

class CNodeConf;

enum ENodeType {
	NONE, TRUNK, BRANCH
};

enum ENodeStatus {
	FREE, BUSY
};

class CNode: public CGlobal {
public:

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

