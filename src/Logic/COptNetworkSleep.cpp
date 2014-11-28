#include "COptNetworkSleep.h"
#include "../Network/CNetworkManager.h"

none_ COptNetworkSleep::work(const TMessageUnit *tmu) {
    v_ networkName = (*_networkName->value(tmu));

    CNode *network = (CNode *)
            CNetworkManager::instance()->GetNetwork((const ch_1 *) networkName);

    if (network) {
        network->sleep();
    }
}
