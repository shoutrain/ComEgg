/*
 * CListener.h
 *
 *  Created on: Jan 7, 2014
 *      Author: rafael
 */

#ifndef CLISTENER_H_
#define CLISTENER_H_

#include "CNetNode.h"

class CListener: public CNetNode{
public:
    CListener();
    virtual ~CListener();

    virtual bool_ start(const CReactor *pReactor);
    virtual bool_ stop();

    virtual ret_ onSignal(const type_ signalType);

private:

};

#endif /* CLISTENER_H_ */
