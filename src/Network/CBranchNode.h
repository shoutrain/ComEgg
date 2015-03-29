/*
 * CBranchNode.h
 *
 *  Created on: Mar 29, 2015
 *      Author: rafael
 */

#ifndef SRC_NETWORK_CBRANCHNODE_H_
#define SRC_NETWORK_CBRANCHNODE_H_

#include "CNode.h"
#include "../Common/IWorkable.h"

class CBranchNode: public CNode, public IWorkable {
public:
	CBranchNode();
	virtual ~CBranchNode();

	virtual bool_ working();
};

#endif /* SRC_NETWORK_CBRANCHNODE_H_ */
