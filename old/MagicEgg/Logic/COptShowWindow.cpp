 #include "COptShowWindow.h"

#include "../UI/CUIManager.h"
#include "../UI/CContainer.h"

void COptShowWindow::Work(const TMU *pTMU)
{
	CContainer *pContainer = CUIManager::Instance()->GetCurContainer();

	if (pContainer)
		pContainer->Destroy();

	pContainer = CUIManager::Instance()->GetContainer(m_szWindowName);

	if (!pContainer)
		throw WINDOW_IS_NOT_EXIST;

	if (!pContainer->Create())
		throw WINDOW_CREATE_ERROR;
}



