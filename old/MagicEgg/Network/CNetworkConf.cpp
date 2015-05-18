#include "CNetworkConf.h"

ret_ CNetworkConf::ConfigPDU(const v_ &ID,
							 const CPDUInfo *pPDUInfo,
							 EDirection Direction)
{
#ifdef _DEBUG_
	if (!pPDUInfo)
		return PARAMETER_NULL | PARAMETER_1;

	if (DIRECTION_IN	!= Direction &&
		DIRECTION_OUT	!= Direction &&
		DIRECTION_ALL	!= Direction)
	{
		return PARAMETER_TYPE_ERROR | PARAMETER_2;
	}
#endif

	if (DIRECTION_IN == (EDirection)(Direction & DIRECTION_IN))
	{
#ifdef _DEBUG_
		try
		{
			CPDUInfo	*pTempPDUInfo = null_v;
			v_			TempID;

			if (true_v == FindPDU(ID, DIRECTION_IN, pTempPDUInfo)
				|| true_v == FindID(pPDUInfo, DIRECTION_IN, TempID))
			{
				return ELEMENT_EXIST_IN_CONTAINER;
			}
		}
		catch (error_code err)
		{
			return err;
		}
#endif

		try
		{
			m_PDUInTableMap.insert(map_pdu_table::value_type((size_)ID,
															 pPDUInfo));
			m_IDInTableMap.insert(map_id_table::value_type(pPDUInfo,
														   (size_)ID));
		}
		catch (error_code err)
		{
#ifdef _DEBUG_
			return err;
#endif
		}
	}

	if (DIRECTION_OUT == (EDirection)(Direction & DIRECTION_OUT))
	{
#ifdef _DEBUG_
		try
		{
			CPDUInfo	*pTempPDUInfo = null_v;
			v_			TempID;

			if (true_v == FindPDU(ID, DIRECTION_OUT, pTempPDUInfo)
				|| true_v == FindID(pPDUInfo, DIRECTION_OUT, TempID))
			{
				return ELEMENT_EXIST_IN_CONTAINER;
			}
		}
		catch (error_code err)
		{
			return err;
		}
#endif

		try
		{
			m_PDUOutTableMap.insert(map_pdu_table::value_type((size_)ID,
															  pPDUInfo));
			m_IDOutTablemap.insert(map_id_table::value_type(pPDUInfo,
															(size_)ID));
		}
		catch (error_code err)
		{
#ifdef _DEBUG_
			return err;
#endif
		}
	}

	return SUCCESS;
}

ret_ CNetworkConf::IdentifyID(const v_ &ID,
							  CPDUInfo *&pPDUInfo,
							  EDirection Direction)
{
#ifdef _DEBUG_
	if (pPDUInfo)
		return PARAMETER_NOT_NULL | PARAMETER_2;

	if (DIRECTION_IN != Direction
		&& DIRECTION_OUT != Direction)
	{
		return PARAMETER_TYPE_ERROR | PARAMETER_3;
	}
#endif

	if (false_v == FindPDU(ID, Direction, pPDUInfo))
		return FAILURE;

	return SUCCESS;
}

ret_ CNetworkConf::IdentifyPDU(const CPDUInfo *pPDUInfo,
							   v_ &ID,
							   EDirection Direction)
{
#ifdef _DEBUG_
	if (!pPDUInfo)
		return PARAMETER_NULL | PARAMETER_2;

	if (DIRECTION_IN != Direction
		&& DIRECTION_OUT != Direction)
	{
		return PARAMETER_TYPE_ERROR | PARAMETER_3;
	}
#endif

	if (false_v == FindID(pPDUInfo, Direction, ID))
		return FAILURE;

	return SUCCESS;
}


bool_ CNetworkConf::FindPDU(const v_ &ID,
							EDirection Direction,
							CPDUInfo *&pPDUInfo)
{
	map_pdu_table::const_iterator pos/* = m_PDUInTableMap.end()*/;

	try
	{
		if (DIRECTION_IN == Direction)
		{
			pos = m_PDUInTableMap.find((size_)ID);

			if (m_PDUInTableMap.end() != pos)
			{
				pPDUInfo = (CPDUInfo *)pos->second;

				return true_v;
			}

		}
		else if (DIRECTION_OUT == Direction)
		{
			pos = m_PDUOutTableMap.find((size_)ID);

			if (m_PDUOutTableMap.end() != pos)
			{
				pPDUInfo = (CPDUInfo *)pos->second;

				return true_v;
			}
		}
	}
	catch (...)
	{
		return false_v;
	}

	return false_v;
}

bool_ CNetworkConf::FindID(const CPDUInfo *pPDUInfo,
						   EDirection Direction,
						   v_ &ID)
{
	map_id_table::const_iterator pos;

	if (DIRECTION_IN == Direction)
	{
		pos = m_IDInTableMap.find((CPDUInfo *)pPDUInfo);

		if (m_IDInTableMap.end() != pos)
		{
			ID = v_((size_)pos->second);

			return true_v;
		}

	}
	else if (DIRECTION_OUT == Direction)
	{
		pos = m_IDOutTablemap.find((CPDUInfo *)pPDUInfo);

		if (m_IDOutTablemap.end() != pos)
		{
			ID = v_((size_)pos->second);

			return true_v;
		}
	}

	return false_v;
}

