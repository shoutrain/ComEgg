#include "CUIManager.h"
#include "CContainer.h"

CUIManager *CUIManager::m_pInstance = null_v;

CUIManager::~CUIManager()
{
	for (map_container::iterator pos = m_ContainerMap.begin();
		 pos != m_ContainerMap.end(); pos++)
	{
		_DEL(pos->second);
	}

	m_ContainerMap.clear();
}

bool_ CUIManager::AddContainer(const CContainer *pContainer)
{
	if (!pContainer)
		return false_v;

	map_container::const_iterator pos = m_ContainerMap.find(pContainer->Name());

	// the container with same name has already exist;
	if (m_ContainerMap.end() != pos) 
		return false_v;

	((CContainer *)pContainer)->Data().SetParent(&Data());
	m_ContainerMap.insert(map_container::value_type(pContainer->Name(), 
													pContainer));	

	return true_v;
}

CContainer *CUIManager::GetContainer(const ch_1 *pszName) const
{
	if (!pszName)
		return null_v;

	map_container::const_iterator pos = m_ContainerMap.find(pszName);
 
	if (m_ContainerMap.end() != pos)
		return (CContainer *)pos->second;

	return null_v;
}

void CUIManager::Run()
{
	m_StartProgram.Work(null_v);
	fltk::run();
	m_EndProgram.Work(null_v);
}
