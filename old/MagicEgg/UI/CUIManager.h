#ifndef CUI_MANAGER_H
#define CUI_MANAGER_H

#include "UICommon.h"

#include <string>
#include <map>

using namespace std;

class CContainer;

typedef map<string, const CContainer *> map_container;

class CUIManager
{
public:
	static CUIManager *Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CUIManager;

		return m_pInstance;
	}

	static void Destory()
	{
		_DEL(m_pInstance);
	}

	bool_ AddContainer(const CContainer *pContainer);
	CContainer *GetContainer(const ch_1 *pszName) const;

	void SetCurContainer(const CContainer *pContainer = null_v)
	{
		m_pCurContainer = (CContainer *)pContainer;
	}

	CContainer *GetCurContainer() const
	{
		return m_pCurContainer;
	}
	
	void Run();

	CData &Data()
	{
		return m_Data;
	}

	CProgram &StartProgram()
	{
		return m_StartProgram;
	}

	CProgram &EndProgram()
	{
		return m_EndProgram;
	}
	
private:
	CUIManager(): m_pCurContainer(null_v) {}

	CUIManager(const CUIManager &);
	const CUIManager &operator =(const CUIManager &);
	
	virtual ~CUIManager();
	
	map_container m_ContainerMap;
	CContainer *m_pCurContainer;

	CData m_Data;

	CProgram m_StartProgram;
	CProgram m_EndProgram;

	static CUIManager *m_pInstance;
};

#endif // CUI_MANAGER_H
