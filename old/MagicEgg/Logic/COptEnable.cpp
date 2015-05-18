#include "COptEnable.h"

#include "../UI/CUIManager.h"
#include "../UI/CContainer.h"

void COptEnable::Work(const TMU *pTMU)
{
	CContainer *pContainer = CUIManager::Instance()->GetCurContainer();

	if (!pContainer)
		throw WINDOW_IS_NOT_EXIST;

	CWindow * pWindow = pContainer->GetChild(m_szWindowName);

	if (pWindow)
		pWindow->Enable(m_bIsEnable);
	else
		pContainer->Enable(m_bIsEnable);
}



