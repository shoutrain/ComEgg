#include "COptUnitaryCalculate.h"

void COptUnitaryCalculate::Work(const TMessageUnit *pTMU)
{
	try
	{
		switch (m_Opt)
		{
		case UC_EQL:
			(*m_pResultVariable->Value(pTMU)) =
				(*m_pRightVariable->Value(pTMU));
			return;
		case UC_NEG:
			(*m_pResultVariable->Value(pTMU)) =
				-(*m_pRightVariable->Value(pTMU));
			return;
		case UC_OBV:
			(*m_pResultVariable->Value(pTMU)) =
				~(*m_pRightVariable->Value(pTMU));
			return;
		case UC_NOT:
			(*m_pResultVariable->Value(pTMU)) =
				v_(!(*m_pRightVariable->Value(pTMU)));
			return;
		default:
			throw OPERATOR_OPERAITON_ERROR;
		}
	}
	catch (...)
	{
		throw;
	}
}
