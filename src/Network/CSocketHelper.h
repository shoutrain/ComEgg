/*
 * CSocketHelper.h
 *
 *  Created on: Mar 29, 2015
 *      Author: rafael
 */

#ifndef SRC_NETWORK_CSOCKETHELPER_H_
#define SRC_NETWORK_CSOCKETHELPER_H_

#include "../Common/CGlobal.h"

class CSocketHelper: public CGlobal {
public:
	static none_ setNonBlocking(b_4 socket);

private:
	CSocketHelper();
	virtual ~CSocketHelper();
};

#endif /* SRC_NETWORK_CSOCKETHELPER_H_ */
