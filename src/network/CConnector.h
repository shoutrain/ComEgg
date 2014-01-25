/*
 * CConnector.h
 *
 *  Created on: Jan 7, 2014
 *      Author: rafael
 */

#ifndef CCONNECTOR_H_
#define CCONNECTOR_H_

#include "INetNode.h"
#include "../common/CBase.h"

class CConnector: public INetNode, public CBase {
public:
    CConnector();
    virtual ~CConnector();

    virtual bool_ start(const CReactor *pReactor, ch_1 *pszIP, ub_2 port);
    virtual bool_ stop();

    virtual ret_ onSignal(const type_ signalType);
};

#endif /* CCONNECTOR_H_ */
