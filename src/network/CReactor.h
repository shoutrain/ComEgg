/*
 * CReactor.h
 *
 *  Created on: Jan 7, 2014
 *      Author: rafael
 */

#ifndef CREACTOR_H_
#define CREACTOR_H_

#include "../common/CBase.h"
#include "../common/IWorkable.h"
#include "../common/CResource.h"

class CReactor: public CBase, public IWorkable {
public:
    CReactor();
    virtual ~CReactor();

    none_ start();
    none_ stop();

protected:
    virtual bool_ working();

private:
    b_4 _epollFd;
};

#endif /* CREACTOR_H_ */
