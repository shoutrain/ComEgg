#include "COptGetUsage.h"

#include "../System/CSysInfo.h"

void COptGetUsage::Work(const TMessageUnit *pTMU)
{
	try
	{
		CSysInfo si;

		v_ Usage((ub_1)si.GetUsage());

		(*m_pResult->Value(pTMU)) = Usage;
	}
	catch (...)
	{
		throw;
	}
}



