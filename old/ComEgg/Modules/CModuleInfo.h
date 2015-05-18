#ifndef CMODULE_INFO_H
#define CMODULE_INFO_H

#include "ModuleCommon.h"
#include "../Data/CData.h"

#include <string>
#include <map>

using namespace std;

class CInterfaceInfo;

typedef map<string, const CInterfaceInfo *> map_interface;

class CModuleInfo: public CBaseClass
{
public:
	CModuleInfo(const ch_1 *pszPath, const ch_1 *pszName, const ch_1 *pszExt)
		: CBaseClass(CMODULEINFO)
	{
		memset(m_szPath, 0, MODULE_PATH_LENGTH);
		strncpy(m_szPath, pszPath, MODULE_PATH_LENGTH);
		memset(m_szName, 0, MODULE_NAME_LENGTH);
		strncpy(m_szName, pszName, MODULE_NAME_LENGTH);
		memset(m_szExt, 0, MODULE_EXT_LENGTH);
		strncpy(m_szExt, pszExt, MODULE_EXT_LENGTH);
	}

	virtual ~CModuleInfo()
	{
		Stop();
	}

	const char *GetPath() const
	{
		return m_szPath;
	}

	const char *GetName() const
	{
		return m_szName;
	}

	const char *GetExt() const
	{
		return m_szExt;
	}

	ret_ AddInterface(const ch_1 *pszName, CInterfaceInfo *&pInterfaceInfo);
	ret_ GetInterface(const ch_1 *pszName, CInterfaceInfo *&pInterfaceInfo);

	bool_ IsInterfaceReady(const ch_1 *pszName)
	{
		if (m_InterfaceInfoMap.end() != m_InterfaceInfoMap.find(pszName))
			return true_v;

		return false_v;
	}

protected:
	ret_ Stop();

private:
	map_interface m_InterfaceInfoMap;

	ch_1 m_szPath[MODULE_PATH_LENGTH];
	ch_1 m_szName[MODULE_NAME_LENGTH];
	ch_1 m_szExt[MODULE_EXT_LENGTH];
};

#endif // CMODULE_INFO_H
