/*
 * CSocketHelper.cpp
 *
 *  Created on: Mar 29, 2015
 *      Author: rafael
 */

#include "CSocketHelper.h"

#include <fcntl.h>

none_ CSocketHelper::setNonBlocking(b_4 socket) {
	int iOpts = fcntl(socket, F_GETFL);

	if (0 > iOpts) {
		log_error(
				"CSokcetHelper::setNonBlocking: failed to call fcntl with F_GETFL");
	}

	iOpts |= O_NONBLOCK;

	if (0 > fcntl(socket, F_SETFL, iOpts)) {
		log_error(
				"CTrafficManager::CSokcetHelper: failed to call fctntl with F_SETFL");
	}
}
