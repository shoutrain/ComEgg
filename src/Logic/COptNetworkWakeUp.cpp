#include "COptNetworkWakeUp.h"
#include "../Network/CNetworkManager.h"

none_ COptNetworkWakeUp::work(const TMessageUnit *tmu) {
    v_ networkName = (*_networkName->value(tmu));

    CNetwork *network = (CNetwork *)
            CNetworkManager::Instance()->GetNetwork((const ch_1 *) networkName);

    if (network) {
        network->work();
    }
}



