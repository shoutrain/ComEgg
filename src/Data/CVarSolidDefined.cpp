#include "CVarSolidDefined.h"

CVariable *CVarSolidDefined::Clone() const
{
	return (CVariable *)new CVarSolidDefined(m_szName);
}

void CVarSolidDefined::Initialize(const CData *pData)
{
	m_pValue = pData->Value(m_szName);
}

v_ *CVarSolidDefined::Value(const TMU *pTMU)
{
	return m_pValue;
}
