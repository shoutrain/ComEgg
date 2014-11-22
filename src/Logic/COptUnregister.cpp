#include "COptUnregister.h"

void COptUnregister::work(const TMessageUnit *tmu)
{
	try
	{
        v_ *pCategory = m_pCategory->Value(tmu);
        v_ *pKey = m_pKey->Value(tmu);

		if (!pCategory || !pKey)
			throw OPERATOR_OPERAITON_ERROR;

		if (STR != pCategory->get_type() || STR != pKey->get_type())
			throw OPERATOR_OPERAITON_ERROR;

		v_ *pObject = null_v;

		if (SUCCESS == _ERR(
				CRegister::Instance()->Search((const ch_1 *)*pCategory, 
											  (const ch_1 *)*pKey, pObject)))
		{
			if (OBJ == pObject->get_type())
			{
				obj_		pObj		= (obj_)(*pObject);
				CProcessor	*pProcessor = (CProcessor *)pObj;

				if (!pProcessor)
					throw OPERATOR_OPERAITON_ERROR;

				ret_ Ret = pProcessor->Unregister((const ch_1 *)*pCategory, 
												  (const ch_1 *)*pKey);

				if (SUCCESS != _ERR(Ret))
					throw OPERATOR_OPERAITON_ERROR;
			}
			else
			{
				if (SUCCESS != _ERR(
						CRegister::Instance()->Unregister(
							(const ch_1 *)*pCategory, (const ch_1 *)*pKey)))
				{
					throw OPERATOR_OPERAITON_ERROR;					
				}
			}
		}
		else
			throw OPERATOR_OPERAITON_ERROR;
	}
	catch (...)
	{
		throw;
	}
}
