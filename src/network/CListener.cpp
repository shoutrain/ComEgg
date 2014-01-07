/*
 * CListener.cpp
 *
 *  Created on: Jan 7, 2014
 *      Author: rafael
 */

#include "CListener.h"

CListener::CListener() {
    // TODO Auto-generated constructor stub

}

CListener::~CListener() {
    // TODO Auto-generated destructor stub
}

bool_ CListener::start(const CReactor *pReactor) {
    return true_v;
}

bool_ CListener::stop() {
    return true_v;
}

ret_ CListener::onSignal(const type_ signalType) {
    return 0;
}
