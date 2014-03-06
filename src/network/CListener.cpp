/*
 * CListener.cpp
 *
 *  Created on: Jan 7, 2014
 *      Author: rafael
 */

#include "CListener.h"

CListener::CListener() {
}

CListener::~CListener() {
}

bool_ CListener::start(const CReactor *pReactor) {
    if (0 == getPort()) {
        return false_v;
    }



    return true_v;
}

bool_ CListener::stop() {
    return true_v;
}

ret_ CListener::onSignal(const type_ signalType) {
    return 0;
}
