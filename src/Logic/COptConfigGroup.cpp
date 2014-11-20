#include "COptConfigGroup.h"

#include "../Data/CVarGroupDefined.h"

void COptConfigGroup::Work(const TMessageUnit *pTMU)
{
	try
	{
		CField *pField = null_v;
		v_ *pGroupData = null_v;
		TFieldGroup *pFieldGroup = null_v;
		v_ *pSize = null_v;
	
		pGroupData = m_pGroup->Value((obj_ &)pField);
		pFieldGroup = (TFieldGroup *)(obj_)*pGroupData;
		pSize = m_pSize->Value(pTMU);

		if (pFieldGroup->nSize && pFieldGroup->pData)
		{
			_DEL_ARR(pFieldGroup->pData);
			pFieldGroup->nSize = 0;
		}

		pFieldGroup->nSize = pField->GetUnitSize() * ((size_)*pSize);
		pFieldGroup->pData = new ub_1[pFieldGroup->nSize];
		memset(pFieldGroup->pData, 0, pFieldGroup->nSize);
	}
	catch (...)
	{
		throw;
	}
}



