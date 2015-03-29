/*
 * CNodeRoute.h
 *
 *  Created on: Mar 29, 2015
 *      Author: rafael
 */

#ifndef SRC_NETWORK_CNODEROUTE_H_
#define SRC_NETWORK_CNODEROUTE_H_

#include "../Common/CGlobal.h"
#include "../Common/IWorkable.h"

class CNodeRoute: public CGlobal, public IWorkable {
public:
	CNodeRoute();
	virtual ~CNodeRoute();

	virtual bool working();

protected:

private:

};

#endif /* SRC_NETWORK_CNODEROUTE_H_ */
