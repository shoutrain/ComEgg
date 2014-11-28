#include <string.h>

#include "CIPFilter.h"

bool_ CIPFilter::addIpGroup(const ch_1 *ip) {
    assert(ip && 0 != ip[0]);

    if (!_isWork) {
        return false_v;
    }

    b_4  length = (b_4) strlen(ip);
    b_4  m      = 0;
    ch_1 singleIp[16];

    memset(singleIp, 0, 16);

    for (b_4 n = 0; n <= length; n++) {
        if (' ' == ip[n] || '\0' == ip[n]) {
            if (!_ipSet.count(singleIp)) {
                _ipSet.insert(singleIp);
                memset(singleIp, 0, 16);
                m = 0;
            }
        } else {
            singleIp[m++] = ip[n];
        }
    }

    return true_v;
}

