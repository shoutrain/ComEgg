#ifndef CINTERFACE_INFO_H
#define CINTERFACE_INFO_H

#include "ModuleCommon.h"
#include "CModuleInfo.h"

#include <string.h>

class CInterfaceInfo: public CBaseClass
{
public:
	CInterfaceInfo(const CModuleInfo *pModuleInfo, const ch_1 *pszName)
		: CBaseClass(CINTERFACEINFO) 
	{
		m_pInField = null_v;
		m_pInCurField = null_v;
		m_pOutField = null_v;
		m_pOutCurField = null_v;
		m_pModuleInfo = (CModuleInfo *)pModuleInfo;
		memset(m_szName, 0, INTERFACE_NAME_LEGNTH);
		strncpy(m_szName, pszName, INTERFACE_NAME_LEGNTH);
	}

	virtual ~CInterfaceInfo() {}

	const CModuleInfo *GetModuleInfo() const
	{
		return m_pModuleInfo;
	}

	const ch_1 *Name() const
	{
		return m_szName;
	}

	// If GroupName is not null, Field is sub-field, GroupName is the name
	// of group.
	ret_ AddInField(const TField &Field,
				  const ch_1 *pszGroupName = null_v);
	ret_ AddOutField(const TField &Field,
				  const ch_1 *pszGroupName = null_v);

	// Get field
	ret_ GetInField(const ch_1 *pszName, CField *&pField);
	ret_ GetOutField(const ch_1 *pszName, CField *&pField);

	// Get struct
	ret_ GetInStruct(CField *&pField);
	ret_ GetOutStruct(CField *&pField);

protected:
	ret_ Stop();

private:
	map_field m_InFieldMap;
	map_field m_OutFieldMap;

	CField *m_pInField;
	CField *m_pInCurField;

	CField *m_pOutField;
	CField *m_pOutCurField;

	CModuleInfo *m_pModuleInfo;
	ch_1 m_szName[INTERFACE_NAME_LEGNTH];
};

#endif // CINTERFACE_INFO_H
