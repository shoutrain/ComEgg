/*
 * INetNode.h
 *
 *  Created on: Jan 7, 2014
 *      Author: rafael
 */

#ifndef INETNODE_H_
#define INETNODE_H_

#include "../common/CBase.h"
class CReactor;

class CNetNode: public CBase {
public:
    CNetNode();
    virtual ~CNetNode();

    virtual bool_ start(const CReactor *pReactor) = 0;
    virtual bool_ stop() = 0;

    virtual ret_ onSignal(const type_ signalType) = 0;

    bool_ bind(ch_1 *pszIp, ub_2 port);

    const ch_1 *getIp() const {
        return _szIp;
    }

    ub_2 getPort() const {
        return _port;
    }

private:
    ch_1 _szIp[16];
    ub_2 _port;

    CReactor *_pReator;
};

#endif /* INETNODE_H_ */
