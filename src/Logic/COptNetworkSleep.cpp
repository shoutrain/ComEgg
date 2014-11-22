#include "COptNetworkSleep.h"
#include "../Network/CNetworkManager.h"

void COptNetworkSleep::work(const TMessageUnit *tmu) {
    v_ networkName = (*_networkName->value(tmu));

    CNetwork *network = (CNetwork *)
            CNetworkManager::Instance()->GetNetwork((const ch_1 *) networkName);

    if (network) {
        network->sleep();
    }
}
