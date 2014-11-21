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

        if (pFieldGroup->size && pFieldGroup->data)
		{
            _DEL_ARR(pFieldGroup->data);
            pFieldGroup->size = 0;
		}

        pFieldGroup->size = pField->getUnitSize() * ((size_) *pSize);
        pFieldGroup->data = new ub_1[pFieldGroup->size];
        memset(pFieldGroup->data, 0, pFieldGroup->size);
	}
	catch (...)
	{
		throw;
	}
}



