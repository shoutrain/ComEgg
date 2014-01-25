/*
 * CConnection.cpp
 *
 *  Created on: Jan 7, 2014
 *      Author: rafael
 */

#include "CConnection.h"

CConnection::CConnection() {
    // TODO Auto-generated constructor stub

}

CConnection::~CConnection() {
    // TODO Auto-generated destructor stub
}

bool_ CConnection::start(const CReactor *pReactor, ch_1 *pszIP, ub_2 port) {
    return true_v;
}

bool_ CConnection::stop() {
    return true_v;
}

ret_ CConnection::onSignal(const type_ signalType) {
    return 0;
}
