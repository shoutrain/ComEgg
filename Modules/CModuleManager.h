#ifndef CMODULE_MANAGER_H
#define CMODULE_MANAGER_H

#include "ModuleCommon.h"

#include <string>
#include <map>

using namespace std;

class CModuleInfo;

typedef map<string, const CModuleInfo *> map_module;

class CModuleManager: public CBaseClass
{
public:
	static CModuleManager *Instance()
	{
		if (m_pInstance)
			return m_pInstance;

		m_pInstance = new CModuleManager;

		return m_pInstance;
	}

	static void Destory()
	{
		_DEL(m_pInstance);
	}

	ret_ AddModule(const ch_1 *pszPath, 
				   const ch_1 *pszName,
				   const ch_1 *pszExt,
				   CModuleInfo *&pModule);
	ret_ GetModule(const ch_1 *pszName, CModuleInfo *&pModule);

	bool_ IsModuleReady(const ch_1 *pszName)
	{
		if (!pszName)
			return false_v;

		if (m_ModuleMap.end() != m_ModuleMap.find(pszName))
			return true_v;

		return false_v;
	}

protected:
	ret_ Stop();

private:
	CModuleManager(): CBaseClass(CMODULEMANAGER) {}

	CModuleManager(const CModuleManager &);
	const CModuleManager &operator =(const CModuleManager &);

	virtual ~CModuleManager()
	{
		Stop();
	}

	map_module m_ModuleMap;

	static CModuleManager *m_pInstance;
};

#endif // CMODULE_MANAGER_H
