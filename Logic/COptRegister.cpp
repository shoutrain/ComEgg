#include "COptRegister.h"

void COptRegister::Work(const TMU *pTMU)
{
	try
	{
		v_ *pCategory	= m_pCategory->Value(pTMU);
		v_ *pKey		= m_pKey->Value(pTMU);

		if (!pCategory || !pKey)
			throw OPERATOR_OPERAITON_ERROR;

		if (STR != pCategory->get_type() || STR != pKey->get_type())
			throw OPERATOR_OPERAITON_ERROR;

		v_ *pObj = m_pObject->Value(pTMU);

		if (pObj)
		{
			if (OBJ != pObj->get_type())
			{
				obj_		p			= (obj_)(*pObj);
				CProcessor	*pProcessor = (CProcessor *)p;

				if (!pProcessor)
					throw OPERATOR_OPERAITON_ERROR;

				if (SUCCESS != _ERR(pProcessor->Register(
										(const ch_1 *)*pCategory,
										(const ch_1 *)*pKey, m_bIsCovered)))
				{
					throw OPERATOR_OPERAITON_ERROR;
				}
			}
			else
			{
				if (SUCCESS != _ERR(CRegister::Instance()->Register(
										(const ch_1 *)*pCategory,
										(const ch_1 *)*pKey,
										pObj,
										m_bIsCovered)))
				{
					throw OPERATOR_OPERAITON_ERROR;
				}
			}
		}
		else
		{
			CProcessor *pProcessor = (CProcessor *)GetContainer();

			if (!pProcessor)
				throw OPERATOR_OPERAITON_ERROR;

			if (SUCCESS != _ERR(pProcessor->Register(
									(const ch_1 *)*pCategory,
									(const ch_1 *)*pKey,
									m_bIsCovered)))
			{
				throw OPERATOR_OPERAITON_ERROR;
			}
		}
	}
	catch (...)
	{
		throw;
	}
}
