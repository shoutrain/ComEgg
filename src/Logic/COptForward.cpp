#include "COptForward.h"

#include "../Network/NetworkCommon.h"

none_ COptForward::work(const TMessageUnit *tmu) {
    TMsgInfo *msgInfo = ((TMessageUnit *) tmu)->msgInfo;
    TMsgInfo localMsgInfo;
    const CProcessor *processor = getContainer();

    if (!processor) {
        assert(0);
        // TODO do something to let outside know
        return;
    }

    if (TCP_SEND == _sendType && _object) {
        v_ *value = _object->value(tmu);

        processor = (CProcessor *) (obj_) *value;
    } else if (UDP_SEND == _sendType && _ip && _port) {
        v_ *ip = _ip->value(tmu);
        v_ *port = _port->value(tmu);

        memset(&localMsgInfo, 0, sizeof(TMsgInfo));
        strncpy(localMsgInfo.localIP, msgInfo->localIP, IP_MAX_LENGTH);
        localMsgInfo.localPort = msgInfo->localPort;
        strncpy(localMsgInfo.remoteIP, (const ch_1 *) *ip, IP_MAX_LENGTH);
        localMsgInfo.remotePort = (ub_2) *port;

        msgInfo = &localMsgInfo;
    }

    if (0 != ((CProcessor *) processor)->send(
            (const CPduInfo *) ((TMessageUnit *) tmu)->pduInfo,
            ((TMessageUnit *) tmu)->message,
            ((TMessageUnit *) tmu)->size,
            msgInfo)) {
        assert(0);
        // TODO do something to let outside know
    }
}
