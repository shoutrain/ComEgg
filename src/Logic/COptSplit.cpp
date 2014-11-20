#include "COptSplit.h"

#include "../System/CSysCall.h"

void COptSplit::Work(const TMessageUnit *pTMU)
{
	v_ Success((b_4)true_v);
	v_ Failure((b_4)false_v);

	(*m_pResult->Value(pTMU)) = Failure;

	try
	{
		v_ Command("./ComEgg ", 0);
		
		Command = Command + (*m_pEnvironment->Value(pTMU));

		CSysCall SysCall;

		if (!SysCall.Exec((const ch_1 *)Command))
			throw SYS_CALL_ERROR;

		(*m_pResult->Value(pTMU)) = Success;
	}
	catch (...)
	{
		
	}
}



