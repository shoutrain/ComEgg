#include "COptNetworkWakeUp.h"
#include "../Network/CNetworkManager.h"

none_ COptNetworkWakeUp::work(const TMessageUnit *tmu) {
    v_ networkName = (*_networkName->value(tmu));

    CNode *network = (CNode *)
            CNetworkManager::instance()->GetNetwork((const ch_1 *) networkName);

    if (network) {
        network->work();
    }
}



