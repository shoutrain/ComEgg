#include "CVarInterface.h"

#include "../UI/CUIManager.h"
#include "../UI/CContainer.h"

CVariable *CVarInterface::Clone() const
{
	return (CVariable *)new CVarInterface(m_szName);
}

v_ *CVarInterface::Value(const TMU *pTMU)
{
	CContainer *pContainer = CUIManager::Instance()->GetCurContainer();

	if (!pContainer)
		return null_v;

	CWindow *pWindow = pContainer->GetChild(m_szName);

	if (!pWindow)
		return null_v;

	return pWindow->Value();
}

