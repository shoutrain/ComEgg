/*
 * CTrunkNode.h
 *
 *  Created on: Mar 29, 2015
 *      Author: rafael
 */

#ifndef SRC_NETWORK_CTRUNKNODE_H_
#define SRC_NETWORK_CTRUNKNODE_H_

#include "CNode.h"
#include "../Common/IWorkable.h"

class CTrunkNode: public CNode, public IWorkable  {
public:
	CTrunkNode();
	virtual ~CTrunkNode();

	virtual bool working();
};

#endif /* SRC_NETWORK_CTRUNKNODE_H_ */
