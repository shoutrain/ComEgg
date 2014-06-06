/*
 * CConnection.h
 *
 *  Created on: Jan 7, 2014
 *      Author: rafael
 */

#ifndef CCONNECTION_H_
#define CCONNECTION_H_

#include "CNetNode.h"
#include "../common/CBase.h"

class CConnection: public CNetNode, public CBase {
public:
    CConnection();
    virtual ~CConnection();

    virtual bool_ start(const CReactor *pReactor, ch_1 *pszIP, ub_2 port);
    virtual bool_ stop();

    virtual ret_ onSignal(const type_ signalType);
};

#endif /* CCONNECTION_H_ */
