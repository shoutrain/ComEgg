#include "COptSearch.h"

void COptSearch::Work(const TMU *pTMU)
{
	try
	{
		v_ *pCategory	= m_pCategory->Value(pTMU);
		v_ *pKey		= m_pKey->Value(pTMU);
		v_ *pObj		= m_pObject->Value(pTMU);

		if (!pCategory || !pKey || !pObj)
			throw OPERATOR_OPERAITON_ERROR;

		if (STR != pCategory->get_type() || STR != pKey->get_type())
			throw OPERATOR_OPERAITON_ERROR;

		v_		*pObject	= null_v;
		ret_	Ret			= _ERR(CRegister::Instance()->Search(
									   (const ch_1 *)*pCategory, 
									   (const ch_1 *)*pKey, pObject));

		if (SUCCESS == Ret)
			*pObj = *pObject;
		else if (NO_ELEMENT_IN_CONTAINER != Ret)
			throw OPERATOR_OPERAITON_ERROR;
	}
	catch (...)
	{
		throw;
	}
}
