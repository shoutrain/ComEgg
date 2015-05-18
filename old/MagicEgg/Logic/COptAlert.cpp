#include "COptAlert.h"

#include "../UI/CUIManager.h"
#include "../UI/CContainer.h"

void COptAlert::Work(const TMU *pTMU)
{
	CContainer *pContainer = CUIManager::Instance()->GetCurContainer();

	if (!pContainer)
		throw WINDOW_IS_NOT_EXIST;

	//fltk::alert(m_pMessage);
	printf("%s\n", m_pMessage);
}



