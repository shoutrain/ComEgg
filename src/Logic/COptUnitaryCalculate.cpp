#include "COptUnitaryCalculate.h"

void COptUnitaryCalculate::work(const TMessageUnit *tmu)
{
	try
	{
		switch (m_Opt)
		{
		case UC_EQL:
            (*m_pResultVariable->Value(tmu)) =
                    (*m_pRightVariable->Value(tmu));
			return;
		case UC_NEG:
            (*m_pResultVariable->Value(tmu)) =
                    -(*m_pRightVariable->Value(tmu));
			return;
		case UC_OBV:
            (*m_pResultVariable->Value(tmu)) =
                    ~(*m_pRightVariable->Value(tmu));
			return;
		case UC_NOT:
            (*m_pResultVariable->Value(tmu)) =
                    v_(!(*m_pRightVariable->Value(tmu)));
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
