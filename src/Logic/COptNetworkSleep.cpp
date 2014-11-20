#include "COptNetworkSleep.h"

#include "../Network/CNetworkManager.h"

void COptNetworkSleep::Work(const TMessageUnit *pTMU)
{
	try
	{
		v_ NetworkName = (*m_pNetworkName->Value(pTMU));

		CNetwork *pNetwork = (CNetwork *)
			CNetworkManager::Instance()->GetNetwork((const ch_1 *)NetworkName);

		if (pNetwork)
			pNetwork->sleep();
	}
	catch (...)
	{
		throw;
	}
}




