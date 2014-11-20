#include "CVarSolidDefined.h"

CAutoVar *CVarSolidDefined::Clone() const
{
	return (CAutoVar *)new CVarSolidDefined(m_szName);
}

void CVarSolidDefined::Initialize(const CData *pData)
{
	m_pValue = pData->Value(m_szName);
}

v_ *CVarSolidDefined::Value(const TMessageUnit *pTMU)
{
	return m_pValue;
}
