#include "COptEmpty.h"

#include "../Data/CVarGroupDefined.h"

void COptEmpty::Work(const TMessageUnit *pTMU)
{
	try
	{
		CField *pField = null_v;
		v_ *p = m_pVariable->Value((obj_ &)pField);

		if (p)
		{
			TFieldGroup *pFieldGroup = (TFieldGroup *)(obj_)*p;

            if (pFieldGroup->size && pFieldGroup->data)
			{
                _DEL_ARR(pFieldGroup->data);
                pFieldGroup->size = 0;
			}
		}

		p = m_pVariable->Value(pTMU);
		p->empty();
	}
	catch (...)
	{
		throw;
	}
}



