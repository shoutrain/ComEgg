/*
 * INetNode.h
 *
 *  Created on: Jan 7, 2014
 *      Author: rafael
 */

#ifndef INETNODE_H_
#define INETNODE_H_

#include "../common/common.h"

class CReactor;

class INetNode {
public:
    virtual bool_ start(const CReactor *pReactor) = 0;
    virtual bool_ stop() = 0;

    virtual ret_ onSignal(const type_ signalType) = 0;
};

#endif /* INETNODE_H_ */
