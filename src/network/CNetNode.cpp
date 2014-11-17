/*
 * CNetNode.cpp
 *
 *  Created on: Jan 25, 2014
 *      Author: rafael
 */

#include "CNetNode.h"

CNetNode::CNetNode() :
        _port(0), pReactor(null_v) {
    memset(_szIp, 0, 16);
}

CNetNode::~CNetNode() {
}

bool_ CNetNode::bind(ch_1 *pszIp, ub_2 port) {
    if ((null_v != pszIp && 0 == pszIp[0])
            || 15 < strlen(pszIp) /* TODO checking if it's a legal IP */) {
        return false_v;
    }

    if (1024 >= port) {
        return false_v;
    }

    if (null_v != pszIp) { // for connection and connector
        strncpy(_ip, ip, 15);
    } else { // only for listener
        memset(_szIp, 0, 16);
    }

    _port = port;

    return true_v;
}
