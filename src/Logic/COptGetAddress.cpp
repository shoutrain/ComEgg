#include "COptGetAddress.h"

void COptGetAddress::work(const TMessageUnit *tmu) {
    if (_remote) {
        *_ip->value(tmu) = v_((ch_1 *) (tmu->msgInfo->remoteIP));
        *_port->value(tmu) = v_((ub_2) (tmu->msgInfo->remotePort));
    } else {
        *_ip->value(tmu) = v_((ch_1 *) (tmu->msgInfo->localIP));
        *_port->value(tmu) = v_((ub_2) (tmu->msgInfo->localPort));
    }
}
