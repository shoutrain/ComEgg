/*
 * CConnector.cpp
 *
 *  Created on: Jan 7, 2014
 *      Author: rafael
 */

#include "CConnector.h"

CConnector::CConnector() {
    // TODO Auto-generated constructor stub

}

CConnector::~CConnector() {
    // TODO Auto-generated destructor stub
}

bool_ CConnector::start(const CReactor *pReactor) {
    return true_v;
}

bool_ CConnector::stop() {
    return true_v;
}

ret_ CConnector::onSignal(const type_ signalType) {
    return 0;
}
